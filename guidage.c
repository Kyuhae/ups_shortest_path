#include <stdio.h>
#include <string.h>
#include "guidage.h"

int guidage_saisir_noeud_source(){
    int src;
    printf("\n\n******///////////////////////////////////////////******");
    printf("\n\nVeuillez saisir votre lieu de début du parcours:");
    scanf("%d",&src);
    return src;
    
}

int guidage_saisir_noeud_dest(){
    int dest;
    printf("\n\n******///////////////////////////////////////////******");
    printf("\n\nVeuillez saisir votre destination:");
    scanf("%d",&dest);
    return dest;
}

void guidage_afficher_noeuds (char tab_noeuds[][100],int nb_noeuds){
    
    int i;
    printf("\nNuméro de borne --> Nom du lieu");
    for( i = 0; i<nb_noeuds; i++){
        printf("\n %d    -->    %s",i,tab_noeuds[i]);
    }
    printf("\n");
}

void guidage_noeud(char* nom_noeud, int nb_adj){
    printf("\nVeuillez suivre la bande rugueuse %d --> %s",nb_adj,nom_noeud);
}

void guidage_distance(int dest,int **path){
    int i ;
    for( i = 0; path[dest][i] != -1; i++ ){
        
    }
    i++;
    printf("\nVous aurrez a parcourir %d metres",path[dest][i]);
    
}
