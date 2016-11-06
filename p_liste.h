#ifndef _P_LISTE_H_
#define _P_LISTE_H_

#include <stdbool.h>

typedef struct liste *Liste;



//CONSTRUCTORS
/**
 * Cette fonction peut prendre en paramètre soit:
 *- un pointeur vers une Liste; initialisé à NULL
 *- un pointeur vers une Liste déjà initialisée
 */
void liste_initialiser (Liste *list);

/**
 * Ajoute un noeud en tête de liste
 * @pre list doit être initialisée 
 * (ne peut pas etre appelé sur une liste libérée, ou non-initialisée)
 */
void liste_push_front(Liste list, int cle, int poids);


//DESTRUCTOR
/**
 * libere une liste
 */
void liste_liberer(Liste *list);


//ACCESSORS
//GETTERS
/**
 * retourne true si la liste est vide
 * @pre list doit être initialisée 
 * (ne peut pas etre appelé sur une liste libérée, ou non-initialisée)
 */
bool liste_vide(Liste list);

/**
 * Supprime le premier element de la liste et met a jour les entiers désignés en paramètre
 * @pre list doit être initialisée 
 * (ne peut pas etre appelé sur une liste libérée, ou non-initialisée)
 */
void liste_pop_front(Liste list, int *cle, int *poids);


//SETTERS
/**
 * Ajoute un noeud en fin de liste
 * @pre list doit être initialisée 
 * (ne peut pas etre appelé sur une liste libérée, ou non-initialisée)
 */
void liste_push_back(Liste list, int cle, int poids);




// ***************  Iterator  ****************


typedef struct list_iterator* lIterator;


/*
 * initialise l'iterateur pointé par iterator.
 * Les variables de type lIterator doivent êtres initialisées à NULL.
 */
void lIterator_initialise(lIterator* iterator, Liste* list);

void lIterator_destroy(lIterator* iterator);

bool lIterator_hasNext(lIterator iterator);


/**
 * Positionne l'iterateur a la position suivante si elle existe. Aucun effet sinon.
 */
void lIterator_next(lIterator* iterator);

/**
 * Positionne l'iterateur au début de la liste
 * @pre: la liste ne peut pas être vide
 */
void lIterator_begin(lIterator* iterator);


/**
 * Retourne l'element courant
 * @pre: l'itérateur doit avoir été déplacé au moins une fois par une des fonctions:
 * lIterator_begin; lIterator_end; lIterator_next ou lIterator_previous
 */
void lIterator_current(lIterator iterator, int *cle, int *poids);



#endif //_P_LISTE_H_
