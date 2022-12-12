#define _CODE_HOC_C_
#include "hoc.h"
#include <stdio.h>
extern int isFloat;

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

void varPush() {
  data_t d;
  d.pSymb = ((pSymbol_t) *PC++);


  if (d.pSymb->clas!=VAR) {
      exeError("EXEC-E-301: varPush -- [%s] is not a variable", d.pSymb->name);
  }
  push(d);
}

void evalVar() {
  data_t d;
  data_t result;
  d = pop();
  isFloat = d.pSymb->type == FVAR;
  if(d.pSymb->type == UNDEF)
    exeError("EXEC-E-301: varPush -- [%s] is not a variable", d.pSymb->name); // Sem
  if(isFloat) {
    d.value = *(double *)(d.pSymb->U.pValue);
    #ifdef DBG_CODE
      printf("Var '%s' value evaluated as a float : %f\n", d.pSymb->name, (double) d.value);
    #endif
  }
  else {
    d.value = *(int *)(d.pSymb->U.pValue);
    #ifdef DBG_CODE
      printf("Var '%s' value evaluated as an integer : %d\n", d.pSymb->name, (int) d.value);
    #endif
  }
  push(d);
}

void assignVar() {
  data_t d1 = pop(), d2 = pop();
	if (d1.pSymb->clas != VAR)
		exeError("[%s] is not a variable, can't assign", d1.pSymb->name); // Sem
	else if (d1.pSymb->type == IVAR)
		*(int *)(d1.pSymb->U.pValue) = (int)d2.value;
	else if (d1.pSymb->type == FVAR)
		*(double *)(d1.pSymb->U.pValue) = d2.value;
	else
	{ // UNDEF
		d1.pSymb->type = (isFloat) ? FVAR : IVAR;
		d1.pSymb->size = (isFloat) ? sizeof(double) : sizeof(int);
		if (isFloat) {
			d1.pSymb->U.pValue = (generic) allocFlo(d2.value);
      #ifdef DBG_CODE
        printf("Var '%s' value after assignment of float value : %f\n", d1.pSymb->name, *(double * )(d1.pSymb->U.pValue));
      #endif
    }
		else {
      d1.pSymb->U.pValue = (generic) allocInt((int)d2.value);
      #ifdef DBG_CODE
        printf("Var '%s' value after assignment of integer value : %d\n", d1.pSymb->name, *(int *)(d1.pSymb->U.pValue));
      #endif
    }
	}
	push(d2);
}

void predef() {
  data_t d = pop();
  d.value = (*(pFctMath_t)((pSymbol_t)*PC++)->U.pFct)(d.value);
  push(d);
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
  if(d2.value == 0) exeError("FPE***Division par zéro"); // Exec
  #ifdef DBG_CODE
    if(d1.pSymb->type == FVAR) {
      printf("First value is a float and is : %f\n", (double)(d1.value));
    } else {
      printf("First value is a integer and is : %d\n", (int)(d1.value));
    }
    if(d2.pSymb->type == FVAR) {
      printf("Second value is a float and is : %f\n", (double)(d2.value));
    } else {
      printf("Second value is an integer and is : %d\n", (int)(d2.value));
    }
  #endif
  d1.value = d1.value / d2.value;
  push(d1);
}

void negate() {
  data_t d = pop();
  if(d.value != 0) d.value = -(d.value);
  push(d);
}

void power() {
  data_t d2 = pop(), d1 = pop();
  d1.value = pow(d1.value, d2.value);
  push(d1);
}

void printExprCode(void) {
  data_t d = pop();
  printExpr(isFloat, d.value);
}
