#ifndef _LIST_NODES_H 
#define _LIST_NODES_H 


#include "tree.h"
#include <stdlib.h>





/**
*****************************NOTE**************************
This module has been designed in a way such that only one of the two push_front and push_back will work.
So once the function pointer has been set. It stays that way. 
A push_back command followed by a push_front command will not yield the desired result.
**/

/*
 * list_nodes:
 * A data structure to maintain a list of nodes 
 * Has one variable for a node pointer , and the other for the next item in the list. 
 */ 
 
typedef struct list_nodes {
	struct list_nodes *next;
	node *x;
} list_nodes;
 


/*
 * List parameters :
 * head 
 * tail
 */ 
typedef struct list_param {
	list_nodes *head;
	list_nodes *tail;
} list_param;


static list_param l_param;




/*
 * popF , pushF : function pointers for the push and pop function.
 * can only be set once during an execution of the program
 * 
 */ 

node* (*popF)(list_nodes **);


node* (*pushF)(list_nodes **);





/*
 *The usual list operations 
 * 
 *pop_front : pops out the front element and returns the pointer to the node popped out 
 * 			  Note that it also modifies the list	
 *
 * 
 *pop_back : pops out the back element and returns the pointer to the node popped out 
 * 			  Note that it also modifies the list	
 *
 * 
 *push_front : pushes a given node to the front of the list   
 *
 *pop_back : pushes a given node to the back of the list   
 *
 *  
 * 
 *empty : returns true if list is empty. returns false otherwise 
 */  

node* pop_front(list_nodes **x);

node* pop_back(list_nodes **x);


node* pop(list_nodes **x);
node* push(list_nodes **x);


int push_front(list_nodes **list , node *n);

int push_back(list_nodes **list ,  node *n);

int empty(list_nodes *x);














/*
 * list_markings:
 * A primitive data structure to maintain a list of markings 
 * Has one variable for a node pointer , and the other for the next item in the list. 
 */ 
 
typedef struct list_markings {
	struct list_markings *next;
	wnat *x;
} list_markings;
 


/*
 *The usual list operations 
 * 
 *pop_frontM : pops out the front element and returns the pointer to the node popped out 
 * 			  Note that it also modifies the list	
 *push_frontM : pushes a given node to the front of the list   
 * 
 *emptyM : returns true if list is empty. returns false otherwise 
 */  

wnat* pop_frontM(list_markings **x);

int push_frontM(list_markings **list ,wnat *n);

int emptyM(list_nodes *x);






















#endif  /* _LIST_NODES_H */
