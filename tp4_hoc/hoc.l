/**
 *	\file		hoc.l
 *	\version	1.2
 *	\date		26 Janvier 2021
 *	\author		Samir El Khattabi
 */
%{
#define _HOC_L_
#include "hoc.h"
int installIntSymbol();
int installDoubleSymbol();
%}
%option noyywrap
entier		[0-9]+
reel		([0-9]+\.?)|([0-9]*\.[0-9]+)
ident		[a-zA-Z][a-zA-Z_0-9]*
carExclu	[^a-zA-Z_0-9\.+\-*/=()\n]+
operateur ("+"|"-"|"*"|"/"|"("|")")
%%
"quit"		return 0;
{entier}    { return installIntSymbol();};
{reel}      { return installDoubleSymbol();};
{ident}		{ symbol_t* mySp =  lookUpSymbol(yytext);
    		if (mySp==NULL) mySp=installSymbol(yytext,VAR,UNDEF,0,NULL);
            yylval.symb   = mySp;
            printf("lex %s, %d, %d, %p\n", mySp->name, mySp->clas, mySp->type, mySp->U.pFct);
            return mySp->type;};
{operateur}			{
          				yylval.symb = lookUpSymbol(yytext);
          				if(yylval.symb == NULL) exeError("Opérateur [%s] inconnu", yytext);
          				return (yylval.symb)->type;
                };
"="         return AFF;
\n			return RC;
{carExclu}	lexError("Unkown Word : #%s#[%d]", yytext, strlen(yytext));
.			;			/* Tout ce qui n'est pas spécifié, sera ignoré */
<<EOF>>		return 0;	/* ^D = fin de ... */
%%
int installIntSymbol() {
	int *pValue = (int *)malloc (sizeof(int));
	*pValue = atoi(yytext);
	yylval.symb = installSymbol("", DAT, ENTIER, sizeof(int), pValue);
	return (yylval.symb)->type;
}
int installDoubleSymbol() {
	double *pValue = (double *)malloc (sizeof(double));
	*pValue = atof(yytext);
	yylval.symb = installSymbol("", DAT, REEL, sizeof(double), pValue);
	return (yylval.symb)->type;
}
