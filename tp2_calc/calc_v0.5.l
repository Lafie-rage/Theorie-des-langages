%{
    #include "calc.tab.h"
%}
Entier      0|[1-9][0-9]*
Reel        [0-9]*\.[0-9]+
minus       [a-z]
majus       [A-Z]
Nl          \n
%%
{Entier}    {yylval.dval = atoi(yytext); return NBR;};
{Reel}      {yylval.fval = atof(yytext); return FLOAT;};
{Nl}        {return RC;};
{minus}     {yylval.dval = yytext[0]-'a'; return ACC;};
{majus}     {yylval.dval = yytext[0]-'A'; return ACC_F;};
"+"         {return ADD;};
"-"         {return SUB;};
"="         {return AFF;};
.           ;
<<EOF>>     {printf("Au revoir\n"); return 0;};
%%
