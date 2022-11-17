%{
  #include <stdio.h>
  int yylex(void);
  void yyerror(char *);
%}
%start  list
%token  NBR   RC  ADD SUB

%%
  list  : // vide
        | list expr RC    {printf("=%d\n", $2);}
        | list RC
        ;
  expr  : NBR             {$$ = $1;} // En réalité, c'est déjà le traitement par défaut
        | NBR ADD NBR     {$$ = $1 + $3;}
        | NBR SUB NBR     {$$ = $1 - $3;}
        ;
%%

int main(void) {
  puts("Calc >");
  yyparse();
  return 0;
}
