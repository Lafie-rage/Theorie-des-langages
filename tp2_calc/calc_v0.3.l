%{
    #include "calc.tab.h"
%}
Entier      0|[1-9][0-9]*
Nl          \n
%%
{Entier}    {yylval = atoi(yytext); return NBR;};
{Nl}        {return RC;};
"+"         {return ADD;};
"-"         {return SUB;};
.           ;
<<EOF>>     {printf("Au revoir\n"); return 0;};
%%
