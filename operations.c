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
    
//operation function    
struct node *operations (FILE *fp, struct node *list){    

		//read log file operation and name
        struct node *new_node;
        new_node = malloc(sizeof(struct node));

        fscanf(fp, "%[^,],", new_node->operation_type);
        
        //birth operation
        if(strcmp(new_node->operation_type,"birth")==0)
        {
            //read name and number of birth to add
            fscanf(fp,"%[^,],%d\n",new_node->name,&new_node->number);

            for(struct node *q = list; q != NULL; q = q->next)
            {
                if(strcmp(new_node->name,q->name)==0)
                {
                    q->number += new_node->number;
                    
                }
            }
            return list;
        }

        //transfer in operation
        if(strcmp(new_node->operation_type,"transfer_in")==0)
        {
            //read transfer name, location and number
            fscanf(fp,"%[^,],%[^,],%d\n",new_node->name,new_node->location,&new_node->number);

            
            //If animal exists in the system (old)
            for(struct node *q = list; q != NULL; q = q->next)
            {
                if(strcmp(new_node->name,q->name)==0 && q->number > 0)
                {
                    q->number += new_node->number;
                    
                    return list;
                    break;
                }
            }
            
            //If the animal does not exist in the system (new)
            new_node->next = list;
            return new_node;//store node to list
        }

        //relocate operation
        if(strcmp(new_node->operation_type,"relocate")==0)
        {
            //read location and target location
            fscanf(fp,"%[^,],%s\n",new_node->location,new_node->target_location);

            for(struct node *q = list; q != NULL; q = q->next)
            {
                if(strcmp(new_node->location,q->location)==0)
                {
                    strcpy(q->location,new_node->target_location);
                    
                }
            }
            return list;
        }

        //death and transfer out operation
        if(strcmp(new_node->operation_type,"death")==0 || strcmp(new_node->operation_type,"transfer_out")==0)
        {
            //read name and number of birth to add
            fscanf(fp,"%[^,],%d\n",new_node->name,&new_node->number);

            for(struct node *q = list; q != NULL; q = q->next)
            {
                if(strcmp(new_node->name,q->name)==0)
                {
                    q->number -= new_node->number;
                    
                }
            }
            
            return list;

        }

}

