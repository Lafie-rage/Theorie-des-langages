/**
 *	\file		codeHoc.c
 *	\brief	GESTION DES OPERATEURS
 *	\date		10 déc 2022
 *	\author	Corentin Destrez
 */

#define _CODE_HOC_C_
#include "hoc.h"
extern int isFloat;

void intPush(void)
{
	data_t d;
	d.value = *(int *)(((pSymbol_t)*PC++)->U.pValue);
	push(d);
}

void floPush(void)
{
	data_t d;
	isFloat = 1;
	d.value = *(double *)((pSymbol_t)*PC++)->U.pValue;
	push(d);
}

void varPush(void)
{
	data_t d;
	d.pSymb = ((pSymbol_t)*PC++);

	if (d.pSymb->clas != VAR)
		exeError("EXEC-E-301: varPush -- [%s] is not a variable", d.pSymb->name);
	push(d);
}

void varEval(void)
{
	data_t d;
	d = pop();
	isFloat = d.pSymb->type == FVAR;
	if (d.pSymb->type == UNDEF)
		exeError("EXEC-E-302: varEval -- [%s] is undefined variable", d.pSymb->name);
	else if (isFloat)
		d.value = *(double *)(d.pSymb->U.pValue);
	else
		d.value = *(int *)(d.pSymb->U.pValue);
	push(d);
}

void varAssign(void)
{
	data_t d1 = pop(), d2 = pop();
	if (d1.pSymb->clas != VAR)
		exeError("[%s] is not a variable, can't assign", d1.pSymb->name);
	else if (d1.pSymb->type == IVAR)
		*(int *)(d1.pSymb->U.pValue) = (int)d2.value;
	else if (d1.pSymb->type == FVAR)
		*(double *)(d1.pSymb->U.pValue) = d2.value;
	else
	{ // UNDEF
		d1.pSymb->type = (isFloat) ? FVAR : IVAR;
		d1.pSymb->size = (isFloat) ? sizeof(double) : sizeof(int);
		if (isFloat)
			d1.pSymb->U.pValue = allocFlo(d2.value);
		else
			d1.pSymb->U.pValue = allocInt((int)d2.value);
	}
	push(d2);
}



void add(void)
{
	data_t d2 = pop(), d1 = pop();
	d1.value = d1.value + d2.value;
	push(d1);
}

void sub(void)
{
	data_t d2 = pop(), d1 = pop();
	d1.value = d1.value - d2.value;
	push(d1);
}

void mul(void)
{
	data_t d2 = pop(), d1 = pop();
	d1.value = d1.value * d2.value;
	push(d1);
}

void Div(void)
{
	data_t d2 = pop(), d1 = pop();
	if (d2.value == 0.0)
		exeError("FPE***Division par zéro");
	d1.value = d1.value / d2.value;
	push(d1);
}

void negate(void)
{
	data_t d = pop();
	d.value = -d.value;
	push(d);
}

void power(void)
{
	data_t d2 = pop(), d1 = pop();
	d1.value = pow(d1.value, d2.value);
	push(d1);
}


void predef(void)
{
	data_t d = pop();
	d.value = (*(pFctMath_t)((pSymbol_t)*PC++)->U.pFct)(d.value);
	push(d);
}

void printExprCode(void)
{
	data_t d = pop();
	printExpr(isFloat, d.value);
}
