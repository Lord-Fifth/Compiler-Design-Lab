/*
   Program to Simulate First and Follow of any given grammar.
   Author : Aditya Suresh (R7)
*/

#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
int n,m=0,p,i=0,j=0;
char a[10][10],f[10];
void follow(char c);
void first(char c); 
int main()  // Main function
{
    int i,z;
    char c,ch;
    printf("Enter the no of productions:\n");
    scanf("%d",&n);   // Getting number of productions
    printf("\nEnter the productions:\n");    
    for(i=0;i<n;i++)
    scanf("%s%c",a[i],&ch);
    do{
        m=0;
        printf("\nEnter the elements whose first & follow is to be found \n");
        scanf("%c",&c);
        first(c);
        printf("First(%c) = { ",c);
        for(i=0;i<m;i++)
            printf("%c ",f[i]);
        printf("}\n");
        strcpy(f," ");
        m=0;
        follow(c);
        printf("Follow(%c) = { ",c);
        for(i=0;i<m;i++)
        printf("%c ",f[i]);
        printf("}\n");
        printf("\nPress 1 to continue or else press 0 to exit.");
        scanf("%d%c",&z,&ch);
    }while(z==1);
    return(0);
}
void first(char c)    // Function to find first of given grammar symbol
{
    int k;
    if(!isupper(c))
        f[m++]=c;
    for(k=0;k<n;k++)
    {
        if(a[k][0]==c)
        {
            if(a[k][2]=='$')
                follow(a[k][0]);
            else if(islower(a[k][2]))
                f[m++]=a[k][2];
            else 
                first(a[k][2]);
        }
    }
}
void follow(char c)  // Function to find follow of given grammar symbol
{
    if(a[0][0]==c)
        f[m++]='$';
    for(i=0;i<n;i++)
    {
        for(j=2;j<strlen(a[i]);j++)
        {
            if(a[i][j]==c)
            {
                if(a[i][j+1]!='\0')
                    first(a[i][j+1]);
                if(a[i][j+1]=='\0' && c!=a[i][0])
                    follow(a[i][0]);
            }
        }
    }
}


/*

Enter the no of productions:
4

Enter the productions:
S=(L)     
S=a
L=SU
U=e  

Enter the elements whose first & follow is to be found 
S
First(S) = { ( a }
Follow(S) = { $ e }

Press 1 to continue or else press 0 to exit.1

Enter the elements whose first & follow is to be found 
L
First(L) = { ( a }
Follow(L) = { ) }

Press 1 to continue or else press 0 to exit.1

Enter the elements whose first & follow is to be found 
U
First(U) = { e }
Follow(U) = { ) }

Press 1 to continue or else press 0 to exit.0


*/


