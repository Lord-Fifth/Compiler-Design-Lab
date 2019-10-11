/* Program to convert NFA to DFA and minimize the DFA
   Author : Aditya Suresh (R7) */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define STATES 100
#define SYMBOLS 100
struct Dstate     // Structure for storing DFA states
{
    char name;
    char StateString[STATES + 1];
    char trans[10];
    int is_final;
} Dstates[50];
struct tran     // Structure for storing transitions
{
    char sym;
    int tostates[50];
    int notran;
};
struct state       // Structure for NFA states
{
    int no;
    struct tran tranlist[50];
};
struct state1{      // Structure for storing DFA states for minimizing DFA
	int input[100];
	int isFinal;
	int current_set;
	int last_set;
	int value;
}table[100];
char input[100];
struct state1 optimized[100];
int stackA[100], stackB[100], C[100], Cptr = -1, Aptr = -1, Bptr = -1;
struct state States[STATES];
char temp[STATES + 1], inp[10];
int nos, noi, nof, j, k, nods = -1,i;
void pushA(int z)   
{
    stackA[++Aptr] = z;
}
void pushB(int z)
{
    stackB[++Bptr] = z;
}
int popA()
{
    return stackA[Aptr--];
}
void copy(int i)
{
    char temp[STATES + 1] = " ";
    int k = 0;
    Bptr = -1;
    strcpy(temp, Dstates[i].StateString);
    while (temp[k] != '\0')
    {
        pushB(temp[k] - '0');
        k++;
    }
}
int popB()
{
    return stackB[Bptr--];
}
int peekB()
{
    return stackA[Bptr];
}
int peekA()
{
    return stackA[Aptr];
}
int seek(int arr[], int ptr, int s)
{
    int i;
    for (i = 0; i <= ptr; i++)
    {
        if (s == arr[i])
            return 1;
    }
    return 0;
}
void sort_state()         // Function to sort state
{
    int i, j, temp;
    for (i = 0; i < Bptr; i++)
    {
        for (j = 0; j < (Bptr - i); j++)
        {
            if (stackB[j] > stackB[j + 1])
            {
                temp = stackB[j];
                stackB[j] = stackB[j + 1];
                stackB[j + 1] = temp;
            }
        }
    }
}
void tostring()
{
    int i = 0;
    sort_state();
    for (i = 0; i <= Bptr; i++)
    {
        temp[i] = stackB[i] + '0';
    }
    temp[i] = '\0';
}
void display_DTran()  // Function to display DFA
{
    int i, j;
    printf("\nDFA Transition Table ");
    printf("\n-------------------- ");
    printf("\nStates\tString\t Inputs\n\t ");
    for (i = 0; i < noi; i++)
    {
        printf("\t%c", inp[i]);
    }
    printf("\n \t\t----------");
    for (i = 0; i < nods; i++)
    {

        if (Dstates[i].is_final == 0)
            printf("\n%c", Dstates[i].name);
        else
            printf("\n*%c", Dstates[i].name);

        printf("\t%s", Dstates[i].StateString);
        for (j = 0; j < noi; j++)
        {
            printf("\t%c", Dstates[i].trans[j]);
        }
    }
    printf("\n");
}

void move(int st, int j)
{
    int ctr = 0;
    while (ctr < States[st].tranlist[j].notran)
    {
        pushA(States[st].tranlist[j].tostates[ctr++]);
    }
}
void lambda_closure(int st)  // Function to find epsilon closure
{
    int ctr = 0, in_state = st, curst = st, chk;
    while (Aptr != -1)
    {
        curst = popA();
        ctr = 0;
        in_state = curst;
        while (ctr <= States[curst].tranlist[noi].notran)
        {
            chk = seek(stackB, Bptr, in_state);
            if (chk == 0)
                pushB(in_state);
            in_state = States[curst].tranlist[noi].tostates[ctr++];
            chk = seek(stackA, Aptr, in_state);
            if (chk == 0 && ctr <= States[curst].tranlist[noi].notran)
                pushA(in_state);
        }
    }
}

