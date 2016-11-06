CC=gcc
CFLAGS= -Wall -std=c99 -g

EXEC= p_listetest p_graphetest p_pcctest create_tabs_test main
all: $(EXEC)

clean: 
	rm -rf *.o *.exe *.out $(EXEC)

p_listetest: p_liste.o test.o p_listetest.o 
	$(CC) $(LDFLAGS) -o $@ $^

p_graphetest: p_liste.o p_graphe.o test.o p_graphetest.o
	$(CC) $(LDFLAGS) -o $@ $^

p_pcctest: p_liste.o p_graphe.o p_pcc.o create_tabs.o test.o p_pcctest.o
	$(CC) $(LDFLAGS) -o $@ $^

create_tabs_test: create_tabs_test.o create_tabs.o
	$(CC) $(LDFLAGS) -o $@ $^
	
main: create_tabs.o p_liste.o p_graphe.o p_pcc.o guidage.o main.o 
	$(CC) $(LDFLAGS) -o $@ $^

