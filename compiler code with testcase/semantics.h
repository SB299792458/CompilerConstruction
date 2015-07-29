#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
//#include "ST_Lexical.h"
int type_check(symbol_table *ST, int val)
{
char *one="result";
char *two="y";
   /*
    1=int
    2=char
    3=function
    4=use
   -1=not in current scope
   */
int ans=lookup_symbol(ST,one);
printf("Block count = %d ans= %d ", ST->blockCount, ans );
gotoblock(ST,0);

}

int overloading_check(symbol_table *symboltable, char *var)
{
	int flag=0;
	elem *list;
  int countx=0;
			unsigned int symbolval = symbol(symboltable, var);
    		for(list = symboltable->table[symbolval]; list != NULL; list = list->next) {
        		if (strcmp(var, list->string) == 0 ) 
       	 		{
              countx++;
    			}
        }

         if(countx>1)
          {
          printf("\nError: Use available function name-> %s\n",list->string); 
          flag=1;
          }
    
   		return flag;

}