%{
	#include<stdio.h>
	#include<stdlib.h>
	extern int yylex();
	void yyerror(char *s);
%}

%start start

%union
{
int integer ;
}

%left '+' '-'
%left '*' '/' '%'
%type<integer> expr 
%token<integer> NUMBER

%%
start : expr ';' 	{ printf("RESULT=%d\n",$1); exit(0); 	}

expr : expr '+' expr	{ $$ =$1+$3;	}
     | expr '-' expr    { $$ =$1-$3;	}
     | expr '*' expr    { $$ =$1*$3;	}
     | expr '/' expr    { $$ = $1/$3;	}
     | '(' expr ')'	{ $$ =$2;	}
     | NUMBER  		{ $$=$1;	}
	
%%

void yyerror(char *s)
{
fprintf(stdout, "INVALID ARITHMETIC EXPRESSION\n");
}

int main()
{
yyparse();
}
