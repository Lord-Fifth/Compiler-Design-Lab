%{
	#include "calc.tab.h"
	#include<stdio.h>
%}

%%
[0-9]+		{ yylval.integer = atoi(yytext); return NUMBER;	}
[+\-*/\(\)%;]    { return *yytext; }
%%

int yywrap()
{
	return 1;
}
