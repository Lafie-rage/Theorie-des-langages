%{
  #include "calc.tab.h"
%}

%%
0|[1-9][0-9]*    {return NBR;};
"+"|"-"|\n          {return yytext[0];};
.     ;
<<EOF>>    {printf("Au revoir\n"); return 0;};
%%
