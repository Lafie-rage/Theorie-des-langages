/**
 *	\file		codeHoc.h
 *	\brief		G E N E R A T I O N   DE   C O D E
 *	\date		6 Février 2021
 *	\author		Samir El Khattabi
 *  \brief      Fichier d'implémentations pour la génération de code
 *              <LI> Symboles Numériques : nombres, constantes, variables</LI>
 *              <LI> Opérations Algébriques</LI>
 *              <LI> Appels Fonctions prédéfinies</LI>
 *              <LI> Affichage résultat</LI>
 */
#ifndef _CODE_HOC_H_
#define _CODE_HOC_H_
/******************************************************************************/
/**
 *	\part	S Y M B O L E S   N U M E R I Q U E S 
 */
/**
 *  \fn         void intPush(void);
 *  \brief      Empiler la valeur d'un entier sur la pile d'exécution
 */
void intPush(void);
/******************************************************************************/
/**
 *  \fn         void floPush(void);
 *  \brief      Empiler la valeur d'un réel sur la pile d'exécution
 */
void floPush(void);
/******************************************************************************/
/**
 *  \fn         void varPush(void);
 *  \brief      Empiler le symbole adressant une variable sur la pile d'exécution
 */
void varPush(void);
/******************************************************************************/
/**
 *  \fn         void varEval(void);
 *  \brief      Dépiler le symbole se trouvant au sommet de la pile d'exécution
 *              et empiler sa valeur
 */
void varEval(void);
/******************************************************************************/
/**
 *	\part	O P E R A T I O N S   A L G E B R I Q U E S
 */
/**
 *  \fn         void add(void);
 *  \brief      Dépiler les deux nombres se trouvant au sommet de la pile
 *              d'exécution, effectuer une addition et empiler le résultat
 */
void add(void);
/**
 *  \fn         void sub(void);
 *  \brief      Dépiler les deux nombres se trouvant au sommet de la pile
 *              d'exécution, effectuer une soustraction et empiler le résultat
 */
void sub(void);
/**
 *  \fn         void mul(void);
 *  \brief      Dépiler les deux nombres se trouvant au sommet de la pile
 *              d'exécution, effectuer une multiplication et empiler le résultat
 */
void mul(void);
/**
 *  \fn         void Div(void);
 *  \brief      Dépiler les deux nombres se trouvant au sommet de la pile
 *              d'exécution, effectuer une division et empiler le résultat
 */
void Div(void);
/**
 *  \fn         void power(void);
 *  \brief      Dépiler les deux nombres se trouvant au sommet de la pile
 *              d'exécution, effectuer une élévation à la puissance et empiler
 *              le résultat
 */
void negate(void);
/******************************************************************************/
/**
 *	\part	A F F I C H A G E 
 */
/**
 *  \fn         void printExprCode(void);
 *  \brief      Dépiler le nombre se trouvant au sommet de la pile et l'afficher
 */
void printExprCode(void);

#endif /* _CODE_HOC_H_ */
