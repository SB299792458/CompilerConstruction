#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int rule[66][58];

typedef struct rulesList
{
	char str[10][30];
	int size;
}rules_list;

rules_list RL[105];

typedef struct _element {
    char *string;
     int value;
    struct _element *next;
   
} element;

typedef struct _hash_table {
    int size;       /* the size of the table */
    element **table; /* the table elements */
} hash_table;



hash_table *create_hash_table(int size)
{
    hash_table *new_table;
    
    if (size<1) return NULL; /* invalid size for table */

    /* Attempt to allocate memory for the table structure */
    if ((new_table = malloc(sizeof(hash_table))) == NULL) {
        return NULL;
    }
    
    /* Attempt to allocate memory for the table itself */
    if ((new_table->table = malloc(sizeof(element *) * size)) == NULL) {
        return NULL;
    }

    /* Initialize the elements of the table */
    int i=0;
    for(i=0; i<size; i++) new_table->table[i] = NULL;

    /* Set the table's size */
    new_table->size = size;

    return new_table;
}


unsigned int hash(hash_table *hashtable, char *str)
{
    unsigned int hashval;
    hashval = 0;
    for(; *str != '\0'; str++) hashval = *str + (hashval << 5) - hashval;
    return hashval % hashtable->size;
}


int lookup_string(hash_table *hashtable, char *str)
{
    element *list;
    unsigned int hashval = hash(hashtable, str);
     for(list = hashtable->table[hashval]; list != NULL; list = list->next) {
        if (strcmp(str, list->string) == 0) return list->value;
    }
    return -1;
}
int add_string(hash_table *hashtable, char *str,int val)
{
    element *new_list;
    element *current_list;
    unsigned int hashval = hash(hashtable, str);
    if ((new_list = malloc(sizeof(element))) == NULL) return 1;
    
    new_list->string = strdup(str);
    new_list->value=val;
    new_list->next=hashtable->table[hashval];
    hashtable->table[hashval] = new_list;
    return 0;
}

struct stack_entry {
  char *data;
  struct stack_entry *next;
};

struct stack_t
{
  struct stack_entry *head;
  size_t stackSize;  
                     
};

struct stack_t *newStack(void)
{
  struct stack_t *stack = malloc(sizeof *stack);
  if (stack)
  {
    stack->head = NULL;
    stack->stackSize = 0;
  }
  return stack;
}
char *copyString(char *str)
{
  char *tmp = malloc(strlen(str) + 1);
  if (tmp)
    strcpy(tmp, str);
  return tmp;
}
void push(struct stack_t *theStack, char *value)
{
  struct stack_entry *entry = malloc(sizeof *entry); 
  
    entry->data = copyString(value);
    entry->next = theStack->head;
    theStack->head = entry;
    theStack->stackSize++;
}

char *top(struct stack_t *theStack)
{
  if (theStack && theStack->head)
    return theStack->head->data;
  else
    return NULL;
}

void pop(struct stack_t *theStack)
{
  if (theStack->head != NULL)
  {
    struct stack_entry *tmp = theStack->head;
    theStack->head = theStack->head->next;
    free(tmp->data);
    free(tmp);
    theStack->stackSize--;
  }
}



int construct_nonterminal()
{
	char *nonterminal[]=
	{
"<program>",
"<structures>",
"<declarations>",
"<functions>",
"<mainfunc>",
"<structure>",
"<P>",
"<type>",
"<idlist>",
"<arrayinit>",
"<T>",
"<funcname>",
"<funcsignature>",
"<Y>",
"<block>",
"<tryblock>",
"<args>",
"<returntype>",
"<T2>",
"<statement>",
"<statements>",
"<assignstat>",
"<returnstat>",
"<iterativestat>",
"<outstat>",
"<arraystmt>",
"<functioncall>",
"<toSend>",
"<literal>",
"<S>",
"<ifstat>",
"<elsestat>",
"<instat>",
"<arraypart>",
"<Z>",
"<X>",
"<Exp>",
"<ORexp>",
"<condExp>",
"<ANDexp>",
"<F>",
"<G>",
"<equalityexp>",
"<H>",
"<equalOp>",
"<relationalexp>",
"<arithmeticexp>",
"<J>",
"<relOp>",
"<addexp>",
"<mulexp>",
"<B>",
"<C>",
"<bitexp>",
"<D>",
"<bitOp>",
"kuchbhinahihaiyahpe",
"<unaryexp>",
"<notexp>",
"<K>",
"<simple>",
"<notOp>",
"<integerliteral>",
"<booleanliteral>",
"<charliteral>",
"yehbhi_kuch_nahi_hai"
	}; 

}

