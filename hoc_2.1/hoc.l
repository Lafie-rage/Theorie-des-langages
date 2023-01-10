/**
 *	\file		hoc.l
 *	\version	2.0
 *	\date		5 Février 2021
 *	\author		Samir El Khattabi
 */
%{
#define _HOC_L_
#include "hoc.h"
%}
%option noyywrap
entier		[0-9]+
reel		([0-9]+\.?)|([0-9]*\.[0-9]+)
ident		[a-zA-Z][a-zA-Z_0-9]*
carExclu	[^\-+*/=()a-zA-Z_0-9?@\n \t]
operateur	("+"|"-"|"*"|"/"|"("|")")
pr_sy		("printSymbols"|"?")
pr_sy2		("??")
%%
{pr_sy}		return PR_TS;
{pr_sy2}	return PR_TS2;
"@"			return DBG_TS;
"@@"		return DBG_TS2;
"debug"		return DBG;
{entier}    { yylval.symb = installIntSymbol("",DAT,atoi(yytext),"*(int *)"); return (yylval.symb)->type; };
{reel}      { yylval.symb = installFloSymbol("",DAT,atof(yytext),"*(double *)"); return (yylval.symb)->type; };
{ident}		{ yylval.symb =  lookUpSymbol(yytext);
    		if (yylval.symb==NULL) yylval.symb=installSymbol(yytext,VAR,UNDEF,0,NULL, NULL);
            return (yylval.symb)->type; };
{operateur}	{ yylval.symb =  lookUpSymbol(yytext);
			if (yylval.symb==NULL) lexError(LEX_ERR_UNK_OP, yytext);
			return (yylval.symb)->type; };
\n			return RC;
{carExclu}+	lexError(LEX_ERR_UNK_WORD, yytext, yyleng);
.			;
			/* Tout ce qui n'est pas spécifié, sera ignoré */
<<EOF>>		return 0;	/* ^D = fin de ... */
%%
