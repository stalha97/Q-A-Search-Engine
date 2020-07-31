#include <iostream>
#include <malloc.h>
#include <string>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include<io.h>  // To make directories
#include <bits/stdc++.h>  // To store a complete text file in a string
#include<conio.h>

using namespace std;

//****************************************************
typedef struct _document
{
    char *docName;
    int termFreq;
    float termRatio;

    _document()
    {
        docName=NULL;
        termFreq=0;
        termRatio=0;
        next=NULL;
    }
     document()
    {
        docName=NULL;
        termFreq=0;
        termRatio=0;
        next=NULL;
    }

    struct _document *next=NULL;
}document;

typedef struct _list_t_
{
        char *str;
        int docFreq;
        document *docs;

        _list_t_()
        {
            docFreq=0;
            docs=NULL;
            next=NULL;
        }

        _list_t_ *next;
} list_t;

typedef struct _hash_table_t_
{
        int size; /* the size of the table */
        list_t **table; /* the table elements */
} hash_table_t;

//****************************************************
void StringToHash(string data,string docName, hash_table_t *table);
void HashToFile(hash_table_t *table);
void HashToFile_2(hash_table_t *table);

//****************************************************

hash_table_t *create_hash_table(int size);
unsigned int hash(hash_table_t *hashtable, char *str);
list_t *lookup_string(hash_table_t *hashtable, char *str);
int add_string(hash_table_t *hashtable, char *str);
int delete_string(hash_table_t *hashtable, char *str);
void free_table(hash_table_t *hashtable);
int count_strings(hash_table_t *hashtable);

//****************************************************
hash_table_t *create_hash_table(int size)
{
    hash_table_t *new_table;

    if (size<1)
    {
        cout<<"Invalid size"<<endl;
        return NULL; /* invalid size for table */
    }
    /* Attempt to allocate memory for the table structure */
    if ((new_table = (hash_table_t*)malloc(sizeof(hash_table_t))) == NULL)
    {
        cout<<"Memory not allocated"<<endl;
        return NULL;
    }
    /* Attempt to allocate memory for the table itself */
    if ((new_table->table = (list_t **) malloc(sizeof(list_t *) * size)) == NULL)
    {
        cout<<"Memory not allocated to table inside"<<endl;
        return NULL;
    }

    /* Initialize the elements of the table */
    for(int i=0; i<size; i++)
    {
        new_table->table[i] = NULL;
    }
    /* Set the table's size */
    new_table->size = size;

    return new_table;
}

//****************************************************

unsigned int hash(hash_table_t *hashtable, char *str)
{
    unsigned int hashval;

    /* we start our hash out at 0 */
    hashval = 0;

    /* for each character, we multiply the old hash by 31 and add the current
    * character. Remember that shifting a number left is equivalent to
    * multiplying it by 2 raised to the number of places shifted. So we
    * are in effect multiplying hashval by 32 and then subtracting hashval.
    * Why do we do this? Because shifting and subtraction are much more
    * efficient operations than multiplication.
    */
    for(  ; *str != '\0'; str++)
    {
        hashval = *str + (hashval << 5) - hashval;
    }
    /* we then return the hash value mod the hashtable size so that it will
    * fit into the necessary range
    */
    return hashval % hashtable->size;
}

//****************************************************

list_t *lookup_string(hash_table_t *hashtable, char *str)
{
    list_t *list;
    unsigned int hashval = hash(hashtable, str);

    /* Go to the correct list based on the hash value and see if str is
    * in the list. If it is, return return a pointer to the list element.
    * If it isn't, the item isn't in the table, so return NULL.
    */
    for(list = hashtable->table[hashval]; list != NULL; list = list->next)
    {
        if (strcmp(str, list->str) == 0) return list;
    }

    return NULL;
}

//****************************************************

int add_string(hash_table_t *hashtable, char *str)
{
    list_t *new_list;
    list_t *current_list;
    unsigned int hashval = hash(hashtable, str);

    /* Attempt to allocate memory for list */
    if ((new_list =new list_t) == NULL) return 1;

    /* Does item already exist? */
    current_list = lookup_string(hashtable, str);
    /* item already exists, don't insert it again. */
    if (current_list != NULL) return 2;
    /* Insert into list */
    new_list->str = strdup(str);
    new_list->next = hashtable->table[hashval];
    hashtable->table[hashval] = new_list;

    return 0;
}

//****************************************************

void free_table(hash_table_t *hashtable)
{
    int i;
    list_t *list, *temp;

    if (hashtable==NULL) return;

    /* Free the memory for every item in the table, including the
    * strings themselves.
    */
    for(i=0; i<hashtable->size; i++)
    {
        list = hashtable->table[i];
        while(list!=NULL)
        {
            temp = list;
            list = list->next;
            free(temp->str);
            free(temp);
        }
    }

    /* Free the table itself */
    free(hashtable->table);
    free(hashtable);
}

//****************************************************

int delete_string(hash_table_t *hashtable, char *str)
{
    list_t *list, *prev;
    unsigned int hashval = hash(hashtable,str);

    /* find the string in the table keeping track of the list item
    * that points to it
    */
    for(prev=NULL, list=hashtable->table[hashval];
    list != NULL && strcmp(str, list->str);
    prev = list,
    list = list->next);

    /* if it wasn't found, return 1 as an error */
    if (list==NULL) return 1; /* string does not exist in table */

    /* otherwise, it exists. remove it from the table */
    if (prev==NULL) hashtable->table[hashval] = list->next;
    else prev->next = list->next;

    /* free the memory associate with it */
    free(list->str);
    free(list);

    return 0;
}

//****************************************************

int count_strings(hash_table_t *hashtable)
{
    int i, count = 0;
    list_t *list;

    /* error check to make sure hashtable exists */
    if (hashtable==NULL) return -1;

    /* go through every index and count all list elements in each index */
    for(i=0; i<hashtable->size; i++) {
    for(list=hashtable->table[i]; list != NULL; list = list->next) count++;
    }

    return count;
}

void printHash(hash_table_t *table)
{
    for(int i=0;i<table->size;i++)
    {
        list_t *list;
        list=new list_t;

        for(list=table->table[i]; list != NULL; list = list->next)
        {
            cout<<"Term___________: "<<list->str<<endl;
            cout<<"docFreq: "<<list->docFreq<<endl<<endl;

            document *doc=list->docs;

            for(doc=list->docs; doc!=NULL ; doc=doc->next)
            {
                cout<<"+++DocName: "<<doc->docName<<endl;
                cout<<"TermRatio: "<<doc->termRatio<<endl;

                cout<<endl;
            }
            cout<<"************************************"<<endl;

        }
    }
}
