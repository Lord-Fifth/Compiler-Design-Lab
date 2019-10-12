/*
   Program Name : Program to develop an operator precedence parser for a given language.
   Author : Aditya Suresh (R7) 
*/
#include<stdio.h>
#include<string.h>

#define MAX_HANDLES 5  

int top = 0;
int len = 0;
int i = 0;

char input[50];
char lastHandle[6];
char stack[50];
char handles[][5] = {")E(","E*E","E+E","i","E^E"};
//(E) becomes )E( when pushed to stack

// Operator precedence table
char precedence[9][9] = {

                            /*input*/

            /*stack    +    -   *   /   ^   i   (   )   $  */

            /*  + */  '>', '>','<','<','<','<','<','>','>',

            /*  - */  '>', '>','<','<','<','<','<','>','>',

            /*  * */  '>', '>','>','>','<','<','<','>','>',

            /*  / */  '>', '>','>','>','<','<','<','>','>',

            /*  ^ */  '>', '>','>','>','<','<','<','>','>',

            /*  i */  '>', '>','>','>','>','e','e','>','>',

            /*  ( */  '<', '<','<','<','<','<','<','>','e',

            /*  ) */  '>', '>','>','>','>','e','e','>','>',

            /*  $ */  '<', '<','<','<','<','<','<','<','>',

            };

int getIndex(char c)    // Function to get index of operator in table
{
    switch(c)
    {
        case '+':return 0;
        case '-':return 1;
        case '*':return 2;
        case '/':return 3;
        case '^':return 4;
        case 'i':return 5;
        case '(':return 6;
        case ')':return 7;
        case '$':return 8;
    }
}
 
void shift()     // Function to shift the input to stack
{
    stack[++top] = input[i++];
    stack[top+1] = '\0';
}

int reduce()   // Function to reduce if high precedence occurs 
{
    int i = 0;
    int j = 0;
    int length = 0;
    int match = 0;

    for(i = 0; i < MAX_HANDLES; i++){
        length = strlen(handles[i]);
        //when there is a possibility of a matching handle of sufficient length
        if(stack[top] == handles[i][0] && (top + 1) >= length){
            match = 1;
            //traverse from top of the stack and check for any mismatch with the handle
            for(j = 0; j < length; j++){
                
                if(stack[top - j] != handles[i][j]){
                    match = 0;
                    break;
                }
            }
            if(match){
                stack[top - j + 1] = 'E';
                top = top - j + 1;
                strcpy(lastHandle, handles[i]);
                stack[top + 1]='\0';
                return 1;
            }
        }
        
    }
    return 0;
}

void print_stack()   // Function to print stack
{
    int j;
    for(j = 0; j <= top; j++)
        printf("%c",stack[j]);
}

void print_input()  // Function to print input 
{
    int j;
    for(j = i; j < len; j++)
        printf("%c",*(input+j));
}

int main()     // Main function
{
    int j;
    
    printf("\nEnter the string\n");
    scanf("%s",input);     // Getting input string
    strcat(input,"$");
    len = strlen(input);
    strcpy(stack,"$");                  //initialise stack 
    printf("\nSTACK\tINPUT\tACTION");

    while(i <= len){
        shift();
        printf("\n");
        print_stack();
        printf("\t");
        print_input();
        printf("\tShift");
        //when top of the stack is related to incoming character by '>' we reduce
        if(precedence[getIndex(stack[top])][getIndex(input[i])] == '>'){
            while(reduce())
			{
			    printf("\n");
			    print_stack();
			    printf("\t");
			    print_input();
			    printf("\tReduced: E->%s",lastHandle);
			}
        }
        
    }
    if(strcmp(stack,"$E$")==0)
        printf("\nAccepted;\n");
    else
        printf("\nNot Accepted;\n");

    return 0;
}