void compute_value(int n,int m)   
{
    int ans,c;
    for(int i=0;i<n;i++)
    {
        ans=0;
        c=1;
        for(int j=0;j<m;j++)
        {
            ans=ans+table[table[i].input[j]].last_set*c;
            c*=10;
        }
        table[i].value=ans;
    }
}
int generate_current_set(int n)  // Function to generate current NFA sets
{
    int c=-1,flag;
    for(int i=0;i<n;i++)
    {
        flag=0;
        for( int j=i-1;j>=0;j--)
        {
           if(table[i].last_set==table[j].last_set&&table[i].value==table[j].value)
            {
                table[i].current_set=table[j].current_set;
                flag=1;
                break;
            }
        }
         if(flag!=1)
            {
                c++;
                table[i].current_set=c;
            }

    }
    return c;
}
void current_to_last(int n)
{
    for(int i=0;i<n;i++)
    {
        table[i].last_set=table[i].current_set;
    }
}
void change_name(int n,int c,int m)  // Function to change state name
{
  for(int i=0;i<=c;i++)
  {
    for(int j=0;j<n;j++)
    {
        if(table[j].current_set==i)
        {
            for(int k=0;k<m;k++)
            optimized[i].input[k]=table[j].input[k];
            optimized[i].isFinal=table[j].isFinal;
             break;
        }
    }

  }
  for(int i=0;i<=c;i++)
  {
      for(int j=0;j<m;j++)
      {

              optimized[i].input[j]=table[optimized[i].input[j]].current_set;
      }
  }
}
void print(struct state1* tabl,int n,int m)   // Function to print minimized DFA
{
    int i,j,k;
    printf("\nState\tInput");
    printf("\n \t----------\n");
    for (i = 0; i < m; i++)
    {
        printf("\t%d",i);
    }
    printf("\n \t----------");
    printf("\n");
    for(i=0;i<=n;i++)
    {
        if(tabl[i].isFinal==1)
            printf("*%c\t",i+65);
        else
            printf("%c\t",i+65);
        for(j=0;j<m;j++)
        {  
           k = tabl[i].input[j];
           printf("%c\t",k+65);
        }
        printf("\n");
    }
}
void dfa_minimize()  // Function to perform DFA minimization
{
    int n,m,t=-1,set=2,i,j,key,q,flag,p,u;
    n=nods;
    m=noi;
    for(int i=0;i<n;i++)
    {
       for(j=0;j<m;j++)
       {

           table[i].input[j] = (Dstates[i].trans[j]) - 65 ;
       }
       table[i].last_set= Dstates[i].is_final;
       table[i].isFinal=table[i].last_set;
       
    }
    flag=0;
    q=1;
    p=3;
    u=0;
    while(p!=q)
    {
            /* 
	       compute function calculates the set value of every state and then adds 
               all the set values in array aar1 and returns the size of array aar1 
            */
	    if(flag==1)
	    {
		q=p;
	    }
	    compute_value(n,m);
	    p=generate_current_set(n);
	    current_to_last(n);
	    printf("\n\n\t %d equivalent \t\t",++u);
	    for(int i=0;i<n;i++)
	    printf("%d",table[i].current_set);
		printf("\n");
	    flag=1;
    }
    change_name(n,p,m);
    print(optimized,p,m);
}

