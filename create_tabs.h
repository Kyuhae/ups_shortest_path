#ifndef _CREATE_TABS_H
#define _CREATE_TABS_H

//Cette fonction vas crée une matrice contenant la distance entre chaque noeud et sont adjacent
int** Create_Tab_Noeud(char nom_fich[], int *nb_noeuds,char tab_noeuds_in[][100],char tab_adj[][100]);

void Delete_tab(int** tab, int nb_noeuds);

#endif