int construct_terminal()
{
	char *terminal[]=
	{
	"$",
"create",
"constant",
"TK_Identifier",
"void",	
"function",	
"main",	
"try",
"catch",
"finally",	
"call",	
"return",	
"end",
"next",	
"if",	
"else",	
"while",	
"input",	
"output",	
"array",	
"#",
".",	
"inc",	
"dec",	
"int",	
"char",	
"boolean",	
"TK_Integer",	
"true",	
"false",
"TK_Character",	
"void",	
"{",	
"}",	
"(",	
")",	
"[",	
"]",	
",",	
":",
";",	
":=",	
"||",	
"&&",	
"==",	
"!=",	
">",	
"<",	
"<=",	
">=",	
"-",	
"+",	
"*",	
"/",	
"%",	
"&",	
"|",	
"!"
	}; 

}

void construct_rule()
{
	
	int i=0, j=0;
	for(i=0; i< 66; i++)
		for(j=0; j<58; j++){
			rule[i][j]=-1;
		}
char *rules[]=
{
"e",
"<structures> <declarations> <functions> <main-func>",
"<structure> <structures>",
"<P> <type> <id-list> ; <declarations>",
"<arrayinit>",
"function <type> <funcname> : <funcsignature> <Y> <functions>",
"main  <block>",
"create TK_Identifier { <declarations> };",
"constant",
"TK_Identifier <T>",
"int",
"char",
"boolean",
"<arraypart> TK_Identifier ;",
", <id-list>",
"( <args> )",
"<try-block>",
"try <block> catch <block> finally <block>",
"<block>",
"{<statements>}",
"<type> TK_Identifier <T2>",
"void T2",
"<type>",
"void",
", <args>",
"<declarations>",
"<assignstat>",
"<functioncall>",
"<returnstat>",
"end;",
"next;",
"<ifstat>",
"<iterativestat>",
"<instat>",
"<outstat>",
"<statement> <statements>",
"<arraystmt> := <Exp>;",
"call id(<toSend>);",
"<arraystmt> <S>",
"<literal> <S>",
", <toSend>",
"return <to return> ;",
"<arraystmt>",
"<literal>",
"if(<condExp>){ <statements> } <elsestat>",
"else { <statements> }",
"while ( <condExp> ){ <statements> }",
"input >> id;",
"output << id;",
"<arraypart> id ;",
"array ( <types> )[<arithmeticexp>] <Z>",
"[ <arithmeticexp> ] <Z>",
"id <X>",
"# id <X>",
"[ <arithmeticexp> ] <X>",
".id",
"<ORexp>",
"<ANDexp> <F>",
"|| <ANDexp> <F>",
"<equalityexp> <G>",
"&&<equalityexp> <G>",
"<relationalexp> <H>",
"<equalOp> <relationalexp>",
"==",
"!=",
"<arithmeticexp> <J>",
"<relOp> <arithmeticexp>",
">",
"<",
"<=",
">=",
"<addexp>",
"<mulexp> <B>",
"+ <mulexp> <B>",
"- <mulexp> <B>",
"<bitexp> <C>",
"* <mulexp> <C>",
"/ <mulexp> <C>",
"% <mulexp> <C>",
"<unaryexp> <D>",
"<bitOp> <bitexp> <D>",
"&",
"|",
"<notexp> <K>",
"inc",
"dec",
"<notOp> <simple>",
"<simple>",
"!",
"(<Exp>)",
"<integerliteral>",
"<booleanliteral>",
"<charliteral>",
"true",
"false",
"TK_Integer",
"TK_Character",
"TK_identifier"
};


rule[0][1]=1;
rule[0][2]=1;
rule[0][5]=1;
rule[0][6]=1;
rule[0][9]=0;
rule[0][24]=1;
rule[0][25]=1;
rule[0][26]=1;
rule[1][1]=2;
rule[1][2]=0;
rule[1][3]=0;
rule[1][5]=0;
rule[1][6]=0;
rule[1][20]=0;
rule[1][24]=0;
rule[1][25]=0;
rule[1][26]=0;
rule[2][2]=3;
rule[2][3]=0;
rule[2][5]=0;
rule[2][6]=0;
rule[2][19]=4;
rule[2][20]=4;
rule[2][24]=3;
rule[2][25]=3;
rule[2][26]=3;
rule[2][33]=0;
rule[3][0]=0;
rule[3][5]=5;
rule[3][6]=0;
rule[4][6]=6;
rule[5][1]=7;
rule[6][2]=8;
rule[6][24]=0;
rule[6][25]=0;
rule[6][26]=0;
rule[7][24]=10;
rule[7][25]=11;
rule[7][26]=12;
rule[8][3]=9;
rule[8][40]=0;
rule[9][19]=13;
rule[10][38]=14;
rule[10][40]=0;
rule[11][3]=97;
rule[12][34]=15;
rule[13][7]=16;
rule[13][32]=18;
rule[14][32]=19;
rule[15][7]=17;
rule[16][24]=20;
rule[16][25]=20;
rule[16][26]=20;
rule[16][31]=21;
rule[17][24]=22;
rule[17][25]=22;
rule[17][26]=22;
rule[17][31]=23;
rule[18][35]=0;
rule[18][38]=24;
rule[19][2]=25;
rule[19][3]=26;


rule[19][22]=98;
rule[19][23]=98;
rule[59][27]=0;
rule[59][3]=0;
rule[59][22]=84;
rule[59][23]=85;



rule[19][10]=99;
rule[19][11]=28;
rule[19][12]=29;
rule[19][13]=30;
rule[19][14]=31;

rule[19][15]=-1;
rule[19][16]=32;
rule[19][17]=33;
rule[19][18]=34;
rule[19][19]=25;
rule[19][20]=26;
rule[19][24]=25;
rule[19][25]=25;
rule[19][26]=25;
rule[20][2]=35;
rule[20][3]=35;

rule[20][10]=35;
rule[20][11]=rule[20][12]=rule[20][13]=35;
rule[20][14]=35;

rule[20][16]=rule[20][17]=rule[20][18]=rule[20][19]=35;

rule[20][20]=35;
rule[20][22]=35;
rule[20][23]=35;


rule[20][24]=35;
rule[20][25]=35;
rule[20][26]=35;
rule[20][33]=0;
rule[21][3]=36;
rule[21][20]=36;
rule[22][11]=41;
rule[23][16]=46;
rule[24][18]=48;
rule[25][3]=52;
rule[25][20]=53;
rule[26][10]=37;
rule[27][27]=rule[27][28]=rule[27][29]=rule[27][30]=39;
rule[27][20]=38;
rule[27][3]=38;
rule[28][27]=90;
rule[28][28]=91;
rule[28][29]=91;
rule[28][30]=92;
rule[29][35]=0;
rule[29][38]=40;
rule[30][14]=44;
rule[31][33]=0;
rule[31][15]=45;
rule[31][16]=0;

rule[32][17]=47;
rule[33][19]=50;
rule[34][36]=51;
rule[34][3]=0;
rule[35][21]=55;
rule[35][21]=55;
rule[35][21]=55;

rule[35][22]=84;
rule[35][23]=85;
rule[35][35]=0;
rule[35][36]=54;
rule[35][38]=0;
rule[35][37]=0;
rule[2][17]=0;
rule[2][18]=0;
rule[27][31]=23;


int k;
for(k=40;k<=56;k++)
{
	rule[35][k]=0;
}
rule[36][3]=56;
rule[36][10]=27;
rule[36][20]=56;
for(k=27;k<=30;k++)
{
	rule[36][k]=56;
}
rule[36][34]=56;
rule[37][3]=57;
rule[37][20]=57;
for(k=27;k<=30;k++)
{
	rule[37][k]=57;
}
rule[37][34]=57;

rule[38][3]=56;
rule[38][20]=56;
for(k=27;k<=30;k++)
{
	rule[38][k]=56;
}
rule[38][34]=56;

rule[39][3]=59;
rule[39][20]=59;
for(k=27;k<=30;k++)
{
	rule[39][k]=59;
}
rule[39][34]=59;

rule[40][35]=0;
rule[40][40]=0;
rule[40][42]=58;

rule[41][35]=0;
rule[41][40]=0;
rule[41][42]=0;
rule[41][43]=60;

rule[42][3]=61;
rule[42][20]=61;
for(k=27;k<=30;k++)
{
	rule[42][k]=61;
}
rule[42][34]=61;

rule[43][35]=0;
rule[43][40]=0;
rule[43][42]=0;
rule[43][43]=0;
rule[43][44]=62;
rule[43][45]=62;

rule[44][44]=63;
rule[44][45]=64;

rule[45][3]=65;
rule[45][20]=65;
for(k=27;k<=30;k++)
{
	rule[45][k]=65;
}
rule[45][34]=65;

rule[46][3]=71;
rule[46][20]=71;
for(k=27;k<=30;k++)
{
	rule[46][k]=71;
}
rule[46][34]=71;

rule[47][35]=0;
rule[47][40]=0;
rule[47][42]=0;
rule[47][43]=0;
rule[47][44]=0;
rule[47][45]=0;
rule[47][47]=66;
rule[47][46]=66;
rule[47][48]=66;
rule[47][49]=66;

rule[48][46]=67;
rule[48][47]=68;
rule[48][48]=69;
rule[48][49]=70;

rule[49][3]=72;
rule[49][20]=72;
for(k=27;k<=30;k++)
{
	rule[49][k]=72;
}
rule[49][34]=72;

rule[50][3]=75;
rule[50][20]=75;
for(k=27;k<=30;k++)
{
	rule[50][k]=75;
}
rule[50][34]=75;


rule[51][35]=0;
rule[51][40]=0;
rule[51][42]=0;
rule[51][43]=0;
rule[51][44]=0;
rule[51][45]=0;
rule[51][47]=0;
rule[51][46]=0;
rule[51][48]=0;
rule[51][49]=0;
rule[51][50]=74;
rule[51][51]=73;

rule[51][37]=0;

rule[52][35]=0;
rule[52][40]=0;
rule[52][42]=0;
rule[52][43]=0;
rule[52][44]=0;
rule[52][45]=0;
rule[52][47]=0;
rule[52][46]=0;
rule[52][48]=0;
rule[52][49]=0;
rule[52][50]=0;
rule[52][51]=0;
rule[52][52]=76;
rule[52][53]=77;
rule[52][54]=78;

rule[52][37]=0;

rule[54][35]=0;
rule[54][37]=0;

rule[54][40]=0;
rule[54][42]=0;
rule[54][43]=0;
rule[54][44]=0;
rule[54][45]=0;
rule[54][47]=0;
rule[54][46]=0;
rule[54][48]=0;
rule[54][49]=0;
rule[54][50]=0;
rule[54][51]=0;
rule[54][52]=0;
rule[54][53]=0;
rule[54][54]=0;
rule[54][55]=80;
rule[54][56]=80;

rule[53][57]=79;

rule[53][3]=79;
rule[53][20]=79;
for(k=27;k<=30;k++)
{
	rule[53][k]=79;
}
rule[53][34]=79;


rule[55][55]=81;
rule[55][56]=82;


rule[57][3]=83;
rule[57][20]=83;
for(k=27;k<=30;k++)
{
	rule[57][k]=83;
}
rule[57][34]=83;
rule[57][57]=83;


rule[58][3]=87;
rule[58][20]=87;
for(k=27;k<=30;k++)
{
	rule[58][k]=87;
}
rule[58][34]=87;
rule[58][57]=86;

rule[59][22]=84;
	rule[59][23]=85;
	rule[59][35]=0;
	rule[59][35]=0;
	rule[59][37]=0;
	
	rule[59][40]=0;
	rule[59][42]=0;
	rule[59][43]=0;
	rule[59][44]=0;
	rule[59][45]=0;
	rule[59][47]=0;
	rule[59][46]=0;
	rule[59][48]=0;
	rule[59][49]=0;
	rule[59][50]=0;
	rule[59][51]=0;
	rule[59][52]=0;
	rule[59][53]=0;
	rule[59][54]=0;
	rule[59][55]=0;
	rule[59][56]=0;

	rule[60][3]=42;
	rule[60][20]=42;
	rule[60][27]=43;
	rule[60][28]=43;
	rule[60][29]=43;
	rule[60][30]=43;
	rule[60][34]=89;


	

	rule[61][57]=88;
	rule[61][27]=87;
	rule[61][28]=87;
	rule[61][29]=87;
	rule[61][30]=87;

	rule[62][27]=95;
	rule[63][28]=93;
	rule[63][29]=94;
	rule[64][30]=96;
	
	rule[65][3]=42;
	rule[65][20]=42;
	rule[65][27]=43;
	rule[65][28]=43;
	rule[65][29]=43;
	rule[65][30]=43;

	
}
void run_parsing_now(struct stack_t* stack,hash_table *colum, hash_table *row)
{
	FILE *fp = fopen ("output.txt", "r+");
	char input[100];
	fscanf(fp,"%s",input);	
	int x,y;
	int line_number=1;
	while(stack->stackSize!=0)
	{	
		printf("top of the stack:%s\n",top(stack));
		printf("input:%s\n",input);
		
		if(strcmp(top(stack),"$")==0 && strcmp(input,"$")){
			printf("loche ulfat hogaya\n");
			break;
		}
		while(strcmp(input,top(stack))==0)
		{
			printf("inp:pop:%s\n",input);
			if(strcmp(input,"TK_Identifier")==0)
			{
				fscanf(fp,"%s",input);

				printf("pop:%s\n",input);		
				line_number++;
			}
			if(strcmp(input,"TK_Integer")==0)
			{
				fscanf(fp,"%s",input);		
				printf("pop:%s\n",input);
				line_number++;

			}
			
			
			pop(stack);
			if(strcmp(top(stack),"$")==0 && strcmp(input,"$")){
				printf("loche ulfat hogaya\n");
				goto parsing_done;
			}
			fscanf(fp,"%s",input);	

			line_number++;	
		}
		if(strcmp(top(stack),"$")==0 && strcmp(input,"$")){
			printf("loche ulfat hogaya\n");
			break;
		}

		x=lookup_string(row,top(stack));
		printf("%s\n",top(stack));
		y=lookup_string(colum,input);		
		
		if(x==-1){
			printf("%d top of the stack:%s\n",line_number,top(stack));
			printf("input:%s\n",input);
			
			printf("type1-------\nError\n--------\n");
			break;
		}
		if(y==-1){
			printf("%d top of the stack:%s\n",line_number,top(stack));
			printf("input:%s\n",input);
			
			printf("type2-------\nError\n--------\n");
			break;
		}
		int rule_value=rule[x][y];

		printf("%d %d %d\n",x,y,rule_value);
		if(rule_value==-1)
		{
			printf("type3-------\nError\n--------\n");
			printf("%d top of the stack:%s\n",line_number,top(stack));
			printf("input:%s\n",input);
			fscanf(fp,"%s",input);
				printf("input:%s\n",input);
			fscanf(fp,"%s",input);
				printf("input:%s\n",input);
			fscanf(fp,"%s",input);
				printf("input:%s\n",input);
			fscanf(fp,"%s",input);
				printf("input:%s\n",input);
			fscanf(fp,"%s",input);	
			break;
		}
		if(rule_value==0)
		{
			pop(stack);
			continue;
		}
		int i;
		pop(stack);
		int l=RL[rule_value].size;
	
		for (i = 0; i <l; ++i)
		{
			push(stack,RL[rule_value].str[l-i-1]);
			printf("pushed:%s\n",RL[rule_value].str[l-i-1]);
		}
	}
	parsing_done:;
}

