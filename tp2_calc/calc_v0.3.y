%{
#include <stdio.h>
int yylex(void);
void yyerror(char *);
%}

%start list
%token NBR
%%
list  :
      | list expr '\n'
      | list '\n'
      ;
expr  : NBR'+'NBR {printf("Addition\n");}
      | NBR'-'NBR {printf("Soustraction\n");}
      ;
%%

main() {
  yyparse();
}
