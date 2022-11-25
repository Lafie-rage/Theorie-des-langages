%{
  #include <stdio.h>
  #include "symbol.h"
  int yylex(void);
  void yyerror(char *);
  void init(void);
  void promptResult(float);
  int isFloat = 0;
  int lineNumber = 0;
%}
%start  list
%union {
  int dval;
  float fval;
  pSymbol_t symb;
}
%token RC ADD SUB MUL DIV PO PF AFF EQ N_EQ SUP SUP_EQ INF INF_EQ AND OR NOT
%token <dval> NBR // On est obligé de les typer
%token <fval> FLOAT
%token <symb> UNDEF IVAR FVAR
%type  <fval>  expr val
%left ADD SUB MUL DIV AND OR NOT
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
          | expr ADD val                  {$$ = $1 + $3;}
          | expr SUB val                  {$$ = $1 - $3;}
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
          | expr OR val                   {
                                            $$ = $1 || $3;
                                            // On passe l'expression entant que non float, pour qu'il affiche 0 ou 1 simplement
                                            isFloat = 0;
                                          }
          | expr AND val                  {$$ = $1 && $3; isFloat = 0;}
          | expr EQ val                   {$$ = $1 == $3; isFloat = 0;}
          | expr N_EQ val                 {$$ = $1 != $3; isFloat = 0;}
          | expr SUP val                  {$$ = $1 > $3; isFloat = 0;}
          | expr SUP_EQ val               {$$ = $1 >= $3; isFloat = 0;}
          | expr INF val                  {$$ = $1 < $3; isFloat = 0;}
          | expr INF_EQ val               {$$ = $1 <= $3; isFloat = 0;}
          | NOT expr                      {$$ = !($2);}
          ;

  val     : NBR                           {$$ = $1;}
          | IVAR                          {
                                            $$ =  $1->U.iVal;
                                          }
          | FVAR                          {
                                            $$ =  $1->U.dVal;
                                            isFloat = 1;
                                          }
          | UNDEF                         {$$ = $1->U.dVal;}
          | FLOAT                         {$$ = $1; isFloat = 1;}
          ;

  assign  : IVAR AFF expr                 {
                                            if(isFloat){
                                              yyerror("Incompatible cast : Trying to cast float to integer");
                                              YYERROR;
                                            }
                                            else $1->U.iVal = $3;
                                          }
          | FVAR AFF expr                 {
                                            if(isFloat) {
                                              $1->U.dVal = $3; isFloat=1;
                                              isFloat = 1;
                                            } else {
                                              $1->U.iVal = $3;
                                            }
                                          }
          | UNDEF AFF expr                {
                                            if(isFloat) {
                                              $1->U.dVal = $3;
                                              $1->type=FVAR;
                                              isFloat = 1;
                                            } else {
                                              $1->U.iVal = $3;
                                              $1->type=IVAR;
                                            }
                                          }
          ;
%%

int main(void) {
  init();
  yyparse();
  return 0;
}

void yyerror(char *s) {
  if(s == NULL) { // S'il n'y a pas de message transmis, on affiche le message par défaut
    printf("calc: %d\t syntax error\n", lineNumber);
  } else { // Sinon, on affiche simplement "calc" et le nombre de ligne d'abord
    printf("calc: %d\t %s\n", lineNumber, s);
  }
}

void init(void) {
  // On réinitialise tout
  printf("Calc %d>", lineNumber);
  isFloat = 0;
}

void promptResult(float val) {
  // On affiche le résultat en fonction du type de donnée
  if (isFloat) printf("=%f\n", val); // Si c'est un float
  else printf("=%d\n", (int)val); // sinon, c'est un entier
}
