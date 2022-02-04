/* Name: Zaber Raiyan Choudhury
   NetID: zaberraiyan
   Description: This code contains my solution for the tenth
               project of COP3514.002
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "operations.h"
#define NAMELENGTH 100
#define LOCATIONLENGTH 3

void clear_list (struct node *list);
struct node *delete_node(struct node *list, int n);

//structure to store databases in linked lists
struct node
{
    char operation_type[NAMELENGTH + 1];//of animals
    char name[NAMELENGTH + 1];//of animals
    char location[LOCATIONLENGTH + 1];//of animals
    char target_location[LOCATIONLENGTH + 1];//used for relocate only (new location)
    int number;//of animals
    struct node *next;
};

int main(int argc, char *argv[]){

    //first node declared
    struct node *list = NULL;

    FILE *fp;

    //opening database backup file on command line
    fp=fopen(argv[1],"r");
    if(fp ==NULL){
        printf("Could not open file\n");
        return 1;
    }

	    //storing lines on linked list
	    while(!feof(fp) && !ferror(fp))
	    {   
		    struct node *new_node;
            new_node = malloc(sizeof(struct node));

            fscanf(fp, "%[^,],%[^,],%d\n", new_node->name, new_node->location, &new_node->number);
		
            new_node->next = list;
            list = new_node;
	    }

    //Closing database backup file
    if(fclose(fp) == EOF){
    printf("Could not close file!\n");
    return 1;
    }


    //opening database log file on command line
    fp=fopen(argv[2],"r");
    if(fp ==NULL){
        printf("Could not open file\n");
        return 1;
    }

	    //conducting operations on linked list
	    while(!feof(fp) && !ferror(fp))
	    {   
		    list = operations(fp,list);
            list = delete_node(list,0);
        }

    //Closing database log file
    if(fclose(fp) == EOF){
    printf("Could not close file!\n");
    return 1;
    }
    

    //Creating database.txt
    fp=fopen("database.txt","w");
    if(fp ==NULL){
        printf("Could not open file\n");
        return 1;
    }

        //Writing updated list on database txt
        for(struct node *q = list; q != NULL; q = q->next){
        
            fprintf(fp,"%s,%s,%d\n",q->name, q->location, q->number);
        }

    //Closing database.txt
    if(fclose(fp) == EOF){
    printf("Could not close file!\n");
    return 1;
    }
    
   
    //clear list
    clear_list(list);

    return 0;
}

//clear list function
void clear_list (struct node *list)
{
    struct node *r;
    while(list != NULL)
    {
        r = list;
        list = list->next;
        free(r);
    }

}

//delete animals with 0 numbers
struct node *delete_node(struct node *list, int n)
{
    struct node *cur, *prev;

    for(cur = list, prev = NULL; cur != NULL && cur->number > n; prev = cur, cur = cur->next);

    //n was not found
    if(cur == NULL)
        return list;
    
    //n is in the first node
    if(prev == NULL)
        list = list -> next;
    //n is in some other node
    else
        prev->next = cur -> next;
    
    //node is removed
    free(cur);
    
    return list;

}