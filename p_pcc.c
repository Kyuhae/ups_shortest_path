#include "p_pcc.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>


typedef struct MinHeapNode {
    int  v;
    int dist;
}* MinHeapNode;
 

typedef struct MinHeap {
    int size;      
    int capacity;  
    int *pos;     
    struct MinHeapNode* *array;
}* MinHeap;
 
// Création d'un noeud du tas
MinHeapNode minHeap_new_node(int v, int dist) {
  MinHeapNode minHeapNode = malloc(sizeof(struct MinHeapNode));
  if (minHeapNode == NULL) {
    printf("p_pcc: malloc failure in minHeap_new_Node");
    exit(EXIT_FAILURE);
  }
  minHeapNode->v = v;
  minHeapNode->dist = dist;
  return minHeapNode;
}
 
// Constructeur du tas
MinHeap minHeap_create(int capacity) {
  MinHeap minHeap = malloc(sizeof(struct MinHeap));
  if (minHeap == NULL) {
    printf("p_pcc: malloc failure in minHeap_create");
    exit(EXIT_FAILURE);
  }
  minHeap->pos = malloc(capacity * sizeof(int));
  if (minHeap->pos == NULL) {
    printf("p_pcc: malloc failure in minHeap_create");
    exit(EXIT_FAILURE);
  }
  minHeap->size = 0;
  minHeap->capacity = capacity;
  minHeap->array = malloc(capacity * sizeof(struct MinHeapNode*));  
  if (minHeap->array == NULL) {
    printf("p_pcc: malloc failure in minHeap_create");
    exit(EXIT_FAILURE);
  }
  return minHeap;
}
 
// Echanger deux noeuds du tas
void minHeap_swap_node(MinHeapNode* a, MinHeapNode* b) {
  MinHeapNode temp = *a;
  *a = *b;
  *b = temp;
}


// Ré-ordonne le tas
void minHeap_heapify(MinHeap minHeap, int i) {
  int smallest, left, right;
  smallest = i;
  left = 2 * i + 1;
  right = 2 * i + 2;
 
  if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist )
    smallest = left;
 
  if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist )
    smallest = right;
 
  if (smallest != i) {
    MinHeapNode smallestNode = minHeap->array[smallest];
    MinHeapNode iNode = minHeap->array[i];

    minHeap->pos[smallestNode->v] = i;
    minHeap->pos[iNode->v] = smallest;
    minHeap_swap_node(&minHeap->array[smallest], &minHeap->array[i]);
 
    minHeap_heapify(minHeap, smallest);
  }
}
 
// Determiner si le tas est vide
int minHeap_empty(MinHeap minHeap) {
  return minHeap->size == 0;
}
 
// Extraire le noeud ayant la plus petite valeur de distance du tas
MinHeapNode minHeap_get_min(MinHeap minHeap){
  if (minHeap_empty(minHeap))
    return NULL;
 
  MinHeapNode root = minHeap->array[0];
 
  MinHeapNode lastNode = minHeap->array[minHeap->size - 1];
  minHeap->array[0] = lastNode;

  minHeap->pos[root->v] = minHeap->size-1;
  minHeap->pos[lastNode->v] = 0;
  
  --minHeap->size;
  minHeap_heapify(minHeap, 0);
  
  return root;
}
 
// mettre à jour le tas avec la nouvelle valeur de distance du noeud v, et ré-ordonner le tas
void minHeap_update(MinHeap minHeap, int v, int dist) {
  int i = minHeap->pos[v];
  minHeap->array[i]->dist = dist;
  
  while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
    minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
    minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
    minHeap_swap_node(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);
    i = (i - 1) / 2;
  }
}
 
// verifier l'appartenance d'un noeud au tas
bool minHeap_check(MinHeap minHeap, int v) {
   if (minHeap->pos[v] < minHeap->size) return true;
   return false;
}

// création et initialisation du tas
MinHeap minHeap_initialise(int nbNoeuds, int src, int *dist, int *parent) {
  MinHeap minHeap = minHeap_create(nbNoeuds);

  for (int i = 0; i < nbNoeuds; i++) {
    dist[i] = INT_MAX;
    minHeap->array[i] = minHeap_new_node(i, dist[i]);
    minHeap->pos[i] = i;
  }

  minHeap->array[src]->v = src;
  minHeap->array[src]->dist = dist[src];
  minHeap->pos[src]   = src;
  dist[src] = 0;
  parent[src] = -1;
  
  minHeap_update(minHeap, src, dist[src]);
  minHeap->size = nbNoeuds;
  
  return minHeap;
}
 
// Construire le tableau pour un chemin donné
void build_path_array(int parent[], int node, int *path, int *plength) {
  if (parent[node]==-1) {
    path[*plength] = node;
    (*plength) ++;
    return;
  }
  
  build_path_array(parent, parent[node], path, plength);
  
  path[*plength] = node;
  (*plength)++;
}

// construire le tableau de tous les chemins depuis le noeud source
void build_info_arrays(int dist[], int parent[], int **path, int nbNoeuds) {
  int plength;
  for (int i = 0; i < nbNoeuds; i++) {
    plength = 0;
    build_path_array(parent, i, path[i], &plength);
    path[i][plength] = -1;
    path[i][plength+1] = dist[i];
  }
}
 

void dijkstra(Graphe graphe, int nbNoeuds, int src, int **path) {
  int *dist, *parent;
  int cle_extrait, cle_adj, poids;
  
  dist = malloc(nbNoeuds * sizeof(int));
  parent = malloc(nbNoeuds * sizeof(int));
  if (dist == NULL || parent == NULL) {
    printf("p_pcc: malloc failure in dijkstra");
    exit(EXIT_FAILURE);
  }
  MinHeap minHeap = minHeap_initialise(nbNoeuds, src, dist, parent);
  MinHeapNode minHeapNode;
  
  while (!minHeap_empty(minHeap)) {

    minHeapNode = minHeap_get_min(minHeap);
    cle_extrait = minHeapNode->v;
    lIterator iterateur = graphe_initialiser_iterateur_adj(graphe, cle_extrait, &cle_adj, &poids);
    
    do {
      if (minHeap_check(minHeap, cle_adj) && dist[cle_extrait] != INT_MAX && poids + dist[cle_extrait] < dist[cle_adj]) {
        parent[cle_adj] = cle_extrait;
        dist[cle_adj] = dist[cle_extrait] + poids;
        minHeap_update(minHeap, cle_adj, dist[cle_adj]);
      }
    } while (graphe_iterateur_adj_next(iterateur, cle_extrait, &cle_adj, &poids));
    
    graphe_iterateur_detruire(&iterateur);
    free(minHeapNode);
  }
 
  build_info_arrays(dist, parent, path, nbNoeuds);
  
  free(dist);
  free(parent);
  
  free(minHeap->array);
  free(minHeap->pos);
  free(minHeap);
}
