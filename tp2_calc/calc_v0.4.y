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
          | list expr RC      {printf("=%d\nCalc>", $2);}
          | list assign RC    {printf("Calc>");}
          | list RC
          ;

  expr    : val
          | expr ADD val      {$$ = $1 + $3;}
          | expr SUB val      {$$ = $1 - $3;}
          ;

  val     : NBR               {$$ = $1;}
          | ACC               {$$ = acc[$1];}
          ;

  assign  : ACC AFF expr      {acc[$1] = $3;}
          ;
%%

int main(void) {
  printf("Calc >");
  yyparse();
  return 0;
}
