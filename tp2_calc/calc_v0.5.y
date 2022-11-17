%{
  #include <stdio.h>
  int yylex(void);
  void yyerror(char *);
  int acc[26]= {0};
  float accf[26] = {0};
  int isFloat = 0;
%}
%start  list
%union {
  int dval;
  float fval;
}
%token  RC ADD SUB AFF
%token <dval> NBR ACC_F ACC // On est obligé de les typer
%token <fval> FLOAT
%type   <fval>  expr val
%%
  list    : // vide
          | list expr RC      {
                                if (isFloat) printf("=%f\nCalc>", $2);
                                else printf("=%d\nCalc>", (int)$2);
                                isFloat = 0;
                              }
          | list assign RC    {printf("Calc>");}
          | list RC
          ;

  expr    : val
          | expr ADD val      {$$ = $1 + $3;}
          | expr SUB val      {$$ = $1 - $3;}
          ;

  val     : NBR               {$$ = $1;}
          | ACC               {$$ = acc[$1];}
          | ACC_F             {$$ = accf[$1]; isFloat = 1;}
          | FLOAT             {$$ = $1; isFloat = 1;}
          ;

  assign  : ACC AFF expr      {acc[$1] = $3;}
          | ACC_F AFF expr    {accf[$1] = $3;}
          ;
%%

int main(void) {
  printf("Calc >");
  yyparse();
  return 0;
}
