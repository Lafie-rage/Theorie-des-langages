
/**
 *	\file		codeHoc.c
 *	\brief		G E N E R A T I O N   DE   C O D E
 *	\date		6 Février 2021
 *	\author		Samir El Khattabi
 *  \brief      Fichier d'implémentations pour la génération de code
 *              <LI> Symboles Numériques : nombres, constantes, variables</LI>
 *              <LI> Opérations Algébriques</LI>
 *              <LI> Appels Fonctions prédéfinies</LI>
 *              <LI> Affichage résultat</LI>
 */
#define _CODE_HOC_C_
#include "hoc.h"
extern int isFloat;
/******************************************************************************/
/**
 *	\part	S Y M B O L E S   N U M E R I Q U E S 
 */
/**
 *  \fn         void intPush(void);
 *  \brief      Empiler la valeur d'un entier sur la pile d'exécution
 */
void intPush(void) {
	data_t d;
	d.value = *(int*) (((pSymbol_t) *PC++)->U.pValue);
	push(d);
}
/******************************************************************************/
/**
 *  \fn         void floPush(void);
 *  \brief      Empiler la valeur d'un réel sur la pile d'exécution
 */
void floPush(void) {
	data_t d;
	isFloat = 1;
	d.value = *(double*) ((pSymbol_t) *PC++)->U.pValue;
	push(d);
}
/******************************************************************************/
/**
 *  \fn         void varPush(void);
 *  \brief      Empiler le symbole adressant une variable sur la pile d'exécution
 */
void varPush(void) {
	data_t d;	
	d.pSymb = ((pSymbol_t) *PC++);
	
	if (d.pSymb->type!=IVAR && d.pSymb->type!=FVAR &&
		d.pSymb->type!=ENTIER && d.pSymb->type!=REEL &&
		d.pSymb->type!=UNDEF)
		exeError("EXEC-E-301: varPush -- [%s] is not a variable",d.pSymb->name);
	push(d);
}
/******************************************************************************/
/**
 *  \fn         void varEval(void);
 *  \brief      Dépiler le symbole se trouvant au sommet de la pile d'exécution
 *              et empiler sa valeur
 */
void varEval(void) {
	data_t d = pop();
	if (d.pSymb->type == UNDEF)
		exeError("EXEC-E-302: varEval -- [%s] is undefined variable",d.pSymb->name);
	else if (d.pSymb->type == IVAR) d.value = *(int*) (((pSymbol_t) *PC++)->U.pValue);
		 else d.value = *(double*) (((pSymbol_t) *PC++)->U.pValue);
	push(d);
}
/******************************************************************************/
/**
 *	\part	O P E R A T I O N S   A L G E B R I Q U E S
 */
/**
 *  \fn         void add(void);
 *  \brief      Dépiler les deux nombres se trouvant au sommet de la pile
 *              d'exécution, effectuer une addition et empiler le résultat
 */
void add(void) {
	data_t d2 = pop(), d1 = pop();
	d1.value = d1.value + d2.value;
	push(d1);
}
/******************************************************************************/
/**
 *  \fn         void sub(void);
 *  \brief      Dépiler les deux nombres se trouvant au sommet de la pile
 *              d'exécution, effectuer une soustraction et empiler le résultat
 */
void sub(void) {
	data_t d2 = pop(), d1 = pop();
	d1.value = d1.value - d2.value;
	push(d1);
}
/******************************************************************************/
/**
 *  \fn         void mul(void);
 *  \brief      Dépiler les deux nombres se trouvant au sommet de la pile
 *              d'exécution, effectuer une multiplication et empiler le résultat
 */
void mul(void) {
	data_t d2 = pop(), d1 = pop();
	d1.value = d1.value * d2.value;
	push(d1);
}
/******************************************************************************/
/**
 *  \fn         void Div(void);
 *  \brief      Dépiler les deux nombres se trouvant au sommet de la pile
 *              d'exécution, effectuer une division et empiler le résultat
 */
void Div(void) {
	data_t d2 = pop(), d1 = pop();
	if (d2.value == 0.0)
		exeError("FPE***Division par zéro");
	d1.value = d1.value / d2.value;
	push(d1);
}
/******************************************************************************/
/**
 *  \fn         void negate(void);
 *  \brief      Dépiler les deux nombres se trouvant au sommet de la pile
 *              d'exécution, inverser le signe et empiler le résultat
 */
void negate(void) {
	data_t d = pop();
	d.value = - d.value;
	push(d);
}
/******************************************************************************/
/**
 *	\part	A F F I C H A G E 
 */
/**
 *  \fn         void printExprCode(void);
 *  \brief      Dépiler le nombre se trouvant au sommet de la pile et l'afficher
 */
void printExprCode(void) {
	data_t d = pop();
	printExpr(isFloat, d.value);
}
/*------\\//------\\//------\\//------\\//------\\//------\\//------\\/ F I N */
