%{
  #define HOC_Y
  #include "hoc.h"
  int yylex(void);
  void yyerror(char *);
  void init(void);
  void promptResult(float);
  int isFloat = 0;
  int lineNumber = 0;
%}
%start  list
/* YYSTYPE : Définition des valeurs sémantiques (yylval renseignée par lex) */
%union {
  int entier;
  double reel;
  pSymbol_t symb;
}
%token RC ADD SUB MUL DIV PO PF AFF EQ N_EQ SUP SUP_EQ INF INF_EQ AND OR NOT
/* Tokens fictifs : définition des classes */
%token VAL CST VAR
/* Tokens nombres */
%token <symb> ENTIER REEL
/* Tokens pour identifiant non reconnu */
%token <symb> UNDEF
/* Tokens pour les variables : passage de UNDEF vers IVAR/FVAR */
%token <symb> IVAR FVAR
/* Typage des unités syntaxiques */
%type  <reel>  expr assign val
%left ADD SUB
%left MUL DIV
%right AFF
%nonassoc UMINUS
%%
  list    : // vide
          | list expr RC                  {
                                            promptResult($2);
                                            init();
                                          }
          | list assign RC                {init();}
          | list error RC                 {yyerrok;init();}// Rend les erreurs acceptables.
          | list RC
          ;

  expr    : val
          | expr ADD expr                  {$$ = $1 + $3;}
          | expr SUB expr                  {$$ = $1 - $3;}
          | SUB expr  %prec UMINUS        {$$ = -$2;}
          | PO expr PF                    {$$ = $2;}
          | expr MUL expr                 {$$ = $1 * $3;}
          | expr DIV expr                 {
                                            if($3 == 0) {
                                              yyerror("Dividing by 0");
                                              YYERROR;
                                            } else
                                              $$ = $1/$3;
                                          }
          ;

  val     : ENTIER                        {$$ = *(int *) $1->pValue;}
          | REEL                          {memcpy((generic) &$$, $1->pValue, $1->size); isFloat = 1;}
          | IVAR                          {$$ = *(int *) $1->pValue;}
          | FVAR                          {$$ = *(double *) $1->pValue; isFloat = 1;}
          ;

  assign  : IVAR AFF expr                 {
                                            $$ = *(int *)$1->pValue = $3;
                                          }
          | FVAR AFF expr                 {
                                            $$ = *(double *)$1->pValue = $3;
                                            isFloat = 1;
                                          }
          | UNDEF AFF expr                {
                                            $1->class = VAR;
                                            $1->type = (isFloat) ? FVAR : IVAR;
                                            $1->size = (isFloat) ? sizeof(double) : sizeof(int);
                                            if(isFloat) {
                                              $1->pValue = (double *) malloc(sizeof(double));
                                              $$ = *(double *)$1->pValue = $3;
                                            } else {
                                              $1->pValue = (int *) malloc(sizeof(int));
                                              $$ = *(int *)$1->pValue = $3;
                                            }
                                          }
          ;
%%

int main(void) {
  init();
  yyparse();
  installDefaultSymbols();
  return 0;
}

void yyerror(char *s) {
  if(s == NULL) { // S'il n'y a pas de message transmis, on affiche le message par défaut
    printf("hoc: %d\t syntax error\n", lineNumber);
  } else { // Sinon, on affiche simplement "hoc" et le nombre de ligne d'abord
    printf("hoc: %d\t %s\n", lineNumber, s);
  }
}

void init(void) {
  // On réinitialise tout
  printf("hoc %d>", lineNumber);
  isFloat = 0;
}

void promptResult(float val) {
  // On affiche le résultat en fonction du type de donnée
  if (isFloat) printf("=%f\n", val); // Si c'est un float
  else printf("=%d\n", (int)val); // sinon, c'est un entier
}
