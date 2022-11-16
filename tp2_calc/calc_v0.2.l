%%
0|[1-9][0-9]*    {printf("Chiffre %s\n", yytext); return 256;};
"+"    {printf("Addition\n"); return 257;};
"-"    {printf("Soustraction\n"); return 258;};
.    ;
<<EOF>>    {printf("Au revoir\n"); return 0;};
%%
