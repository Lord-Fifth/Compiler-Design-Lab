%{
	#include<stdio.h>
	#include "arth.tab.h"
%}

%%

[0-9]+	{ return NUMBER;  }
[a-z]+ | [A-Z]+	{ return ID; }
[+\-*/\(\) ;] 	{ return *yytext; }

%%
int yywrap()
{
	return 1;
}
