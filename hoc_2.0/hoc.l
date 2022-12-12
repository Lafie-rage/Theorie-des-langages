/**
 *	\file		hoc.l
 *	\version	1.4.6
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
operateur	("+"|"-"|"*"|"/"|"#"|"("|")"|"?"|"??"|"@")
%%
{entier}    { yylval.symb = installIntSymbol("",DAT,atoi(yytext),NULL); return (yylval.symb)->type; };
{reel}      { yylval.symb = installFloSymbol("",DAT,atof(yytext),NULL); return (yylval.symb)->type; };
{ident}		{ yylval.symb =  lookUpSymbol(yytext);
    		if (yylval.symb==NULL) yylval.symb=installSymbol(yytext,VAR,UNDEF,0,NULL, NULL);
            return (yylval.symb)->type; };
{operateur}	{ yylval.symb =  lookUpSymbol(yytext);
			if (yylval.symb==NULL) lexError("Opérateur [%s] inconnu", yytext);
			return (yylval.symb)->type; }; // Transformer en utilisant myError
"="         return AFF;
\n			return RC;
{carExclu}+	lexError("Unkown Word : #%s#[%d]", yytext, yyleng);
.			;
			/* Tout ce qui n'est pas spécifié, sera ignoré */
<<EOF>>		return 0;	/* ^D = fin de ... */
%%
