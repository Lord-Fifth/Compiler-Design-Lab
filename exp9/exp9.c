/* Program to convert to 3-Address Code in 8086 Architecture
   Author : Aditya Suresh (R7) */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main()
{
	char input[10][30],str[20],opr[10];
	char tab[10];
	int i=0,n=0,k=0,j=0,m=0;
	printf("enter input terminated by exit\n");
	do{
		scanf("%s",input[i]);
	}while(strcmp(input[i++],"exit")!=0);
	printf("\n target code generation");

	i=0;
	do
	{
	strcpy(str,input[i]);
	switch(str[3])
	{
		case '+':
			strcpy(opr,"ADD");
			break;
		case '-':
			strcpy(opr,"SUB");
			break;
		case '*':
			strcpy(opr,"MUL");
			break;
		case '/':
			strcpy(opr,"DIV");
			break;
	}

	printf("\n%d\tMOV %c,R%d",1000+(n++),str[2],i);
	printf("\n%d\t%s %c,R%d",1000+(n++),opr,str[4],i);
	printf("\n%d\tMOV R%d,%c",1000+(n++),i,str[0]);
	}while(strcmp(input[++i],"exit")!=0);
}

/*
enter input terminated by exit
a=b+c
b=c-d
d=e*b
exit

 target code generation
1000	MOV b,R0
1001	ADD c,R0
1002	MOV R0,a
1003	MOV c,R1
1004	SUB d,R1
1005	MOV R1,b
1006	MOV e,R2
1007	MUL b,R2
1008	MOV R2,d
*/