void parsing(FILE * fp,hash_table *colum, hash_table *row)
{
	struct stack_t* stack1=newStack();
	char str[100];
	push(stack1,"$");
	push(stack1,"<program>");
	int i=0;

    fp = fopen ("qwerty.txt", "r+");
    int len=0;
    i=0;
    while(fscanf(fp,"%d",&len)!=EOF)
    {	
    	RL[i].size=len;

    	int j;
    	//printf("%d %d ",i+1,len);
    	for (j = 0; j < len; ++j)
    	{
    		fscanf(fp,"%s",RL[i].str[j]);	
    		//printf("%s ",RL[i].str[j]);
    	}
    	//printf("\n");
    	i++;
    }
    close(fp);
    printf("%s\n",RL[98].str[0]);
    run_parsing_now(stack1,colum,row);
   // printf("%s\n",lookup_string(row , "unaryexp"));

}

int main(int argc, char const *argv[])
{
	int con=construct_terminal();
	construct_nonterminal();
    construct_rule();
	hash_table *colum,*row;
    int size_of_table = 197;
    colum = create_hash_table(size_of_table);
    row= create_hash_table(size_of_table);
    FILE * fp;
    fp = fopen ("terminal.txt", "r+");
    char str[100];
    int i=0;
    while(fscanf(fp,"%s",str)!=EOF)
    {
        add_string(colum,str,i++);
    }
    close(fp);
    fp = fopen ("int.txt", "r+");
    i=0;
    while(fscanf(fp,"%s",str)!=EOF)
    {
        add_string(row,str,i++);
    }
    close(fp);
    
    fp = fopen ("output.txt", "r+");
    parsing(fp,colum,row);
   	

   	return 0;
}