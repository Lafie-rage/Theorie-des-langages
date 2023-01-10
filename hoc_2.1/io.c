/**
 *	\file		io.c
 *	\brief		G E S T I O N   DES   S O R T I E S  &   E R R E U R S
 *	\date		26 Janvier 2021
 *	\author		Samir El Khattabi
 */
#define _IO_C_
#include "hoc.h"
/**
 *	\var        progName
 *	\brief		Nom du programme
 */
extern char *progName;
/**
 *	\var		lineNo
 *	\brief		Ligne courante
 *	\note		A déclarer avec l'attribut "extern" par les utilisateurs
 */
int lineNo = 0;
/******************************************************************************/

static struct {
	int code;
	short category;
	char *message;
} _error[] = {
		// Lexical errors
		LEX_ERR_UNK_WORD,		LEXICAL,		"Unkown Word : #%s#[%d]",
		LEX_ERR_UNK_OP, 		LEXICAL, 		"Unknow operator : #%s#[%d]",
		// Syntactic errors
		SYN_ERR_DEFAULT,		SYNTACTIC, 	"Syntax error [%d]",
		SYN_ERR_MULTI_OP,		SYNTACTIC, 	"An operator cannot be followed by another [%d]",
		// Semantic errors
		SEM_ERR_DIV_ZERO,		SEMANTIC,		"Illegal operation : dividing by 0 [%d]",
		// Execution errors
		EXE_ERR_NOT_VAR,		EXECUTION,	"%s -- [%s] is not a variable [%d]",
		EXE_ERR_UNDEF_VAR,	EXECUTION, 	"%s -- [%s] is undefined [%d]",
		0, 									0,					NULL
};

/**
 *	\part		G E S T I O N   DES  S O R T I E S
 */
/**
 *	\fn 		void prompt(void)
 *	\brief		Affichage du prompt et incrémentation de la ligne courante
 */
void prompt(void) {
	printMessage(10);
	lineNo++;
}
/**
 *	\fn 		void printExpr(int isFloat, double val)
 *	\brief		Affichage du résultat (val) d'une expression
 */
void printExpr(int isFloat, double val) {
    if (isFloat) printMessage(12, val);
    else printMessage(11,(int)val);
}
/**
 *	\fn 		void printMessage(int iMsg, ...)
 *	\brief		Affichage d'un message formaté prédéfini avec un style prédéfini
 *	\param		iMsg : indice dans _msgFmt[] qui fournit
 *					   le message formaté ainsi que son sytle
 */
void printMessage(int iMsg, ...) {
	va_list pArg;
		va_start(pArg, iMsg);
		prMsgFmtWithStyle(_msgFmt[iMsg].iStyle, _msgFmt[iMsg].msg, pArg);
	va_end(pArg);
}
/**
 *	\fn 		void printMessageTag(int iMsg, ...)
 *	\brief		Affichage d'un message formaté prédéfini et son TAG avec un style prédéfini
 *	\param		iMsg : indice dans _msgFmt[] qui fournit
 *					   le message formaté ainsi que son sytle
 */
void printMessageTag(int iMsg, ...) {
	va_list pArg;
		va_start(pArg, iMsg);
		prTagAndMsgFmtWithStyle(_msgFmt[iMsg].iStyle, _msgFmt[iMsg].msg, pArg);
	va_end(pArg);
}
/******************************************************************************/
/**
 *	\part		G E S T I O N   DES  E R R E U R S
 */
/**
 *	\fn			void yyerror(char *strErr, ...)
 *	\brief		Fonction de gestion des erreurs de syntaxe
 *	\note		invoquée automatiquement par yyparse() sur l'unité syntaxique "error"
 *	\note		peut être invoquée explicitement
 */
void yyerror(char *strErr, ...) {
	va_list pArg;
	va_start(pArg, strErr);
    	prTagAndMsgFmtWithStyle(5, strErr, pArg);
	va_end(pArg);
	printLn();
    //printMessageTag(47, strErr);
}

char *getErrorMessageFromMyError(int myerror) {
	int i;
	for(i = 0; _error[i].code != 0; i++) {
		if(_error[i].code == myerror) return _error[i].message;
	}
}

/**
 *	\fn			void lexError(const char* strErr, ...)
 *	\brief		Fonction de gestion des erreurs lexicales
 *	\note		A invoquer explicitement depuis les règles de yylex()
 *	\note		Le prototype peut être adapté à votre besoin
 */
