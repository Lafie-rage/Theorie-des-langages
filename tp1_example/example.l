entier    [0-9]+
nl    \n
sortie    (quit|exit|ciao|bye)
test      ("A bientôt")

%%
{entier}    {ECHO; printf(" ");};
{nl}        {ECHO; printf("- ");};
{sortie}     {printf("Au revoir\n"); return 0; };
{test}      {printf("Test test test");};
.
%%

main(){
    yylex();
}
