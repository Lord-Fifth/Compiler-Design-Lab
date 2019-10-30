/* Program to implement compiler back-end and convert to Three-Address Code in 8086 Architecture
   Author : Aditya Suresh (R7) */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main()
{
	char input[10][30],str[20],opr[10];
	char tab[10];
	int i=0,n=0,k=0,j=0,m=0;
	

	printf("enter input\n");

	do{
		gets(input[i]);
	

	}while(strcmp(input[i++],"exit")!=0);

	//puts(input[0]);


printf("\n target code generation");

i=0;
do
{
 strcpy(str,input[i]);
 if(str[0]=='l')
 {
	//printf("yo%d",(str[1]-'0'));
	k=str[1]-'0';
	tab[k++]=n;
 }


 switch(str[6])
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
case 'o':
 goto jum;
 break;
 }

 printf("\n%d\tMOV %c,R%d",1000+(n++),str[5],i);

 printf("\n%d\t%s %c,R%d",1000+(n++),opr,str[7],i);
 printf("\n%d\tMOV R%d,%c",1000+(n++),i,str[3]);

jum: if(str[8]=='l')
 {
	j=str[9]-'0';
	m=tab[j];
	printf("\n%d\tJUMP %d",1000+(n++),1000+m);
 }

 }while(strcmp(input[++i],"exit")!=0);







}

/*

l1:a=a*b         
   b=b*a
   goto l1
exit

   a=a*b         
l1:b=b*a
   goto l1
exit

   a=a*b         
l1:b=b+a
   goto l1
exit



*/
