#define TAB_SIZE 6

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "test.h"
#include "p_liste.h"

bool test1(void) {
  bool passed;
  Liste list = NULL;
  liste_initialiser(&list);
  passed = liste_vide(list);
  liste_liberer(&list);
  return passed;
}

bool test2(void) {
  bool passed = true;
  int t[TAB_SIZE] = {7,8,4,5,1,2,};
  int pop[TAB_SIZE];
  Liste list = NULL;
  liste_initialiser(&list);
  for (int i = 0; i < TAB_SIZE; i+=2)   
    liste_push_front(list, t[i], t[i+1]);
  for (int i = 0; i < TAB_SIZE; i+=2)
    liste_pop_front(list, &pop[i+1], &pop[i]);
  for (int i = 0; i < TAB_SIZE; i++)
    passed = pop[i] == t[TAB_SIZE-1-i];
  liste_liberer(&list);
  return passed;
}

bool test3(void) {
  bool passed = true;
  int t[TAB_SIZE] = {7,8,4,5,1,2};
  int pop[TAB_SIZE];
  Liste list = NULL;
  liste_initialiser(&list);
  for (int i = 0; i < TAB_SIZE; i+=2)   
    liste_push_back(list, t[i], t[i+1]);
  for (int i = 0; i < TAB_SIZE; i+=2)
    liste_pop_front(list, &pop[i], &pop[i+1]);
  for (int i = 0; i < TAB_SIZE; i++) 
    passed = pop[i] == t[i];
  liste_liberer(&list);
  return passed;
}

int main(void) {
  TestSuite testptr;
  testptr = tst_create();

  test(testptr, "Creer une liste vide, puis tester si elle est vide", test1());
  test(testptr, "Ajouter des elements à une liste, verifier leur presence et l'ordre (ajout en debut)", test2());
  test(testptr, "Ajouter des elements à une liste, verifier leur presence et l'ordre (ajout en fin) ", test3());
  
  tst_results(testptr);
  tst_free(testptr);
  return 0;
}
