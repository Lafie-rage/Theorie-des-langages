/**
 *	\file		codeHoc.h
 *	\brief	GESTION DES OPERATEURS
 *	\date		10 déc 2022
 *	\author	Corentin Destrez
 */

#ifndef _CODE_HOC_H_
#define _CODE_HOC_H_

void intPush(void);
void floPush(void);
void varPush(void);
void varEval(void);
void varAssign(void);

void add(void);
void sub(void);
void mul(void);
void Div(void);
void negate(void);
void power(void);
void predef(void);

void printExprCode(void);

#endif /* _CODE_HOC_H_ */
