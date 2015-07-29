#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _element {
    char *string;
    char *token;
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


element *lookup_string(hash_table *hashtable, char *str)
{
    element *list;
    unsigned int hashval = hash(hashtable, str);
     for(list = hashtable->table[hashval]; list != NULL; list = list->next) {
        if (strcmp(str, list->string) == 0) return list;
    }
    return NULL;
}


int add_string(hash_table *hashtable, char *str, char *tok)
{
    element *new_list;
    element *current_list;
    unsigned int hashval = hash(hashtable, str);
    if ((new_list = malloc(sizeof(element))) == NULL) return 1;
    current_list = lookup_string(hashtable, str);
    if (current_list != NULL) return 2;
    new_list->string = strdup(str);
    new_list->token = strdup(tok);
    new_list->next = hashtable->table[hashval];
    hashtable->table[hashval] = new_list;
    return 0;
}



char word[100];
int isAlpha(char ch){
	if((ch>=97 && ch<='z') || (ch>='A' && ch<='Z') )
		return 1;
	else
		return 0;
}
int isNum(char ch)
{
	if((ch>='0' && ch<='9'))
		return 1;
	else
		return 0;
}
void print_word(FILE *fp,int len){
	int i;
	for (i = 0; i <len; ++i)
	{
		fprintf(fp,"%c",word[i]);
	}
	
}
int main(int argc, char const *argv[])
{
	int x;	
	x=0;
	char ch=getchar();
	hash_table *my_hash_table;
	int size_of_table = 197;
	my_hash_table = create_hash_table(size_of_table);
	add_string(my_hash_table,"function", "TK_Function");
    add_string(my_hash_table,"while", "TK_While");
    add_string(my_hash_table,"boolean", "TK_Bool");
    add_string(my_hash_table,"create", "TK_Create");
	add_string(my_hash_table,"int", "TK_Int");
	add_string(my_hash_table,"char", "TK_Char");
	add_string(my_hash_table,"input", "TK_Input");
	add_string(my_hash_table,"output", "TK_Output");
	add_string(my_hash_table,"if", "TK_If");
    add_string(my_hash_table,"else", "TK_Else");
    add_string(my_hash_table,"array", "TK_Array");
    add_string(my_hash_table,"true", "TK_True");
    add_string(my_hash_table,"false", "TK_False");
    add_string(my_hash_table,"return", "TK_Return");
    add_string(my_hash_table,"next", "TK_Next");
    add_string(my_hash_table,"end", "TK_End");
    add_string(my_hash_table,"try", "TK_Try");
    add_string(my_hash_table,"catch", "TK_Catch");
    add_string(my_hash_table,"finally", "TK_Finally");
    add_string(my_hash_table,"constant", "TK_Constant");
    add_string(my_hash_table,"call", "TK_Call");
    add_string(my_hash_table,"dec", "TK_Dec");
    add_string(my_hash_table,"inc", "TK_Inc");
    add_string(my_hash_table,"main", "TK_Main");
    add_string(my_hash_table,"void", "TK_Void");
    
    FILE * fp;
   	fp = fopen ("output.txt", "w+");
	
	while(1)
	{
		if(ch==EOF)break;
		
		x=0;
		
		if(ch==' ' || ch=='\n' || ch=='\t'){
			ch=getchar();
			continue;
		}
		
		if(isAlpha(ch)){
			
			while(isAlpha(ch) || isNum(ch) )
			{
				word[x++]=ch;			
				ch=getchar();
			}
			word[x]='\0';
			element *ans=lookup_string(my_hash_table,word);
			if(NULL==ans)
			{
				fprintf(fp,"TK_Identifier ");
			}
			print_word(fp,x);
			fprintf(fp," \n");
			continue;
		}
		 if(isNum(ch))
		{
			x=0;
			while(isNum(ch))
			{	
				word[x++] = ch;			
				ch=getchar();	
			}
			fprintf(fp,"TK_Integer ");
			print_word(fp,x);
			fprintf(fp," \n");
			continue;
		}
		else if(ch=='{' || ch=='}' || 
				ch=='[' || ch==']' || 
				ch==';' || ch=='(' ||
				ch==')' || ch==34  ||
				ch==39	|| ch==',' ||
				ch=='%' || ch=='#' )
		{
			fprintf(fp,"%c\n",ch);
			ch=getchar();
			continue;	
		}
		else
		{
			switch (ch)
			{

				case ':':
					ch=getchar();
					switch (ch)
					{
						case '=' :
							fprintf(fp,":=\n");
							break;
						default:
							fprintf(fp,":\n");
							continue;
					}
					break;
				case '=':
					ch=getchar();
					switch (ch)
					{
						case '=' :
							fprintf(fp,"==\n");
							break;
						default:
							fprintf(fp,"chutiya\n");
							continue;
					}
					break;
				case '<':
					ch=getchar();
					switch (ch)
					{
						case '=' :
							fprintf(fp,"<=\n");
							break;
						case '<' :
							fprintf(fp,"<<\n");
							break;	
						default :
							fprintf(fp,"<\n");
							continue;
					}
					break;
				case '>' :
					ch=getchar();
					switch (ch)
					{
						case '=' :
							fprintf(fp,">=\n");
							break;
						case '>':
						fprintf(fp,">> \n");
						break;
						default:
						fprintf(fp,">\n");
							continue;
					}
					break;
				case '!' :
					ch=getchar();
					switch (ch)
					{
						case '=' :
							fprintf(fp,"!= T\n");
						break;
						default:
							fprintf(fp,"! T\n");
							continue;
					}
					break;
				case '+' :
					ch=getchar();
					switch (ch)
					{
						case '+' :
							fprintf(fp,"++\n");
						break;
						default:
							fprintf(fp,"+\n");
							continue;
					}
					break;	

				case '-' :
					ch=getchar();
					switch (ch)
					{
						case '-' :
							fprintf(fp,"--\n");
						break;
						default:
							fprintf(fp,"-\n");
							continue;
					}
					break;	
				case '*' :
					fprintf(fp,"*\n");
					break;
					
				case '/' :
					fprintf(fp,"/\n");
					break;
				case '|' :
					ch=getchar();
					switch (ch)
					{
						case '|' :
							fprintf(fp,"||\n");
						break;
						default:
							fprintf(fp,"|\n");
							continue;
					}
					break;	

				case '&' :
					ch=getchar();
					switch (ch)
					{
						case '&' :
							fprintf(fp,"&&\n");
						break;
						default:
							fprintf(fp,"&\n");
							continue;
					}
					break;	
				
				case '#' :
					ch=getchar();
					fprintf(fp,"#\n");
					continue;
				break;
				
			}
			ch=getchar();
		}
	}
	return 0;
}