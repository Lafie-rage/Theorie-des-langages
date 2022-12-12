/**
 *	\file		hoc.y
 *	\version	2.0
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
%type	<reel> expr
%type	<symb> opAlg sym nbr var
/* Associativités & priorités */
%left ADD SUB
%left MUL DIV
%nonassoc UNARY_MINUS

%%
// return : fin de génération de code intermédiare
// suivi d'une génération de code machine (ici évaluation)
liste :	/* VIDE */
	| liste error RC    { yyerrok; yyclearin; code (STOP); return 1;}
	| liste RC 			{ code (STOP); return 2;}
	| liste expr  RC	{ code((instr_t)printExprCode); code (STOP); return 3;}
	| liste cmd	  RC 	{ code (STOP); return 5;}
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
opAlg : ADD | SUB | MUL | DIV
	;
// génération de code : empiler du code (fct, @ symbole) sur une pile de code
expr :	ENTIER 			{ code2((instr_t)intPush, (instr_t)$1);  }
    | REEL 				{ code2((instr_t)floPush, (instr_t)$1);}
	| IVAR  			{ code3((instr_t)varPush, (instr_t)$1, (instr_t)varEval);}
	| FVAR   			{ code3((instr_t)varPush, (instr_t)$1, (instr_t)varEval);}
	| PO expr PF  		{ $$=$2; }
	| expr opAlg expr 	{ code ((instr_t)*($2->U.pFct)); }
	| SUB expr 			{ code((instr_t)negate); } %prec UNARY_MINUS
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
	printMessage(1,"2.0");
    installDefaultSymbols();
	for (initCode(); ((resParse=yyparse()) !=0 ) ; initCode()) {
		execute(PC);
		switch (resParse) {
			case 1 : printMessage(46, "\t--- Une erreur a été comise ---"); break;
			case 2 : printMessage(46, "\t--- Un retour à la ligne a été demandé ---"); break;
			case 3 : printMessage(46, "\t--- Une expression algébrique a été évaluée ---"); break;
			case 4 : printMessage(46, "\t--- Une variable a été assignée ---"); break;
			case 5 : printMessage(46, "\t--- Une commande a été demandée ---"); break;
			default : printMessage(46, "\t--- OVNI ---"); break;
		}		
	}
	printMessage(2);
    return 0;
}

