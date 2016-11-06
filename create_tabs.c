#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "create_tabs.h"
#define EXIT_MALLOC_ERROR 1
#define EXIT_OPEN_FILE 2
#define EXIT_PB_FORMAT_MAP 3

//En cas d'erreur dû à un probleme avec le fichier map,
//cette fonction vas afficher la bonne formatation du fichier map et termine l'execution
void Afficher_format_fich_map(){
    printf("\n Votre fichier de création map n'est pas bien formaté.");
    printf("\n Il doit être rédigé de la manière suivante:");
    printf("\n 1º Ligne: Nombre total de noeuds contenu dans votre map (type Integer)");
    printf("\n Lignes suivantes: \n Nombre de noeuds adjacents du premier noeud");
    printf("\n Nom du noeud (espace) Nom noeud adjacent n°1 (espace) distance entre ces deux noeuds (espace) Nom noeud adjacent n°2 (espace) distance...\n\n");
    exit(EXIT_PB_FORMAT_MAP);
}

//Si nom_noeud est présent dans le tableau tab,
//alors on renvoi l'indice, sinon on renvoi -1
int Search_tab(char tab[][100], char nom_noeud[], int nb_noeuds){
    for ( int i = 0; i < nb_noeuds; i++){
        if(strcmp(tab[i],nom_noeud) == 0)
            return i;
    }
    return -1;
}

void Delete_tab(int** tab, int nb_noeuds){
    for (int i= 0; i< nb_noeuds; i++){
            free(tab[i]);
    }
    free(tab);
}


//Cette fonction vas crée une matrice contenant la distance entre chaque noeud et sont adjacent
int** Create_Tab_Noeud(char nom_fich[], int *nb_noeuds,char tab_noeuds_in[][100],char tab_adj[][100]){
    /*Ouverture fichier passée en paramètres*/
    FILE * fich;
    fich = fopen (nom_fich, "r");
    /*Verification ouverture fichier*/
    if( fich == NULL){
        /*Erreur ouverture de fichier*/
        perror("\nERREUR: ouverture du fichier échoué");
        exit(EXIT_OPEN_FILE);
    }
    
    *nb_noeuds = 0; //nombre de noeuds totales dans le map
    fscanf(fich, "%d\n",nb_noeuds);
    
    if( *nb_noeuds == 0 )
        /*Erreur nombre de noeuds insuffisants*/
        Afficher_format_fich_map();
    
    long debut = ftell( fich );
    char nom_noeud[100];
    char nom_noeud_adj[100];
    int nb_adj;
    int dist_noeuds;
    int cpt = 0;
    char tab_noeuds[*nb_noeuds][100];
    while (cpt < *nb_noeuds){
        /*Creation d'un tableau avec toutes les noueds et leurs clés comme indice*/
        
        fscanf(fich, "%d\n",&nb_adj);
        fscanf(fich,"%s%*[^\n]",nom_noeud);
        strcpy(tab_noeuds[cpt],nom_noeud);
        strcpy(tab_noeuds_in[cpt],nom_noeud);
        cpt++;
    }
    cpt = 0;
    int cpt2,ind_key,cpt_adj = 0;
    fseek(fich,debut,0);
    int **arretes;
    arretes = malloc(sizeof(int*) * (*nb_noeuds));
    if (arretes == NULL) {
      perror("echech de malloc\n");
      exit(EXIT_MALLOC_ERROR);
    }
    while( cpt < (*nb_noeuds)){
        cpt2 = 0;
        fscanf(fich, "%d\n",&nb_adj);
        fscanf(fich,"%s",nom_noeud);
        arretes[cpt]=malloc(sizeof(int)*(nb_adj*2+1));
        if (arretes[cpt] == NULL) {
          perror("echec de malloc\n");
          exit(EXIT_MALLOC_ERROR);
        }
        strcpy(tab_adj[cpt_adj]," ");//Actualiser tableau d'adjacents
        cpt_adj++;
        strcpy(tab_adj[cpt_adj],nom_noeud);
        while( fscanf(fich,"%s",nom_noeud_adj) ){
            ind_key = Search_tab(tab_noeuds,nom_noeud_adj, *nb_noeuds);
            if( (ind_key == -1) || (nom_noeud == NULL)){
                Afficher_format_fich_map();
                
                
            }
            cpt_adj++;
            strcpy(tab_adj[cpt_adj],nom_noeud_adj);
            fscanf(fich," %d",&dist_noeuds);
            if( dist_noeuds == 0 ){
                Afficher_format_fich_map();
                
            }
            arretes[cpt][cpt2] = ind_key;
            cpt2++;
            arretes[cpt][cpt2] = dist_noeuds;//arretes : [nodeKey][ajd1key adj1weight ajd2key adj2weight....]
            cpt2++;
            if( getc(fich) == '\n' )
                break;
        }
        arretes[cpt][cpt2] = -1;
        cpt++;
        cpt_adj++;
    }
    fclose(fich);
return arretes;
}
