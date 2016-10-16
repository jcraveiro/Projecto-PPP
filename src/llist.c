#include "llist.h"
#include "client.h"

llist *llist_new()
{
  llist *new_list = (llist*) malloc(sizeof(llist));
  new_list->root = NULL;
  return new_list;
}

lnode *lnode_new(void *value)
{
  lnode *new_node = (lnode*) malloc(sizeof(lnode));
  new_node->value = value;
  new_node->next = NULL;
  return new_node;
}

lnode *_llist_insert_rec(lnode *where, void *value)
{
  if (where == NULL)
  {
    where = lnode_new(value);
    return where;
  }

  where->next = _llist_insert_rec(where->next, value);
  return where;
}

void llist_insert(llist *which_llist, void *value)
{
  which_llist->root = _llist_insert_rec(which_llist->root, value);
}

lnode *_llist_find_rec(lnode *where, void *find_value)
{
  if (where == NULL)
  {
    return NULL;
  }

  if (where->value == find_value)
  {
    return where;
  }

  return _llist_find_rec(where->next, find_value);
}

lnode *llist_find(llist *which_llist, void *value)
{
  return _llist_find_rec(which_llist->root, value);
}

lnode *_llist_remove_rec(lnode *where, void *value)
{
  if (where == NULL)
  {
    return where;
  }

  if (where->value == value)
  {
    lnode *temp = where->next;
    free(where);
    return temp;
  }

  where->next = _llist_remove_rec(where->next, value);

  return where;
}

void llist_remove(llist *which_llist, void *value)
{
  which_llist->root = _llist_remove_rec(which_llist->root, value);
}

void llist_remove_by_index(llist* which_llist, int index)
{
  int i = 0;

  lnode *aux = which_llist->root;
  for (i = 0; i < index; i++)
  {
    aux = aux->next;

    if (aux == NULL)
    {
      return;
    }
  }

  llist_remove(which_llist, aux->value);
}

int _llist_get_size_rec(lnode *where, int size)
{
  if (where == NULL)
  {
    return size;
  }

  return _llist_get_size_rec(where->next, size + 1);
}

int llist_get_size(llist *which_llist)
{
  int size = 0;

  return _llist_get_size_rec(which_llist->root,size);
}

lnode *_llist_swap(lnode *l1, lnode *l2)
{
  l1->next = l2->next;
  l2->next = l1;

  return l2;
}

void _llist_destroy_rec(lnode *where)
{
  if (where == NULL)
  {
    return;
  }

  lnode *aux = where;

  free(where);
  _llist_destroy_rec(aux->next);
}

void llist_destroy(llist *my_llist)
{
  _llist_destroy_rec(my_llist->root);
  free(my_llist);
}
