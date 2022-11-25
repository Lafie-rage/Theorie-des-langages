%{
    #include "symbol.h" // Récupération de la struct symbole et ses fonctions
    #include "calc.tab.h" // Récupération de la table des token défini dans calc.y
    extern int lineNumber; // Nombre de lignes, récupéré depuis calc.y
%}
/* Pattern des nombre entiers */
Entier      0|[1-9][0-9]*
/* Pattern des nombre réel */
Reel        [0-9]*\.[0-9]+
/* Pattern du retour chariot */
Nl          \n
/* Pattern des noms de variables */
Var         [_a-zA-Z][a-zA-Z0-9\-]*
/* Pattern du mot clef "quit" */
QUIT        "quit".*
%%
{QUIT}      {printf("Bye !\n"); return 0;}; // On affiche quit si on quitte le programme
{Entier}    {yylval.dval = atoi(yytext); return NBR;}; // On affecte la valeur entière du nombre saisi. Cette valeur pourra être utilisée par yacc.
{Reel}      {yylval.fval = atof(yytext); return FLOAT;}; // On affecte la valeur réel du nombre saisi. Cette valeur pourra être utilisée par yacc.
{Nl}        {lineNumber++; return RC;}; // On incrémente le nombre de ligne;
{Var}       {
              symbol_t* mySp;
              // On vérifie si la variable a déjà été utilisée
              mySp = lookUpSymbol(yytext);
              if(mySp == SYMBOL_NULL) {
                // Si elle n'a jamais été utilisée, on la créé
                // Elle sera de type non défini par défaut
                mySp = installSymbol(yytext, UNDEF);
              }
              // on affecte le symbole entant que valeur utilisable par yacc.
              yylval.symb = mySp;
              return mySp->type;
            };
"+"         {return ADD;}; // region DEFINITION DES OPERATEURS
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
"!"         {return NOT;}; // endregion
.           ; // On ignore tous les autres caractères
<<EOF>>     {printf("Au revoir\n"); return 0;};
%%