void lexError (int myerror, ...) {
	char *strErr = (char *)malloc(strlen(getErrorMessageFromMyError(myerror))+1);
	strcpy(strErr, getErrorMessageFromMyError(myerror));
	va_list pArg;
	va_start(pArg, myerror);
	prTagAndMsgFmtWithStyle(6, strErr, pArg);
	va_end(pArg);
	printLn();
	//printMessageTag(48, strErr);
}
/**
 *	\fn			void exeError (const char* strErr, ...)
 *	\brief		Fonction de gestion des erreurs d'exécution de fonctions importées,
 *	\note		comme les fonctions mathématiques prédéfinies (à base de errno),
 *	\note		et les futurs traitements qui seront implémentés
 *	\note		Le prototype peut être adapté à votre besoin
 */
void exeError (const char* strErr, ...) {
	va_list pArg;
	va_start(pArg, strErr);
		prTagAndMsgFmtWithStyle(7, strErr, pArg);
	va_end(pArg);
	printLn();
	//printMessageTag(49, strErr);
}
/******************************************************************************/
/**
 *	\part		G E S T I O N   DES  T R A C E S
 */
extern pSymbol_t  _symbolList;
/**
 *	\fn			void printSymbolList(void)
 *	\brief		Afficher une vue de la table des symboles définis
 */
void printSymbolList(void) {
	for (symbol_t *mySp = _symbolList; mySp != SYMBOL_NULL; mySp = mySp->next) {
		switch (mySp->clas) {
			case DAT :
				if (mySp->type == ENTIER) printMessage(61,*(int *) mySp->U.pValue);
				else if (mySp->type == REEL) printMessage(62,*(double *) mySp->U.pValue);
				else printMessage(67,mySp->name);
				break;
			case CST :
				if (mySp->type == ENTIER) printMessage(63, mySp->name, *(int *)(mySp)->U.pValue);
				else if (mySp->type == REEL) printMessage(64, mySp->name, *(double *)(mySp)->U.pValue);
				else if (mySp->type == UNDEF) printMessage(67,mySp->name);
				//else printMessage(67,mySp->name);
				break;
			case VAR :
				if (mySp->type == IVAR) printMessage(63, mySp->name, *(int *)(mySp)->U.pValue);
				else if (mySp->type == FVAR) printMessage(64,mySp->name, *(double *)(mySp)->U.pValue);
				else if (mySp->type == UNDEF) printMessage(67,mySp->name);
				//else printMessage(67,mySp->name);
				break;
			case PRG :
				if (mySp->type == PREDEF) printMessage(65,mySp->name);
				else printMessage(66,mySp->name); /* traitement des opérateurs : ADD, SUB, MUL et DIV, ... */
				//else printMessage(67,mySp->name);
				break;
			default  : printMessage(68);

		}
		printf("\n");
	}
}
/**
 *	\fn			void printSymbolListByClass(void)
 *	\brief		Afficher les symboles définis par classe et type
 */
void printSymbolListByClass(void) {
	symbol_t *mySp; int i;
	printMessage(70,"---- Nombres \t----\n");
	for (i=0, mySp = _symbolList; mySp != SYMBOL_NULL; mySp = mySp->next)
		if (mySp->clas == DAT) {
			if (mySp->type == ENTIER) printMessage(71,*(int *) mySp->U.pValue);
			else if (mySp->type == REEL) printMessage(72,*(double *) mySp->U.pValue);
			if ((++i)%4 == 0) printMessage(70,"\n");
		}
	printMessage(70,"\t****\n");
	printMessage(70,"---- Variables \t----\n");
	for (i=0, mySp = _symbolList; mySp != SYMBOL_NULL; mySp = mySp->next)
		if (mySp->clas == CST || mySp->clas == VAR) {
			if (mySp->type == ENTIER || mySp->type == IVAR) printMessage(73, mySp->name, *(int *) mySp->U.pValue);
			else if (mySp->type == REEL || mySp->type == FVAR) printMessage(74, mySp->name,*(double *) mySp->U.pValue);
			if ((++i)%2 == 0) printMessage(70,"\n");
		}
	printMessage(70,"\t****\n");
	printMessage(70,"---- Fonctions prédéfinies \t----\n");
	for (mySp = _symbolList; mySp != SYMBOL_NULL; mySp = mySp->next)
		if (mySp->clas == PRG && mySp->type == PREDEF)
			printMessage(75,mySp->name);
	printMessage(70,"\t****\n");
	printMessage(70,"---- Opérateurs arithmétiques \t----\n");
	for (mySp = _symbolList; mySp != SYMBOL_NULL; mySp = mySp->next)
		if (mySp->clas == PRG && mySp->type != PREDEF)
			printMessage(76,mySp->name);
	printMessage(70,"\t****\n");
	printMessage(70,"---- Non-définis \t----\n");
	for (mySp = _symbolList; mySp != SYMBOL_NULL; mySp = mySp->next)
		if (mySp->type == UNDEF)
			printMessage(76,mySp->name);
	printMessage(70,"\t****\n");
}
/**
 *	\var		_strClassSymbol[]
 *	\brief		Chaine de caractères décrivant la classe d'un symbole
 */
