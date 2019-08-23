%{
	#include<stdlib.h>
	#include<stdio.h>

	extern int yylex();
	void yyerror(char *s);
%}

%start start
%token NUMBER ID

%left '+' '-'
%left '*' '/'
%%

start : expr ';' 		{ printf("Valid arithmetic expression\n"); }

expr : NUMBER 
      | ID
      | expr '+' expr
      | expr '-' expr
      | expr '*' expr 
      | expr '/' expr 	
      | '(' expr ')'   {;}
%%

void yyerror(char *s)
{
 fprintf(stdout,"INVALID ARITHMETIC EXPRESSION");
}

int main()
{
 yyparse();
}
