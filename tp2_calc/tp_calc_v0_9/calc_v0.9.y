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
%token  RC ADD SUB MUL DIV PO PF AFF
%token <dval> NBR // On est obligé de les typer
%token <fval> FLOAT
%token <symb> UNDEF IVAR FVAR
%type   <fval>  expr val
%left ADD SUB MUL DIV
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
          ;

  val     : NBR                           {$$ = $1;}
          | IVAR                          {
                                            $$ =  $1->U.iVal;
                                          }
          | FVAR                          {
                                            $$ =  $1->U.dVal;
                                            isFloat = 1;
                                          }
          | FLOAT                         {$$ = $1; isFloat = 1;}
          ;

  assign  : IVAR AFF expr                 {$1->U.iVal = $3;}
          | FVAR AFF expr                 {$1->U.dVal = $3;}
          ;
%%

int main(void) {
  init();
  yyparse();

  return 0;
}

void yyerror(char *s) {
  if(s == NULL) {
    printf("calc: %d\t syntax error\n", lineNumber);
  } else {
    printf("calc %d\t %s\n", lineNumber, s);
  }
}

void init(void) {
  printf("Calc %d>", lineNumber);
  isFloat = 0;
}

void promptResult(float val) {
  if (isFloat) printf("=%f\n", val);
  else printf("=%d\n", (int)val);
}
