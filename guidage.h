#ifndef _GUIDAGE_H
#define _GUIDAGE_H

int guidage_saisir_noeud_source();

int guidage_saisir_noeud_dest();

void guidage_afficher_noeuds (char tab_noeuds[][100],int nb_noeuds);

void guidage_noeud(char* nom_noeud, int nb_adj);

void guidage_distance(int dest,int **path);

#endif
