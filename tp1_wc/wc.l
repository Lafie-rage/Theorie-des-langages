%%
        int row_count=0;
        int carac_count=0;
\n          {row_count++;};
.    {carac_count++;};
<<EOF>>       {printf("carac: %d, rows : %d\n", carac_count, row_count);}; return 0;
%%

int main(int argc, char **argv) {
    if(argc < 2) {
        printf("usage : %s filenameToBeAnalysed\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if(yyin = fopen(argv[1], "r")) yylex();
    else {
        printf("Erreur d'ouverture de %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
