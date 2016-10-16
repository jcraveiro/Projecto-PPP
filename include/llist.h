#ifndef LLIST_HEADER
#define LLIST_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * The abstract node for linked lists, values are pointed to in ->value.
 */
typedef struct lnode
{
  struct lnode *next;
  void *value;
} lnode;

/**
 * The simplistic llist structure, holding only its root.
 */
typedef struct llist
{
  lnode *root;
} llist;

/**
 * Allocates memory for and returns a new linked list.
 */
llist *llist_new();

/**
 * Allocates memory for and returns a new lnode.
 */
lnode *lnode_new(void *value);

/**
 * Recursive function to insert a new node into an existing linked list.
 */
lnode *_llist_insert_rec(lnode*, void*);

/**
 * Inserts a new node to a linked list.
 */
void llist_insert(llist*, void*);

/**
 * Recursive function to find an element in a linked list.
 */
lnode *_llist_find_rec(lnode*, void*);

/**
 * Finds an element in a linked list.
 */
lnode *llist_find(llist*, void*);

/**
 * Recursive funtion to remove an element from a linked list.
 */
lnode *_llist_remove_rec(lnode*, void*);

/**
 * Removes an element from a linked list.
 */
void llist_remove(llist*, void*);

/**
 * Removes an element from a linked list, by its index in it.
 */
void llist_remove_by_index(llist*, int);

/**
 * Recursive function to get the size of a linked list.
 */
int _llist_get_size_rec(lnode*, int);

/**
 * Gets the size of a linked list.
 */
int llist_get_size(llist*);

/**
 * Swaps two nodes in a linked list.
 */
lnode *_llist_swap(lnode *, lnode *);

/**
 * Recursive function to destroy nodes of a llist.
 */
void _llist_destroy_rec(lnode*);

/**
 * Function that calls llist_destroy_rec and frees llist.
 */
void llist_destroy(llist*);

#endif
