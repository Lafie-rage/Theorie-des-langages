typedef struct symbol {
  char* name;
  short type;
  union {
    int iVal;
    double dVal;
  }U;
  struct symbol* next;
} symbol_t;

typedef struct symbol* pSymbol_t;

#define SYMBOL_NULL ((pSymbol_t) 0)

symbol_t* installSymbol(char* tokenName, short tokenType);

symbol_t* lookUpSymbol(const char* tokenName);
