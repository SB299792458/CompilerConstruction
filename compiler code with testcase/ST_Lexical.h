/*36 T1
Shikhar Brajesh 2012A7PS114P
Girish Rathi 2012A7PS347P
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _elem
{
    int type;
    /*
    1=int
    2=char
    3=function
    4=use
    5=boolean
    */
    char *string;
    int blockno;
    int isGlobal;
    int lineno;
    
    struct _elem *next; 

}elem;

typedef struct _symbol_table {
    int size;       /* the size of the table */
    elem **table; /* the table elements */
	struct _symbol_table *prev;
	int blockCount;
	struct _symbol_table *child[100];
	int children;

} symbol_table;

symbol_table *create_symbol_tableGLOBAL(int size)
{
    symbol_table *new_table;
    
    if (size<1) return NULL; /* invalid size for table */

    /* Attempt to allocate memory for the table structure */
    if ((new_table = malloc(sizeof(symbol_table))) == NULL) {
        return NULL;
    }
    
    /* Attempt to allocate memory for the table itself */
    if ((new_table->table = malloc(sizeof(elem *) * size)) == NULL) {
        return NULL;
    }

    /* Initialize the elements of the table */
    int i=0;
    for(i=0; i<size; i++) new_table->table[i] = NULL;

    /* Set the table's size */
    new_table->size = size;
	new_table->prev=NULL;
	new_table->blockCount=0;
	new_table->children=0;
	return new_table;
}

symbol_table *create_symbol_table(symbol_table *par_table, int size)
{
    symbol_table *new_table;
    
    if (size<1) return NULL; /* invalid size for table */

    /* Attempt to allocate memory for the table structure */
    if ((new_table = malloc(sizeof(symbol_table))) == NULL) {
        return NULL;
    }
    
    /* Attempt to allocate memory for the table itself */
    if ((new_table->table = malloc(sizeof(elem *) * size)) == NULL) {
        return NULL;
    }

    /* Initialize the elements of the table */
    int i=0;
    for(i=0; i<size; i++) new_table->table[i] = NULL;

    /* Set the table's size */
    new_table->size = size;
	new_table->prev=par_table;
	new_table->children=0;
    return new_table;
}


unsigned int symbol(symbol_table *symboltable, char *str)
{
    unsigned int symbolval;
    symbolval = 0;
    for(; *str != '\0'; str++) symbolval = *str + (symbolval << 5) - symbolval;
    return symbolval % symboltable->size;
}


symbol_table* PrevScope(symbol_table *tab)
{
//delete and close hash table
symbol_table *parentScope=tab->prev;
//destroy_table(tab);
return parentScope;
}

symbol_table* CloseScope(symbol_table *tab)
{
//delete and close hash table
symbol_table *parentScope=tab->prev;
//destroy_table(tab);
return parentScope;
}

int lookup_symbol(symbol_table *symboltable, char *str)
{
    elem *list;
    unsigned int symbolval = symbol(symboltable, str);
     while(symboltable!=NULL)
     {

     for(list = symboltable->table[symbolval]; list != NULL; list = list->next) {
        /*if (strcmp(str, list->string) == 0)
       	 printf("%d",list->type);
       */
        if (strcmp(str, list->string) == 0 && list->type != 4 ) 
    	    {
        	printf("%d\n",list->type);
        	return list->type; //return type on finding element with same symbol in correct scope
        	}
    
    	}
    		symboltable = PrevScope(symboltable);
    }
    return -1;
}
int add_symbol_lexical(symbol_table *symboltable, char *type, char *str,int line, int block )
{
    printf("%s\n",type);
    elem *new_list;
    elem *current_list;
    unsigned int symbolval = symbol(symboltable, str);
    if ((new_list = malloc(sizeof(elem))) == NULL) return 1;
    
    new_list->string = strdup(str);
    new_list->lineno=line;
    new_list->blockno=block;
    /*
    1=int
    2=char
    3=function
    4=use
    5=boolean
    */
    if(strcmp(type,"int\0")==0 || strcmp(type,"char\0")==0 || strcmp(type,"void\0")==0 )
    {
    if(strcmp(type,"int\0")==0)	
    new_list->type =1;
    if(strcmp(type,"char\0")==0)
    new_list->type =2;
    if(strcmp(type,"void\0")==0)
    new_list->type =3;
	
	//ensure that it has not been declared before
	int flag=0;
	elem *list;
     		for(list = symboltable->table[symbolval]; list != NULL; list = list->next) {
        		if (strcmp(str, list->string) == 0 && list->type != 4 ) 
       	 		{
    			printf("\nError: Multiple declaration of same variable-> %s\n",list->string);	
    			flag=1;
	    		}
    
   			}


    }

    //Check: Variable used is declared in scope
    if(strcmp(type,"use\0")==0)
    {	
    	elem *list;
    	int flag=0;
    	new_list->type =4;
    		while(symboltable!=NULL)
     		{

     		for(list = symboltable->table[symbolval]; list != NULL; list = list->next) {
        		if (strcmp(str, list->string) == 0 && list->type != 4 ) 
       	 		{
    			new_list->next=symboltable->table[symbolval];
    			symboltable->table[symbolval] = new_list;
    			flag=1;
	    	//	printf("%d",list->type);
        	//	return list->type; //return type on finding element with same symbol in correct scope
        		}
    
   			}
    		symboltable = PrevScope(symboltable);
		    }
		    if(flag==0)
		    printf("\nError: cannot store undeclared var -> %s \n",str);
      		

    }else
    {
    new_list->next=symboltable->table[symbolval];
    symboltable->table[symbolval] = new_list;
	}
  //  printf("done : lexical analysis -> symbol table\n");
    return 0;
}

/*
void destroy_table(symbol_table *hashtable)
{
    int i;
    elem *list, *temp;

    if (hashtable==NULL) return;

    for(i=0; i<hashtable->size; i++) {
        list = hashtable->table[i];
        while(list!=NULL) {
            temp = list;
            list = list->next;
            //free(temp->container);
            free(temp->next);
            free(temp);
        }
    }

    //
    free(hashtable->table);
    free(hashtable);
}*/

symbol_table *gotoblock(symbol_table *ST, int num)
{

	int i=0;
	while(ST->child[i]!=NULL)
     		{

     			if (ST->child[i]->blockCount == num) 
       	 		{
       	 		printf("\n%d\n",ST->child[i]->blockCount);
				return ST->child[i]; 
    			}
    			/*else if (ST->child[i]->blockCount == num %)
    			{

    			}
    			*/
 		    i++;
		    }

}
