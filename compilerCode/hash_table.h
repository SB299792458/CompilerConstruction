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