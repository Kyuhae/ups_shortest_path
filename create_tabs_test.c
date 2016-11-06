#include <stdio.h>
#include <stdbool.h>
#include "create_tabs.h"

void test() {
  int j,i, nbNoeuds;
  int **arretes;
  char tab_noeuds[100][100];    
  char tab_adj[100][100];

  arretes = Create_Tab_Noeud("map.txt", &nbNoeuds, tab_noeuds, tab_adj);
  printf("nodes = %d\n",nbNoeuds);

  printf("\n");
  printf("format: adjacent nodes to node 1: Key1 Weight1 Key2 Weight2 Key3 Weight3...\n");
  printf("adjacent nodes to node 2: Key1 Weight1 Key2 Weight2 Key3 Weight3...\n");
  printf("\n"); 
  for ( i = 0; i < nbNoeuds; i++) { 
    printf("these are the nodes adjacent to node %i :  ", i);
    for ( j = 0; arretes[i][j] != -1; j++)
      printf("%d ",arretes[i][j]);
  printf("\n");
  }
}

int main(){
    test();
    return 0;
}
