/**
 *  \struct generic
 *  \brief Définition du type de données générique.
 */
typedef void* generic;

/**
 *  \typdef symbol_t
 *  \brief Définition du type de données "symbole" de type struct
 */
typedef struct symbol {
  char *name;             // Nom du symbole : identifiant
  short class;            // Classe du symbole : VAL, CST, VAR
  short type;             // Type dy symbole : ENTIER, REEL, UNDEF
  generic pValue;         // Pointeur générique sur la valeur du symbole
  short size;             // Taille mémoire occupée par la valeur
  struct symbol *next;    // Pointeur sur symbole suivant;
} symbol_t;

typedef struct symbol* pSymbol_t;

#define SYMBOL_NULL ((pSymbol_t) 0)

symbol_t* installSymbol(char * tokenName, short tokenClass, short tokenType, short tokenSize, generic tokenPtrValue);

symbol_t* lookUpSymbol(const char* tokenName);
