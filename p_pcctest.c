
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "test.h"
#include "p_pcc.h"


bool test1(void) {
  bool passed = true;
  int nbNoeuds = 5;
  int j;
  int ** path, **arretes;;
  
  path = malloc(sizeof(int*) * nbNoeuds);
  if (path == NULL) {
    printf("p_pcctest: malloc failure in test1");
    exit(EXIT_FAILURE);
  }
  
  for (int i = 0; i < nbNoeuds; i++) {
    path[i] = malloc(sizeof(int) * (nbNoeuds+2));
    if (path[i] == NULL) {
      printf("p_pcctest: malloc failure in test1");
      exit(EXIT_FAILURE);
    }
  }
  
  
  arretes = malloc(sizeof(int*) * nbNoeuds);
  if (arretes == NULL) {
    printf("p_pcctest: malloc failure in test1");
    exit(EXIT_FAILURE);
  }
  
  for (int i = 0; i < nbNoeuds; i++) {
    arretes[i] = malloc(sizeof(int) * (nbNoeuds * 2));
    if (arretes[i] == NULL) {
      printf("p_pcctest: malloc failure in test1");
      exit(EXIT_FAILURE);
    }
  }
  
  
  Graphe graphe = graphe_initialiser(nbNoeuds);
  arretes[0][0] = 3;
  arretes[0][1] = 70;
  arretes[0][2] = 4;
  arretes[0][3] = 40;
  arretes[0][4] = 1;
  arretes[0][5] = 100;
  arretes[0][6] = -1;
  graphe_ajouter_noeud(graphe, 0, arretes[0]);
  
  arretes[1][0] = 4;
  arretes[1][1] = 50;
  arretes[1][2] = 2;
  arretes[1][3] = 70;
  arretes[1][4] = 0;
  arretes[1][5] = 100;
  arretes[1][6] = -1;
  graphe_ajouter_noeud(graphe, 1, arretes[1]);

  arretes[2][0] = 1;
  arretes[2][1] = 70;
  arretes[2][2] = -1;
  graphe_ajouter_noeud(graphe, 2, arretes[2]);
    
  arretes[3][0] = 4;
  arretes[3][1] = 30;
  arretes[3][2] = 0;
  arretes[3][3] = 70;
  arretes[3][4] = -1;
  graphe_ajouter_noeud(graphe, 3, arretes[3]);
 
  arretes[4][0] = 3;
  arretes[4][1] = 30;
  arretes[4][2] = 1;
  arretes[4][3] = 50;
  arretes[4][4] = 0;
  arretes[4][5] = 40;
  arretes[4][6] = -1;
  graphe_ajouter_noeud(graphe, 4, arretes[4]);

 
 int tabPaths[5][5][7] = 
 { {{0, -1, 0},
    {0, 4, 1, -1, 90}, 
    {0, 4, 1, 2, -1, 160}, 
    {0, 3, -1, 70}, 
    {0, 4, -1, 40}},
    
   {{1, 4, 0, -1, 90},
    {1, -1, 0},
    {1, 2, -1, 70},
    {1, 4, 3, -1, 80},
    {1, 4, -1, 50}},

   {{2, 1, 4, 0, -1, 160},
    {2, 1, -1, 70},
    {2, -1, 0},
    {2, 1, 4, 3, -1, 150},
    {2, 1, 4, -1, 120}},

   {{3, 0, -1, 70},
    {3, 4, 1, -1, 80},
    {3, 4, 1, 2, -1, 150},
    {3, -1, 0},
    {3, 4, -1, 30}},
    
   {{4, 0, -1, 40},
    {4, 1, -1, 50},
    {4, 1, 2, -1, 120},
    {4, 3, -1, 30},
    {4, -1, 0}}
 };

  for (int src = 0; src < nbNoeuds; src ++) { 
    dijkstra(graphe, nbNoeuds, src, path);
    
    for (int i = 0; i < nbNoeuds; i++) {
      for (j = 0; tabPaths[src][i][j] != -1; j++) {
        if (path[i][j] != tabPaths[src][i][j]) {
          passed = false;
          break;
        }
      }
      if (path[i][j+1] != tabPaths[src][i][j+1]) {
        passed = false;
        break;
      }
    }
    
  }

  //frees
  graphe_liberer(&graphe);
  for (int i = 0; i < nbNoeuds; i++) {
    free(arretes[i]);
    free(path[i]);
  }
  free(arretes);
  free(path);
  
  return passed;
}

int main(void) {
  TestSuite testptr;
  testptr = tst_create();

  test(testptr, "Verifier les chemins retournés pour le graphe 5 pcc_test", test1());
  
  tst_results(testptr);
  tst_free(testptr);
  return 0;
}
