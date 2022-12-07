/**
 *	\file		hoc.y
 *	\version	1.4.6
 *	\date		5 Février 2021
 *	\author		Samir El Khattabi
*/
%{
#define _HOC_Y_
#include "hoc.h"
extern int yylex(void);
void init(void);
int isFloat = 0;
%}
/* YYSTYPE  : Définition des valeurs sémantiques (yylval renseignée par lex) */
%union {
	int			entier;
	double		reel;
	pSymbol_t	symb;
}
/* Tokens fictifs : déclaration des classes */
%token DAT CST VAR PRG
/* Tokens nombres */
%token	<symb> ENTIER REEL
/* Token pour identifiant non reconnu */
%token	<symb> UNDEF
/* Tokens pour les variables : passage de UNDEF vers IVAR/FVAR */
%token	<symb> IVAR FVAR
/* Token pour fonction prédéfinie */
%token	<symb> PREDEF
// Typage des tokens d'opérations arithmétiques
%token <symb> ADD SUB MUL DIV
%token <symb> PO PF
// Tokens sans valeurs sémantiques
%token RC
%token AFF
%token PR_TS PR_TS2 DBG_TS DBG_TS2 DBG
/* Typage des unités syntaxiques */
%type	<reel> expr assgn
%type	<symb> opAlg sym
/* Associativités & priorités */
%right AFF
%left ADD SUB
%left MUL DIV
%nonassoc UNARY_MINUS

%%
liste :	/* VIDE */
	| liste RC 			{ init (); }
	| liste expr  RC	{ printExpr(isFloat,$2); init (); }
	| liste assgn RC    { printExpr(isFloat,$2); init (); }
	| liste error RC    { yyerrok; yyclearin; init ();}
	| liste cmd	  RC 	{ init();}
	;
sym : nbr | var | PREDEF | opAlg
	;
nbr : ENTIER | REEL
	;
var : UNDEF |  IVAR | FVAR 
	;
cmd	: PR_TS				{ printSymbolList();}
	| PR_TS2			{ printSymbolListByClass();}
	| DBG_TS			{ dbgSymbolList(); }
	| DBG_TS2			{ dbgSymbolListV2(); }
	| DBG sym			{ dbgSymbol($2); }
	;
assgn :
      IVAR AFF expr		{ $$ = *(int *)$1->U.pValue    = $3; }
	| FVAR  AFF expr    { $$ = *(double *)$1->U.pValue = $3; }
	| UNDEF AFF expr    {
        $1->type = (isFloat)?FVAR:IVAR;
        $1->size = (isFloat)?sizeof(double):sizeof(int);
       	if (isFloat) $1->U.pValue = allocFlo($3);
		else $1->U.pValue = allocInt($3);
		$$ =  $3;
    }
	;
opAlg : ADD | SUB | MUL | DIV
	;
expr :	ENTIER 			{ $$=*(int *)$1->U.pValue; }
    | REEL 				{ memcpy((generic)&$$, $1->U.pValue, $1->size); isFloat=1;}
	| IVAR  			{ $$=*(int *)$1->U.pValue; }
	| FVAR   			{ memcpy((generic)&$$, $1->U.pValue, $1->size); isFloat=1;}
	| UNDEF				{ printMessageTag(13,$1->name); YYERROR;
						// yyerror("Undefined variable --%s--\n", $1->name);
						
						}
	| PO expr PF  		{ $$=$2; }
	| expr opAlg expr 	{ $$ = (*($2->U.pFct))($1,$3); }
	| SUB expr 			{ $$ = -$2; } %prec UNARY_MINUS
	| PREDEF PO expr PF { $$ = (*($1->U.pFct))($3); isFloat=1;}
	;
%%

/**
 *	\var        progName
 *	\brief		Nom du programme
 *	\note 		A déclarer avec l'attribut "extern" par les utilisateurs
 */
char * progName;
int main(int argc, char **argv) {
    int resParse;
    
	progName = argv[0];
	printMessage(0);
	printMessage(1,"1.4.6");
    installDefaultSymbols();
    init();
//    while ((resParse=yyparse())!=0) init();
    resParse=yyparse();
    printf("Le parseur se termine dans l'état %d\n", resParse);
    return 0;
}
void init(void) {
	prompt();
    isFloat = 0;
}

