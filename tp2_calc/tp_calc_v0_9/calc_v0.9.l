%{
    #include "symbol.h"
    #include "calc.tab.h"
    extern int lineNumber;
%}
Entier      0|[1-9][0-9]*
Reel        [0-9]*\.[0-9]+
Nl          \n
Var         _?[a-zA-Z][a-zA-Z0-9\-]*
%%
{Entier}    {yylval.dval = atoi(yytext); return NBR;};
{Reel}      {yylval.fval = atof(yytext); return FLOAT;};
{Nl}        {lineNumber++; return RC;};
{Var}       {
              symbol_t* mySp;
              mySp = lookUpSymbol(yytext);
              if(mySp == SYMBOL_NULL) {
                mySp = installSymbol(yytext, UNDEF);
              }
              yylval.symb = mySp;
              return mySp->type;
            };
"+"         {return ADD;};
"-"         {return SUB;};
"*"         {return MUL;};
"/"         {return DIV;};
"("         {return PO;};
")"         {return PF;};
"="         {return AFF;};
.           ;
<<EOF>>     {printf("Au revoir\n"); return 0;};
%%