int main()    // Main Function
{
    int final[20], start, fin = 0, i;
    char c, ans, st[20];
    printf("\nEnter no. of states in NFA\n");
    scanf("%d", &nos);
    for (i = 0; i < nos; i++)
    {
        States[i].no = i;
    }
    printf("\nEnter the start state\n");
    scanf("%d", &start);
    printf("Enter the no. of final states\n");
    scanf("%d", &nof);
    printf("\nEnter the final states\n");
    for (i = 0; i < nof; i++)
        scanf("%d", &final[i]);
    printf("\nEnter the no. of input symbols\n");
    scanf("%d", &noi);
    c = getchar();
    printf("\nEnter the input symbols\n ");
    for (i = 0; i < noi; i++)
    {
        scanf("%c", &inp[i]);
        c = getchar();
    }
    inp[i] = 'e';
    printf("\nEnter the transitions (-1 to stop)\n");
    for (i = 0; i < nos; i++)
    {
        for (j = 0; j <= noi; j++)
        {
            States[i].tranlist[j].sym = inp[j];
            k = 0;
            ans = 'y';
            while (ans == 'y')
            {
                printf("move(%d,%c) : ", i, inp[j]);
                scanf("%d", &States[i].tranlist[j].tostates[k++]);
                if (States[i].tranlist[j].tostates[k - 1] == -1)
                {
                    k--;
                    ans = 'n';
                    break;
                }
            }
            States[i].tranlist[j].notran = k;
        }
    }
    //Starting DFA Conversion
    i = 0;
    nods = 0;
    fin = 0;
    pushA(start);
    lambda_closure(peekA());
    tostring();
    Dstates[nods].name = 'A';
    nods++;
    strcpy(Dstates[0].StateString, temp);
    while (i < nods)
    {
        for (j = 0; j < noi; j++)
        {
            fin = 0;
            copy(i);
            while (Bptr != -1)
            {
                move(popB(), j);
            }
            while (Aptr != -1)
                lambda_closure(peekA());
            tostring();
            for (k = 0; k < nods; k++)
            {
                if ((strcmp(temp, Dstates[k].StateString) == 0))
                {
                    Dstates[i].trans[j] = Dstates[k].name;
                    break;
                }
            }
            if (k == nods)
            {
                nods++;
                for (k = 0; k < nof; k++)
                {
                    fin = seek(stackB, Bptr, final[k]);
                    if (fin == 1)
                    {
                        Dstates[nods - 1].is_final = 1;
                        break;
                    }
                }
                strcpy(Dstates[nods - 1].StateString, temp);
                Dstates[nods - 1].name = 'A' + nods - 1;
                Dstates[i].trans[j] = Dstates[nods - 1].name;
            }
        }
        i++;
    }
    display_DTran();
    printf("\nMinimized DFA Transition Table ");
    printf("\n------------------------------ ");
    dfa_minimize();
    return 0;
}


/*

Enter no. of states in NFA
10

Enter the start state
0
Enter the no. of final states
1

Enter the final states
9

Enter the no. of input symbols
2

Enter the input symbols
 a b

Enter the transitions (-1 to stop)
move(0,a) : -1
move(0,b) : -1
move(0,e) : 1
move(0,e) : 7
move(0,e) : -1
move(1,a) : -1
move(1,b) : -1
move(1,e) : 2
move(1,e) : 4
move(1,e) : -1
move(2,a) : 3
move(2,a) : -1
move(2,b) : -1
move(2,e) : -1
move(3,a) : -1
move(3,b) : -1
move(3,e) : 6
move(3,e) : -1
move(4,a) : -1
move(4,b) : 5
move(4,b) : -1
move(4,e) : -1
move(5,a) : -1
move(5,b) : -1
move(5,e) : 6
move(5,e) : -1
move(6,a) : -1
move(6,b) : -1
move(6,e) : 7
move(6,e) : -1
move(7,a) : 8
move(7,a) : -1
move(7,b) : -1
move(7,e) : -1
move(8,a) : -1
move(8,b) : 9
move(8,b) : -1
move(8,e) : -1
move(9,a) : -1
move(9,b) : -1
move(9,e) : -1

DFA Transition Table 
-------------------- 
States	String	 Inputs
	 	a	b
 		----------
A	01247	B	C
B	3678	D	E
C	567	D	F
D	8	F	E
*E	9	F	F
F		F	F

Minimized DFA Transition Table 
------------------------------ 

	 1 equivalent 		010120


	 2 equivalent 		010234


	 3 equivalent 		012345


	 4 equivalent 		012345

State	Input
 	----------
	0	1
 	----------
A	B	C	
B	D	E	
C	D	F	
D	F	E	
*E	F	F	
F	F	F	

*/
