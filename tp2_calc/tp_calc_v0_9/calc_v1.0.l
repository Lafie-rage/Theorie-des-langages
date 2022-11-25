%{
    #include "symbol.h" // Récupération de la struct symbole et ses fonctions
    #include "calc.tab.h" // Récupération de la table des token défini dans calc.y
    extern int lineNumber; // Nombre de lignes, récupéré depuis calc.y
%}
Entier      0|[1-9][0-9]*
Reel        [0-9]*\.[0-9]+
Nl          \n
Var         [_a-zA-Z][a-zA-Z0-9\-]*
QUIT        "quit".*
%%
{QUIT}      {printf("Bye !\n"); return 0;};
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
"=="        {return EQ;};
"!="        {return N_EQ;};
">"         {return SUP;};
">="        {return SUP_EQ;};
"<"         {return INF;};
"<="        {return INF_EQ;};
"&&"        {return AND;};
"||"        {return OR;};
.           ;
<<EOF>>     {printf("Au revoir\n"); return 0;};
%%
