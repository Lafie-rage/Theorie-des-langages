%{
  #include <stdio.h>
  int yylex(void);
  void yyerror(char *);
  int acc[26]= {0};
%}
%start  list
%token  NBR RC ADD SUB ACC AFF

%%
  list    : // vide
          | list expr RC    {printf("=%d\nCalc>", $2);}
          | list assign RC  {printf("Calc>");}
          | list RC
          ;
  expr    : NBR             {$$ = $1;} // En réalité, c'est déjà le traitement par défaut
          | ACC             {$$ = acc[$1];}
          | NBR ADD NBR     {$$ = $1 + $3;}
          | NBR SUB NBR     {$$ = $1 - $3;}
          ;

  assign  : ACC AFF expr    {acc[$1] = $3;}
          ;
%%

int main(void) {
  printf("Calc >");
  yyparse();
  return 0;
}
