%{
	#include "validvar.tab.h"
	#include <stdio.h>
%}

%%
[a-z]|[A-Z]	{ return LETTER; }
[0-9] 	 	{ return DIGIT;  }
[\n] 		{ return *yytext;}
%%

int yywrap()
{
 return 1;
}
