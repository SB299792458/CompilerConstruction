/*
36
Shikhar Brajesh 2012A7PS114P
Girish Rathi	2012A7PS347P
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//int X;
/*typedef struct _node
{
    int value;
    char *str;
    int type;
    struct _node *child[10];
    int nc;

    int blockNo;
    int lineNo;
}node;
*/
typedef struct _node
{
    int value;
    char *str;
    int type;
    struct _node *child[10];
    int nc;
    struct _node *par;
    int rules_info;
    int lineNo;
    int blockNo;
}node;

typedef struct  _lle
{
	char *data;
	int lineno;
	int block;
	char *datatype;
} lle;


typedef struct _ll
{
lle head;
char *hash_key;
}ll;


typedef struct _elementX {
    ll *container;
    struct _elementX *next;
} elementX;

typedef struct _hash_tableX {
    int size;   
    int scopeLevel;
    struct _hash_tableX* prev;
    elementX **table;
} hash_tableX;


hash_tableX *create_symbol_table(int size)
{
    hash_tableX *new_table;
    
    if ((new_table->table = malloc(sizeof(elementX *) * size)) == NULL) {
        return NULL;
    }
	int i=0;
    for(i=0; i<size; i++) new_table->table[i] = NULL;
	new_table->size = size;
	//new_table->scopeLevel=X++;

    return new_table;
}


unsigned int hashST(hash_tableX *hashtable, ll *to_insert)
{
    unsigned int hashval;
    hashval = 0;
    char *str=to_insert->hash_key;
    for(; *str != '\0'; str++) hashval = *str + (hashval << 5) - hashval;
    return hashval % hashtable->size;
}


elementX *lookup_elementX(hash_tableX *hashtable, ll *to_search)
{
    elementX *list;
    char *str=to_search->hash_key;
    unsigned int hashval = hashST(hashtable, to_search);
     for(list = hashtable->table[hashval]; list != NULL; list = list->next) 
    	{
        if (strcmp(str, list->container->hash_key) == 0) return list;
    	}
    return NULL;
}


int add_data(hash_tableX *hashtable, ll *to_add)
{
    elementX *new_list;
    elementX *current_list;
    unsigned int hashval = hashST(hashtable, to_add);
    if ((new_list = malloc(sizeof(elementX))) == NULL) return 1;
    current_list = lookup_elementX(hashtable, to_add);
    if (current_list != NULL) return 2;
    new_list->container = to_add;
    
    new_list->next = hashtable->table[hashval];
    hashtable->table[hashval] = new_list;

    return 0;
}


void destroy_table(hash_tableX *hashtable)
{
    int i;
    elementX *list, *temp;

    if (hashtable==NULL) return;

    for(i=0; i<hashtable->size; i++) {
        list = hashtable->table[i];
        while(list!=NULL) {
            temp = list;
            list = list->next;
            free(temp->container);
            free(temp->next);
            free(temp);
        }
    }

    /* Free the table itself */
    free(hashtable->table);
    free(hashtable);
}

ll *create(node *n)
{
int i=0;
ll *list;
 
lle e;
//e.key="name";
e.data=strdup(n->str);
int j= (int)n->type;
switch(j)
{
    case 2:
    e.datatype="int";
    break;
    case 7:
    e.datatype="char";
    break;
}

e.lineno=n->lineNo;
e.block=n->blockNo;

list->head=e;

return list;
}


int Insert(hash_tableX *ST,node *n)
{
//insert ll into symbol table
ll *new_entry=create(n);
add_data(ST, new_entry);
}

hash_tableX * OpenScope(hash_tableX *parentScope)
{
//create new symbol table
hash_tableX *ST=create_symbol_table(100);
ST->prev=parentScope;
if(parentScope!=NULL)
    ST->scopeLevel=parentScope->scopeLevel;
else
    ST->scopeLevel=0;

return ST;
}
hash_tableX * CloseScope(hash_tableX *tab)
{
//delete and close hash table
hash_tableX * parentScope=tab->prev;
destroy_table(tab);

return parentScope;
}

int LookUp(hash_tableX *ST,char *x)
{
//find in hash table
	ll *finder;
	finder->hash_key=x;
	elementX *result;
	result=lookup_elementX(ST , finder);
}