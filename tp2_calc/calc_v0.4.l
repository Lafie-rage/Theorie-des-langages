%{
    #include "calc.tab.h"
%}
Entier      0|[1-9][0-9]*
minus       [a-z]
Nl          \n
%%
{Entier}    {yylval = atoi(yytext); return NBR;};
{Nl}        {return RC;};
{minus}       {yylval=yytext[0]-'a'; return ACC;};
"+"         {return ADD;};
"-"         {return SUB;};
"="         {return AFF;};
.           ;
<<EOF>>     {printf("Au revoir\n"); return 0;};
%%
