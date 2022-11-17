%{
  #include "calc.tab.h"
%}

%%
0|[1-9][0-9]*    {return NBR;};
"+"|"-"          {return yytext[0];};
.     ;
\n    ;
<<EOF>>    {printf("Au revoir\n"); return 0;};
%%