const char* _strClassSymbol[]   = { "VALUE",    "CONSTANT", "VARIABLE", "PROGRAM" };
#define STR_CLASS(param)  		_strClassSymbol[(param)-DAT]
/**
 *	\var		_strClassSymbol[]
 *	\brief		Chaine de caractères décrivant le type d'un symbole
 */
const char* _strTypeSymbol[]    = {
	"INTEGER",  "FLOAT",    "UNDEF",    "VAR_INT",	"VAR_FLO",
	"PREDEF",	"ADD",      "SUB",      "MUL",      "DIV",
	"PO",       "PF"
};
#define STR_TYPE(param)    _strTypeSymbol[(param)-ENTIER]
/**
 *	\fn			void _symbolValue(symbol_t * syPtr, char * value)
 *	\brief		Renseigne value avec la valeur du symbole selon son type
 */
void _symbolValue(symbol_t * syPtr, char * value) {
	switch (syPtr->type) {
		case ENTIER : case IVAR	:
			sprintf(value,"%14i",*(int*)(syPtr->U.pValue)); break;
		case REEL : case FVAR :
			sprintf(value,"%14.12g",*(double*)(syPtr->U.pValue)); break;
		case PREDEF :
			sprintf(value,"%-14p",syPtr->U.pValue); break;
		case UNDEF :
			sprintf(value,"%-14s","UNDEFINED"); break;
		default:
			if (syPtr->clas == PRG) sprintf(value,"%-14p",syPtr->U.pValue);
	}
}
/**
 *	\fn			void dbgSymbolList(void)
 *	\brief		Afficher les attributs du tous les symboles
 *	\note		Les données seront affichées sous forme d'un tableau :
 *				entête/pied, 1 ligne par symbole (adresse mémoire, nom, classe,
 *				type, adresse mémoire valeur, valeur)
 */
void dbgSymbolList(void) {
	symbol_t *mySp;
	char value[20];

	printMessage(81); printMessage(82); printMessage(83); printMessage(82);
	for (mySp = _symbolList; mySp != SYMBOL_NULL; mySp = mySp->next) {
		_symbolValue(mySp, value);
		printMessage(85, mySp, STR_CLASS(mySp->clas), STR_TYPE(mySp->type),mySp->name, value, mySp->desc);
	}
	printMessage(82); printMessage(84);
}
void dbgSymbolListV2(void) {
	symbol_t *mySp;
	char value[20];

	printMessage(81); printMessage(82); printMessage(83); printMessage(82);
	for (mySp = _symbolList; mySp != SYMBOL_NULL; mySp = mySp->next) {
		_symbolValue(mySp, value);
		printMessage(86);
		printMessage(87, mySp, STR_CLASS(mySp->clas), STR_TYPE(mySp->type),mySp->name, value, mySp->desc);
	}
	printMessage(82); printMessage(84);
}
/**
 *	\fn			void dbgSymbol(symbol_t * symbPtr)
 *	\brief		Afficher les attributs du symbole fourni en paramètre
 *	\note		symbPtr : pointeur sur le symbole
 */
void dbgSymbol(symbol_t * symbPtr) {
	printMessage(90, STR_CLASS(symbPtr->clas), STR_TYPE(symbPtr->type), symbPtr->desc);
	 switch (symbPtr->clas) {
		 case PRG:
			 if (symbPtr->type == PREDEF) printMessage(94, symbPtr->name, symbPtr->U.pFct);
			 else if (symbPtr->type >= ADD && symbPtr->type <= PF)
				 printMessage(93, symbPtr->name, symbPtr->U.pFct);
			 else printMessage(96);
			 break;
		 case DAT:
		 case CST:
		 case VAR:
			 if (symbPtr->type == ENTIER || symbPtr->type == IVAR)
				 printMessage(91, symbPtr->name, *(int *)symbPtr->U.pValue);
			 else if (symbPtr->type == REEL || symbPtr->type == FVAR)
				 printMessage(92, symbPtr->name, *(double*)symbPtr->U.pValue);
			 else printMessage(95);
			 break;
		 default: printMessage(97);
	 }
}
