#define _CODE_HOC_C_
#include "hoc.h"

void intPush() {
  data_t d;
  d.value = *(int *)(((pSymbol_t) *PC++)->U.pValue);
  push(d);
}

void floPush() {
  data_t d;
  isFloat = 1;
  d.value = *(double *)(((pSymbol_t) *PC++)->U.pValue);
  push(d);
}

void nbrPush() {
  data_t d;
  d.value = *(int *)(((pSymbol_t) *PC++)->U.pValue);
  push(d);
}

void varPush() {
  data_t d:
  d.pSymb = ((pSymbol_t) *PC++);


  if (d.pSymb->clas!=VAR) {
      exeError("EXEC-E-301: varPush -- [%s] is not a variable", d.pSymb->name);
  }
}

void evalVar() {
  data_t d;
  d = pop();
  isFloat = d.pSymb->type == FVAR;
  if(d.pSymb->type == UNDEF)
    exeError("EXEC-E-301: varPush -- [%s] is not a variable", d.pSymb->name);
  push(d);
}

void assignVar() {

}

void predef() {

}


void add() {
  data_t d2 = pop(), d1 = pop();
  d1.value = d1.value + d2.value;
  push(d1);
}

void sub() {
  data_t d2 = pop(), d1 = pop();
  d1.value = d1.value - d2.value;
  push(d1);
}

void mul() {
  data_t d2 = pop(), d1 = pop();
  d1.value = d1.value * d2.value;
  push(d1);
}

void myDiv() {
  data_t d2 = pop(), d1 = pop();
  if(d2.vlaue == 0) exeError("FPE***Division par zéro");
  else {
    d1.value = d1.value / d2.value;
    push(d1);
  }
}
