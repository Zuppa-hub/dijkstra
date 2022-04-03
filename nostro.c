/*1) APPLICARE ALGORITMO DI DIJKSTRA AD UN GRAFO CON 5 NODI ORIENTATO IN UN SOLO VERSO
a. Soluzione default
b. Soluzione dijkstra con dati inseriti utente
c. Vedere se ci sono altri cammini minimi se si stamparli
2) APPLICARE ALGORITMO DI DIJKSTRA AD UN GRAFO CON 10 NODI ORIENTATO IN UN SOLO VERSO
a. Soluzione default
b. Soluzione dijkstra con dati inseriti utente
c. Vedere se ci sono altri cammini minimi se si stamparli
3) APPLICARE ALGORITMO DI DIJKSTRA AD UN GRAFO QUALSIASI
a. Soluzione default
b. Soluzione dijkstra con dati inseriti utente
c. Vedere se ci sono altri cammini minimi se si stamparli
n.b. fare gli opportuni controlli sui dati inseriti dagli utenti
nel punto 3 se avete problemi a farlo subito per qualsiasi grafo iniziate magari con meno nodi*/

#define MAX 2147483647
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void inserimento(int pesi[][100], int nodi);

int main()
{
    int nodi, i, j, scelta;
    int pesi[100][100];
    do
    {
        printf("1 per la soluzione a 5 nodi di default\n2 per la soluzione a 10 nodi di default\n3 per la soluzione ad un grafo qualsiasi\n0 per uscire\n");
        scanf("%d", &scelta);
        switch (scelta)
        {
        case 1:
        
            break;
        case 2:

            break;
        case 3:

            break;
        }
    } while (scelta != 0);
}

void fisso1(int pesi[][100])
{
    int v[25]={0, 0, 0};
    int cont=0,j,i;
    for (j = 0; j < 5; j++)
    {
        for (i = 0; i < 5; i++)
        {
            if (v[cont] != 0)
            {
                pesi[i][j] = v[cont];
            }
            else
            {
                pesi[i][j] = MAX;
            }
            cont++;
        }
    }
}

void fisso2(int pesi[][100])
{
    int v[100]={0, 0, 0};
    int cont=0,j,i;
    for (j = 0; j < 10; j++)
    {
        for (i = 0; i < 10; i++)
        {
            if (v[cont] != 0)
            {
                pesi[i][j] = v[cont];
            }
            else
            {
                pesi[i][j] = MAX;
            }
            cont++;
        }
    }
}

void inserimento(int pesi[][100], int nodi) // funzione per l'impot di una matrice nodi per nodi al momento statica
{
    int scelta;
    printf("inserire numero nodi: ");
    scanf("%d", &nodi);

    int i, j;
    for (i = 0; i < nodi; i++)      //inizioalizzazione matrice pesi 
    {
        for (j = 0; j < nodi; j++)
        {
            pesi[i][j] = MAX;
        }
    }
    do
    {
        printf("il grafo è orientato?\n 1) si\n 2) no\n");
        scanf("%d",&scelta);
    }while(scelta!=1 || scelta!=2);
    switch (scelta)
    {
    case 1:
        for (i = 0; i < nodi; i++)      //input orientato 
        {
            for (j = 0; j < nodi; j++)
            {
                if (i != j)
                {
                    do
                    {
                        printf("il nodo %d è collegato al nodo %d\n(0=no,1=si)\n", i, j);
                        scanf("%d", &scelta);
                        if (scelta == 1)
                        {
                            do
                            {
                                printf("inserire peso tra %d e %d: ", i, j);
                                scanf("%d", &pesi[i][j]);
                            } while (pesi[i][j] < 0); // i pesi inseriti devono essere positivi e diversi da 0
                        }
                    } while (scelta != 0 || scelta != 1);
                }
            }
        }
        break;
    case 2:
        for (i = 0; i < nodi; i++)      //input non orientato
        {
            for (j = 0; j < nodi; j++)
            {
                if (i != j&& pesi[i][j]!=MAX)
                {
                    {
                        do
                        {
                            printf("il nodo %d è collegato al nodo %d\n(0=no,1=si)\n", i, j);
                            scanf("%d",&scelta);
                            if (scelta == 1)
                            {
                                do
                                {
                                    printf("inserire peso tra %d e %d: ", i, j);
                                    scanf("%d", &pesi[i][j]);
                                    pesi[j][i]=pesi[i][j];
                                } while (pesi[i][j] < 0); // i pesi inseriti devono essere positivi e diversi da 0
                            }
                        } while (scelta != 0 || scelta != 1);
                    }
                }
            }
        }
        break;
    }
}

void djikstra(int pesi[][100], int nodi)
{
    //write a function that implements djikstra algorithm

    //input:
    //matrix of weights
    //starting node
    //finish node
    //output:
    //array of distances from starting node to finish node

    //algorithm:
    //initialize array of distances from starting node to finish node
    //initialize array of visited nodes
    //initialize array of previous nodes
    
    //while there are unvisited nodes
    //find the node with the minimum distance
    //mark it as visited
    //for each unvisited node
    //if the distance from the current node to the new node is less than the current distance
    //update the distance
    //update the previous node
    //end for
    //end while
    //return the array of distances
    int prec[nodi];
    int costi[nodi];
    int i,j,k,app=MAX,apprec,arr;
    printf("inserire nodo di partenza: ");
    scanf("%d", &k);
    printf("inserire nodo di arrivo: ");
    scanf("%d", &arr);
    k=k-1;      //quarto nodo = nodo 3
    do
    {
        apprec=k;                   //volendo cambia k con j
        for (i = 0; i < nodi; i++)
        {
            prec[i] = -1;
            costi[i] = pesi[i][k];
        }
        for (i = 0; i <nodi; i++)
        {
            if (costi[i] < app)
            {
                app = costi[i];
                k = i;       
            }
        }
        prec[k] = apprec;
    } while (k != arr);
}
