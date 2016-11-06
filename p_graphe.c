#include "p_graphe.h"
#include "p_liste.h"
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

struct s_graphe {
  Liste *TabAdjacents;
  int nbNoeuds;
};

Graphe graphe_initialiser(int nbNoeuds) {
  Graphe graphe = malloc(sizeof(struct s_graphe));
  if (graphe == NULL) {
    printf("graph_init: malloc error");
    exit(EXIT_FAILURE);
  }
  graphe->TabAdjacents = malloc(nbNoeuds * sizeof(Liste));
  graphe->nbNoeuds = 0;
  return graphe;
}

bool graphe_vide(Graphe graphe) {
  assert(graphe != NULL);
  return graphe->nbNoeuds == 0;
}

void graphe_ajouter_noeud(Graphe graphe, int cle, int *arretes) {
  assert(graphe != NULL && arretes != NULL && cle >= 0);
  Liste liste = NULL;
  liste_initialiser(&liste);
  graphe->TabAdjacents[graphe->nbNoeuds] = liste;
  for (int i = 0; arretes[i] != -1; i += 2) 
    liste_push_front(graphe->TabAdjacents[graphe->nbNoeuds], arretes[i], arretes[i+1]);
  graphe->nbNoeuds ++;
}

void graphe_liberer(Graphe *graphe) {
  assert(graphe != NULL && *graphe != NULL);
  for (int i = 0; i < (*graphe)->nbNoeuds; i++)
    liste_liberer(&((*graphe)->TabAdjacents[i]));
  free((*graphe)->TabAdjacents);
  free(*graphe);
}

lIterator graphe_initialiser_iterateur_adj(Graphe graphe, int noeud, int *cle, int *poids) {
  assert(graphe != NULL && cle != NULL && poids != NULL);
  assert(!graphe_vide(graphe) && !liste_vide(graphe->TabAdjacents[noeud]));
  lIterator iterateur = NULL;
  lIterator_initialise(&iterateur, &(graphe->TabAdjacents[noeud]));
  lIterator_begin(&iterateur);
  lIterator_current(iterateur, cle, poids);
  return iterateur;
}

bool graphe_iterateur_adj_next(lIterator iterateur, int noeud, int *cle, int *poids) {
  assert(iterateur != NULL && cle != NULL && poids != NULL);
  
  if (!lIterator_hasNext(iterateur)) return false;
  lIterator_next(&iterateur);
  lIterator_current(iterateur, cle, poids);
  return true;
}

void graphe_iterateur_detruire(lIterator *iterateur) {
  lIterator_destroy(iterateur);
  *iterateur = NULL;
}

