%{
  #include <stdio.h>
  int yylex(void);
  void yyerror(char *);
  void init(void);
  void promptResult(float);
  int acc[26]= {0};
  float accf[26] = {0};
  int isFloat = 0;
  int lineNumber = 0;
%}
%start  list
%union {
  int dval;
  float fval;
}
%token  RC ADD SUB MUL DIV PO PF AFF
%token <dval> NBR ACC_F ACC // On est obligé de les typer
%token <fval> FLOAT
%type   <fval>  expr val
%left ADD SUB MUL DIV
%nonassoc UMINUS
%%
  list    : // vide
          | list expr RC                  {
                                            promptResult($2);
                                            init();
                                          }
          | list assign RC                {init();}
          | list error RC                 {yyerrok;init();}// Rend les erreurs acceptables.
          | list RC
          ;

  expr    : val
          | expr ADD val                  {$$ = $1 + $3;}
          | expr SUB val                  {$$ = $1 - $3;}
          | SUB expr  %prec UMINUS        {$$ = -$2;}
          | PO expr PF                    {$$ = $2;}
          | expr MUL expr                 {$$ = $1 * $3;}
          | expr DIV expr                 {
                                            $$ = $1/$3;
                                          }
          ;

  val     : NBR                           {$$ = $1;}
          | ACC                           {$$ = acc[$1];}
          | ACC_F                         {$$ = accf[$1]; isFloat = 1;}
          | FLOAT                         {$$ = $1; isFloat = 1;}
          ;

  assign  : ACC AFF expr                  {acc[$1] = $3;}
          | ACC_F AFF expr                {accf[$1] = $3;}
          ;
%%

int main(void) {
  init();
  yyparse();

  return 0;
}

void yyerror(char *s) {
  if(s == NULL) {
    printf("calc: %d\t syntax error\n", lineNumber);
  } else {
    printf("calc %d\t %s\n", lineNumber, s);
  }
}

void init(void) {
  printf("Calc %d>", lineNumber);
  isFloat = 0;
}

void promptResult(float val) {
  if (isFloat) printf("=%f\n", val);
  else printf("=%d\n", (int)val);
}
