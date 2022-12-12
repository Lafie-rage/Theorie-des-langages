/**
 *	\file		code.c
 *	\brief	GESTION DES PILE DE DONNEES ET TABLE DE CODES
 *	\date		10 déc 2022
 *	\author	Corentin Destrez
 */

#define _CODE_C_
#include "hoc.h"

// Pile de données
static data_t pile[MAX_PILE];
static data_t *pilePtr = pile;

void push(data_t d)
{
	if (pilePtr >= &pile[MAX_PILE])
		printMessageTag(17);
	*pilePtr++ = d;
}

data_t pop(void)
{
	data_t d;
	if (pilePtr <= pile)
		printMessageTag(18);
	d = *--pilePtr;
	return d;
}

// Table de code
static instr_t prog[MAX_PROG];
static instr_t *progPtr;

instr_t *code(instr_t frame)
{
	instr_t *adr = progPtr;
	if (progPtr >= &prog[MAX_PROG])
		printMessageTag(19);
	*progPtr++ = frame;
#ifdef DBG_CODE
	printf("Debug code %p\n", frame);
#endif
	return adr;
}

extern int isFloat; // Nature de l'expression en cous d'analyse

extern int myError;

#include <stdio.h>

void execute(instr_t *p)
{
	for (PC = p; *PC != STOP;)
	{
		(*(*PC++))();
		if (myError)
			break;
	}
}

void initCode(void)
{
	pilePtr = pile;
	progPtr = prog;
	PC = prog;
	isFloat = 0;
	myError = 0;
	prompt();
}
