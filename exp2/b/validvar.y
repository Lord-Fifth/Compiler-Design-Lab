%{	
	#include<stdio.h>
	#include<stdlib.h>
	
	extern int yylex();
	void yyerror(char *s);

%}

%token LETTER DIGIT 
%start start

%%

start : variable {  printf("Valid variable definition\n"); exit(0);	}

variable : LETTER postcondn {;}

postcondn : LETTER postcondn
	  | DIGIT postcondn 
	  | '\n'   {;}

%%

void yyerror(char *s)
{
	fprintf(stdout,"Invalid variable definition\n");
}

int main()
{
	yyparse();
}
