#define TAB_SIZE 6

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "test.h"
#include "p_graphe.h"


bool test1(void) {
  bool passed;
  int nbNoeuds = 4;
  Graphe graphe = graphe_initialiser(nbNoeuds);
  passed = graphe_vide(graphe);
  graphe_liberer(&graphe);
  return passed;
}

bool test2(void) {
  bool passed = true;
  int nbNoeuds = 9;
  int cle, poids;
  
  int **arretes;
  arretes = malloc(sizeof(int*) * nbNoeuds);
  if (arretes == NULL) {
    printf("graphetest: malloc failure in test2");
    exit(EXIT_FAILURE);
  }
  
  Graphe graphe = graphe_initialiser(nbNoeuds);
  
  arretes[0] = malloc(sizeof(int) * (nbNoeuds * 2));
  if (arretes[0] == NULL) {
    printf("graphetest: malloc failure in test2");
    exit(EXIT_FAILURE);
  }
  arretes[0][0] = 1;
  arretes[0][1] = 40;
  arretes[0][2] = 2;
  arretes[0][3] = 30;
  arretes[0][4] = -1;
  graphe_ajouter_noeud(graphe, 0, arretes[0]);
  
  
  arretes[1] = malloc(sizeof(int) * ((nbNoeuds) * 2));
  if (arretes[1] == NULL) {
    printf("graphetest: malloc failure in test2");
    exit(EXIT_FAILURE);
  }
  arretes[1][0] = 0;
  arretes[1][1] = 40;
  arretes[1][2] = 2;
  arretes[1][3] = 30;
  arretes[1][4] = 3;
  arretes[1][5] = 10;
  arretes[1][6] = 8;
  arretes[1][7] = 50;
  arretes[1][8] = -1;
  graphe_ajouter_noeud(graphe, 1, arretes[1]);
  
  
  arretes[2] = malloc(sizeof(int) * (nbNoeuds * 2));
  if (arretes[2] == NULL) {
    printf("graphetest: malloc failure in test2");
    exit(EXIT_FAILURE);
  }
  arretes[2][0] = 0;
  arretes[2][1] = 30;
  arretes[2][2] = 1;
  arretes[2][3] = 30;
  arretes[2][4] = 4;
  arretes[2][5] = 10;
  arretes[2][6] = -1;
  graphe_ajouter_noeud(graphe, 2, arretes[2]);
  
  
  arretes[3] = malloc(sizeof(int) * (nbNoeuds * 2));
  if (arretes[3] == NULL) {
    printf("graphetest: malloc failure in test2");
    exit(EXIT_FAILURE);
  }
  arretes[3][0] = 1;
  arretes[3][1] = 10;
  arretes[3][2] = 7;
  arretes[3][3] = 20;
  arretes[3][4] = -1;
  graphe_ajouter_noeud(graphe, 3, arretes[3]);
    
  
  arretes[4] = malloc(sizeof(int) * (nbNoeuds * 2));
  if (arretes[4] == NULL) {
    printf("graphetest: malloc failure in test2");
    exit(EXIT_FAILURE);
  }
  arretes[4][0] = 2;
  arretes[4][1] = 10;
  arretes[4][2] = 6;
  arretes[4][3] = 100;
  arretes[4][4] = 5;
  arretes[4][5] = 10;
  arretes[4][6] = -1;
  graphe_ajouter_noeud(graphe, 4, arretes[4]);
  
  
  arretes[5] = malloc(sizeof(int) * (nbNoeuds * 2));
  if (arretes[5] == NULL) {
    printf("graphetest: malloc failure in test2");
    exit(EXIT_FAILURE);
  }
  arretes[5][0] = 4;
  arretes[5][1] = 10;
  arretes[5][2] = -1;
  graphe_ajouter_noeud(graphe, 5, arretes[5]);
  
  
  arretes[6] = malloc(sizeof(int) * (nbNoeuds * 2));
  if (arretes[6] == NULL) {
    printf("graphetest: malloc failure in test2");
    exit(EXIT_FAILURE);
  }
  arretes[6][0] = 4;
  arretes[6][1] = 100;
  arretes[6][2] = 8;
  arretes[6][3] = 90;
  arretes[6][4] = -1;
  graphe_ajouter_noeud(graphe, 6, arretes[6]);
  
  
  arretes[7] = malloc(sizeof(int) * (nbNoeuds * 2));
  if (arretes[7] == NULL) {
    printf("graphetest: malloc failure in test2");
    exit(EXIT_FAILURE);
  }
  arretes[7][0] = 8;
  arretes[7][1] = 30;
  arretes[7][2] = 3;
  arretes[7][3] = 20;
  arretes[7][4] = -1;
  graphe_ajouter_noeud(graphe, 7, arretes[7]);
  
  
  arretes[8] = malloc(sizeof(int) * (nbNoeuds * 2));
  if (arretes[8] == NULL) {
    printf("graphetest: malloc failure in test2");
    exit(EXIT_FAILURE);
  }
  arretes[8][0] = 1;
  arretes[8][1] = 50;
  arretes[8][2] = 7;
  arretes[8][3] = 30;
  arretes[8][4] = 6;
  arretes[8][5] = 90;
  arretes[8][6] = -1;
  graphe_ajouter_noeud(graphe, 8, arretes[8]);
  
  

  int tabAdj[nbNoeuds]; 
  for (int i = 0; i < nbNoeuds; i++) {
    int cpt = 0;
    lIterator iterateur = graphe_initialiser_iterateur_adj(graphe, i, &cle, &poids);
    tabAdj[0] = cle; tabAdj[1] = poids;
    
    for (int j = 0; arretes[i][j] != -1; j+=2) {
      graphe_iterateur_adj_next(iterateur, i, &cle, &poids);
      tabAdj[j+2] = cle; tabAdj[j+3] = poids;
      cpt+=2;
    }
    for (int j = cpt-1; j >=0; j-=2) {
      if (arretes[i][cpt-j-1] != tabAdj[j-1] || arretes[i][cpt-j] != tabAdj[j])
        return false;
    }  
    graphe_iterateur_detruire(&iterateur);
    free(arretes[i]);
  } 
  free(arretes);
  graphe_liberer(&graphe);
  
  return passed;
}


int main(void) {
  TestSuite testptr;
  testptr = tst_create();

  test(testptr, "Creer un graphe vide puis tester si il est vide", test1());
  test(testptr, "Remplir un Graphe, et verifier que l'iterateur retourne des valeurs correctes", test2());
  
  tst_results(testptr);
  tst_free(testptr);
  return 0;
}