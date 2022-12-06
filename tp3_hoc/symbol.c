#define SYMBOL_C_C
#include "hoc.h"

static pSymbol_t _symbolList=SYMBOL_NULL;

/**
 *  \fn symbol_t* installSymbol(char * tokenName, short tokenClass, short tokenSize, generic pValue)
 *  \brief Insérer un nouveau symbole en tête de la liste des symboles.
 *
 *  \return Pointeur sur le symbole inséré.
 */
symbol_t* installSymbol(char * tokenName, short tokenClass, short tokenType, short tokenSize, generic tokenPtrValue) {
  symbol_t* mySp = (symbol_t *) malloc(sizeof(symbol_t));
  mySp->class = tokenClass;
  mySp->type = tokenType;
  mySp->size = tokenSize;
  mySp->pValue = tokenPtrValue;
  mySp->name = NULL;
  if(tokenName != NULL) {
    mySp->name = (char *) malloc(strlen(tokenName)+1);
    strcpy(mySp->name, tokenName);
  }
  mySp->next = _symbolList;
  _symbolList = mySp;
  return mySp;
}

symbol_t* lookUpSymbol(const char* tokenName) {
  symbol_t* mySp = _symbolList;
  for(; mySp != SYMBOL_NULL; mySp = mySp->next) {
    if(strcmp(mySp->name, tokenName) == 0) return mySp;
  }
  return SYMBOL_NULL;
}

#include "defSymbols.c"
