
#ifndef _P_GRAPHE_H_
#define _P_GRAPHE_H_

#include "p_liste.h"

typedef struct s_graphe *Graphe;


Graphe graphe_initialiser(int nbNoeuds);

/**
 * Determine si un graphe est graphe_vide
 * @pre graphe doit avoir été initialisé
 */
bool graphe_vide(Graphe graphe);


/**
 * Ajoute un noeud au graphe
 * @pre graphe doit avoir été initialisé
 */
void graphe_ajouter_noeud(Graphe graphe, int cle, int *arretes);


/**
 * crée un iterateur sur les noeuds adjacents au noeud passé en paramètre, et le place au premier noeud
 * la clé de ce noeud ainsi que le poids de l'arrête concernée sont stockées dans cle et poids
 * @pre graphe doit avoir été initialisé, et ne peut etre vide. Le noeud doit avoir au moins un noeud adjacent
 */
lIterator graphe_initialiser_iterateur_adj(Graphe graphe, int noeud, int *cle, int *poids);


/**
 * avance l'iterateur sur le prochain noeud adjacent.
 * la clé de ce noeud ainsi que le poids de l'arrête concernée sont stockées dans cle et poids
 * @return false si l'iterateur n'a pas pu avancer (fin des noeuds adjacents), true sinon
 */
bool graphe_iterateur_adj_next(lIterator iterateur, int noeud, int *cle, int *poids);


/**
 * detruit l'iterateur passé, et le met à NULL
 */
void graphe_iterateur_detruire(lIterator *iterateur);


/**
 * Détruit un graphe et libère la mémoire qu'il occupait
 * @pre !graphe_vide(graphe)
 */
void graphe_liberer(Graphe *graphe);


#endif //_P_GRAPHE_H_