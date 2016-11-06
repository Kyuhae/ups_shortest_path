#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include "p_liste.h"

typedef struct cell {
        int cle;
        int poids;
        struct cell *next;
        struct cell *prev; 
} *Cell;

struct liste {
        Cell sentinelle;
};


void liste_initialiser (Liste *list) {
  assert(list != NULL);
  
  if (*list != NULL ) 
    liste_liberer(list);
  
  *list = malloc(sizeof(struct liste));
  if (*list == NULL) {
    printf("initialiser_liste: malloc error");
    exit(EXIT_FAILURE);
  }
  (*list)->sentinelle = malloc(sizeof(struct cell));
  if ((*list)->sentinelle == NULL) {
    printf("initialiser_liste: malloc error:");
    exit(EXIT_FAILURE);
  }
  (*list)->sentinelle->next = (*list)->sentinelle;
  (*list)->sentinelle->prev = (*list)->sentinelle;
  (*list)->sentinelle->cle = -1;
  (*list)->sentinelle->poids = -1;
}

 
void liste_liberer(Liste *list) {
  (*list)->sentinelle->cle = -1;
  Cell n = (*list)->sentinelle->next;
  while (n->cle != -1) {
    n = n->next;
    free(n->prev);
  } 
  free((*list)->sentinelle);
  free(*list);
  *list = NULL;
}


void liste_push_front(Liste list, int cle, int poids) {
  assert(list != NULL && cle >= 0 && poids > 0);
  struct cell *new_cell = malloc(sizeof(struct cell));
  if (new_cell == NULL) {
    printf("err malloc");
    exit(EXIT_FAILURE);
  }
  new_cell->cle = cle;
  new_cell->poids = poids;
  new_cell->next = list->sentinelle->next;
  new_cell->prev = list->sentinelle;
  list->sentinelle->next = new_cell;
  new_cell->next->prev = new_cell; 
}


void liste_push_back(Liste list, int cle, int poids) {
  assert(list != NULL && cle > 0 && poids > 0);
  struct cell *new_cell = malloc(sizeof(struct cell));
  if (new_cell == NULL) {
    printf("err malloc");
    exit(EXIT_FAILURE);
  }
  new_cell->cle = cle;
  new_cell->poids = poids;
  new_cell->next = list->sentinelle;
  new_cell->prev = list->sentinelle->prev;
  list->sentinelle->prev = new_cell;
  new_cell->prev->next = new_cell;  
}


void liste_pop_front(Liste list, int *cle, int *poids){
  assert(list != NULL);
  if (liste_vide(list)) return;
  *cle = list->sentinelle->next->cle;
  *poids = list->sentinelle->next->poids;
  list->sentinelle->next = list->sentinelle->next->next;
  free(list->sentinelle->next->prev);
  list->sentinelle->next->prev = list->sentinelle; 
}


bool liste_vide(Liste list) {
  assert(list != NULL);
  return (list->sentinelle->next == list->sentinelle && 
          list->sentinelle->prev == list->sentinelle);
}


//************ Iterator *************

struct list_iterator {
        Liste list;
        Cell current;
};


void lIterator_initialise(lIterator* iterator, Liste* list) {
  assert(iterator != NULL && list != NULL);
  if (*iterator != NULL)
    free(*iterator);
  *iterator = malloc(sizeof(struct list_iterator));
  (*iterator)->list = *list;
  (*iterator)->current = (*list)->sentinelle; 
}

void lIterator_destroy(lIterator* iterator) {
  assert(iterator != NULL);
  free(*iterator);
  *iterator = NULL;
}

bool lIterator_hasNext(lIterator iterator) {
  return iterator->current->next != iterator->list->sentinelle;
}

void lIterator_next(lIterator* iterator) {
  if (lIterator_hasNext(*iterator))
    (*iterator)->current = (*iterator)->current->next;
}

void lIterator_begin(lIterator* iterator) {
  assert(iterator != NULL && *iterator != NULL && !liste_vide((*iterator)->list));
  (*iterator)->current = (*iterator)->list->sentinelle->next;
}

void lIterator_current(lIterator iterator, int *cle, int *poids) {
  assert(!liste_vide(iterator->list)); 
  *cle = iterator->current->cle;
  *poids = iterator->current->poids;
}
