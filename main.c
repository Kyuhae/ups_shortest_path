#include "create_tabs.h"
#include "p_graphe.h"
#include "p_liste.h"
#include "p_pcc.h"
#include "guidage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SUCCESS 0
#define EXIT_NB_PARAM 1


int main(int argc,char* argv[]){
    if( argc != 2){
        printf("\nERREUR: nombre de paramètres en entrée");
        printf("\n./executable fichier_map.txt\n");
        exit(EXIT_NB_PARAM);
    }
    int** arretes;
    char tab_adj[100][100];
    int nb_noeuds;
    int src,dest;
    char tab_noeuds[100][100];
    int i,j;
    src = -1;
    dest = -1;
    /*Création à partir du ficher passé en paramètre des tableaux d'arretes, de noeuds et de noeuds adjacents*/
    arretes = Create_Tab_Noeud(argv[1], &nb_noeuds, tab_noeuds,tab_adj);
    
    /*Saisir points de départ et destination*/
    /*vérification aussi si ils sont cohérents*/
    while( ((src < 0) || (src >= nb_noeuds)) || ((dest <  0) || (dest >= nb_noeuds)) || (src == dest)){
        guidage_afficher_noeuds (tab_noeuds,nb_noeuds);
        src = guidage_saisir_noeud_source();
        dest = guidage_saisir_noeud_dest();
    }
    Graphe graphe = graphe_initialiser(nb_noeuds);//initialisation du graphe
    for( i = 0; i < nb_noeuds; i++){
        graphe_ajouter_noeud(graphe,i,arretes[i]);
    }
    int pos_actuel,cpt_sortie = 0;
    int ** path;
    path = malloc(sizeof(int*) * nb_noeuds);
    if (path == NULL) {
        printf("main: malloc failure");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < nb_noeuds; i++) {
        path[i] = malloc(sizeof(int) * (nb_noeuds + 1));
        if (path[i] == NULL) {
            printf("main: malloc failure");
            exit(EXIT_FAILURE);
        }
    }
    dijkstra(graphe,nb_noeuds,src,path);//Calcul du plus court chemin
    guidage_distance(dest,path);
    
    i = 0;
    /*Tant qu'on n'as pas arriver a notre destination, on boucle*/
    while( path[dest][i] != -1 ){
        printf("\nSaisir votre position actuelle:");
        guidage_afficher_noeuds (tab_noeuds,nb_noeuds);
        scanf("\n%d",&pos_actuel);
        if( pos_actuel == dest )
            break;
        if( path[dest][i] != pos_actuel ){
            /*On s'est trompé de chemin*/
            i = 0;
            src = pos_actuel;
            dijkstra(graphe,nb_noeuds,src,path);//Recalculer le plus court chemin à partir de notre nouvelle position
            cpt_sortie=0;
            for( j=0; j<nb_noeuds*nb_noeuds; j++){
                if( strcmp(tab_adj[j]," ") == 0)
                    if( strcmp(tab_adj[j+1],tab_noeuds[pos_actuel]) == 0 )
                        break;
            }
            j++;
            while ( strcmp(tab_noeuds[path[dest][i+1]],tab_adj[j]) != 0 ){
                cpt_sortie++;
                j++;
            }
            guidage_noeud(tab_noeuds[path[dest][i+1]],cpt_sortie);
        }else{
            /*On est dans le bon chemin*/
            /*On doit donc simplement afficher la prochaine sortie a prendre*/
            for( j=0; j<nb_noeuds*nb_noeuds; j++){
                if( strcmp(tab_adj[j]," ") == 0)
                    if( strcmp(tab_adj[j+1],tab_noeuds[pos_actuel]) == 0 )
                        break;
            }
            cpt_sortie = 0;
            j++;
             while ( strcmp(tab_noeuds[path[dest][i+1]],tab_adj[j]) != 0 ){
                cpt_sortie++;
                j++;
            }
            guidage_noeud(tab_noeuds[path[dest][i+1]],cpt_sortie);
            i++;
        }
        cpt_sortie = 0;
    }
    /*On est arrivé a notre destination*/
    printf("\n Vous etes arrivé à votre destination\n");
    /*Libération de mémoire*/
    graphe_liberer(&graphe);
    for (int i = 0; i < nb_noeuds; i++) {
            free(path[i]);
    }
    free(path);
    Delete_tab(arretes, nb_noeuds);
    
    exit(SUCCESS);
    return 0;
}
