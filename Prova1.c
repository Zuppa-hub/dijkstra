// A quanto pare funziona

/****************************************************************
1) APPLICARE ALGORITMO DI DIJKSTRA AD UN GRAFO CON 5 NODI ORIENTATO IN UN SOLO VERSO
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
nel punto 3 se avete problemi a farlo subito per qualsiasi grafo iniziate magari con meno nodi
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#define MAX 9999
void inizializza(size_t, size_t, int[*][*], int n);
void default5(size_t, size_t, int[*][*]);
void default10(size_t, size_t, int[*][*]);
void custom(size_t, size_t, int[*][*]); // matrice di default a nodi variabili contiene 7 nodi
void inserimento(size_t, size_t, int pesi[*][*], int nodi, int flag);
void outputWindows(size_t, size_t, int pesi[*][*], int nodi);
void outputLinux(size_t, size_t, int pesi[*][*], int nodi);
// void djikstra(size_t, size_t, int pesi[*][*], int nodi);
void splash();
void pulisci();

int detect();

int main()
{
    if (detect() == -1)
    {
        wprintf(L"PIATTAFORMA NON SUPPORTATA");
        exit(-1);
    }
    setlocale(LC_ALL, "en_US.UTF-8");
    int mat5[5][5];    // matrice da riempire con i dati di default, in caso di input dell'utente sovrascrivre e inserire i dati.
    int mat10[10][10]; // stessa cosa
    int Grafo;
    int scelta;
    int nodi;
    size_t c, r;
    do
    {
        wprintf(L"\t\t\t --- DIJSKTRA ---\n\n");
        wprintf(L"\t\t\t1) Grafo a 5 nodi\n\t\t\t2) Grafo a 10 nodi\n\t\t\t3) Grafo a nodi variabili\n\t\t\t4) spiegazioni \n\t\t\t>4) Uscire dal programma\n\n\n");
        wprintf(L"Opzione: ");
        scanf("%d", &Grafo);
        pulisci();
        switch (Grafo)
        {
        default:
            wprintf(L"Uscita dal programma");
            exit(1);
            break;
        case 1:
            c = 5, r = 5;
            wprintf(L"1)Grafo di Default a 5 nodi \n2)Grafo a 5 nodi con dati inseriti dall'utente\n3)Altri cammini minimi\n\n");
            wprintf(L"Opzione: ");
            scanf("%d", &scelta);
            switch (scelta)
            {
            case 1:
                default5(c, r, mat5);
                // lancio funzione che fa dijkstra
                break;
            case 2:
                inizializza(c, r, mat5, 5);
                inserimento(c, r, mat5, 5, 0);
                // lancio funzione che fa dijkstra
                break;
            case 3:
                inizializza(c, r, mat5, 5);
                inserimento(c, r, mat5, 5, 0);
            default:
                wprintf(L"Scelta non valida, riprova\n\n");
                break;
            }
            break;
        case 2:
            c = 10, r = 10;
            wprintf(L"1)Grafo di Default a 10 nodi\n2)Grafo a 10 nodi con dati inseriti dall'utente\n3)Altri cammini minimi\n\n");
            wprintf(L"Opzione: ");
            scanf("%d", &scelta);
            switch (scelta)
            {
            case 1:
                default10(c, r, mat10);
                // lancio funzione che fa dijkstra
                break;
            case 2:
                inizializza(c, r, mat10, 10);
                inserimento(c, r, mat10, 10, 0);
                // lancio funzione che fa dijkstra
                break;
            case 3:
                // input
                // lancio funzione che fa dijksra
                // altri cammini minimi
                break;
            default:
                wprintf(L"scelta non valida, riprova");
                break;
            }
            break;
        case 3:
            c = 7, r = 7;
            wprintf(L"1)Grafo di Default\n2)Grafo con nodi e dati inseriti dall'utente\n3)Altri cammini minimi\n\n");
            wprintf(L"Opzione: ");
            scanf("%d", &scelta);
            if (scelta == 2 || scelta == 3)
            {
                do
                {
                    wprintf(L"Digita il numero di nodi");
                    scanf("%d", &nodi);
                } while (nodi > 0);
                c = nodi, r = nodi; // c e r sono le dimensioni della matrice
            }
            else if (scelta == 1)
            {
                c = 7, r = 7;
            }
            int MATcustom[c][r]; // matrice con i dati inseriti dall'utente DA SISTEMARE< MAX e' troppo grande
            switch (scelta)
            {
            case 1:
                custom(c, r, MATcustom);
                //  lancio funzione che fa dijkstra
                break;
            case 2:
                inizializza(c, r, MATcustom, MAX);
                inserimento(c, r, MATcustom, nodi, 0);

                // lancio funzione che fa dijkstra
                break;
            case 3:
                inizializza(c, r, MATcustom, MAX);
                inserimento(c, r, MATcustom, nodi, 1);
                // lancio funzione che fa dijksra
                // altri cammini minimi
                break;
            default:
                wprintf(L"scelta non valida, riprova");
                break;
            }
            break;
        case 4:
            splash();
            break;
        }
        wprintf(L"\n");
    } while (Grafo == 1 || Grafo == 2 || Grafo == 3 || Grafo == 4);
}

///
/// FUNZIONI
///
void splash()
{
    
}
void inizializza(size_t c, size_t r, int matrice[c][r], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            matrice[i][j] = MAX;
        }
    }
}

int detect() // C program to detect Operating System
{
#ifdef _WIN32
    return 0; // 0 se windows
#elif __linux__
    return 1; // 1 se linux
#else
    return -1; // sistema non supportato
#endif
}

void inserimento(size_t c, size_t r, int pesi[c][r], int nodi, int flag) // funzione per l'impot di una matrice nodi per nodi al momento statica
{
    setlocale(LC_ALL, "en_US.UTF-8");
    int i, j; // indici per i clicli principali
    int k, y; // indici per i clicli secondari
    int scelta;
    int cont = 0;
    int lettere = 65;
    if (flag == 1)
    {
        wprintf(L"inserire numero nodi: ");
        scanf("%d", &nodi);
    }
    for (i = 0; i < nodi; i++) // inizializzazione matrice pesi
    {
        for (j = 0; j < nodi; j++)
        {
            pesi[i][j] = MAX;
        }
    }
    do
    {
        wprintf(L"il grafo e' orientato?\n 1) si\n 2) no\n");
        scanf("%d", &scelta);
    } while (scelta != 1 && scelta != 2); // controllo input
    switch (scelta)
    {
    case 1:
        for (i = 0; i < nodi; i++) // input orientato
        {
            for (j = 0; j < nodi; j++)
            {
                if (i != j)
                {
                    do
                    {
                        wprintf(L"il nodo %d è collegato al nodo %d\n(0=no,1=si)\n", i, j);
                        scanf("%d", &scelta);
                    } while (scelta != 0 && scelta != 1);
                    if (scelta == 1)
                    {
                        do
                        {
                            wprintf(L"inserire peso tra %d e %d: ", i, j);
                            scanf("%d", &pesi[i][j]);

                        } while (pesi[i][j] < 0); // i pesi inseriti devono essere positivi e diversi da 0
                    }
                }
            }
            // output tabellare
            pulisci();
            wprintf(L"\\");
            // aggiungere if che se i nodi sono più di 21 stampa a numeri o bho
            for (cont = 0; cont < nodi; cont++)
            {
                wprintf(L"\t%c", lettere);
                lettere++;
            }
            lettere = 65;
            for (k = 0; k <= i; k++) // righe
            {
                wprintf(L"\n");
                wprintf(L"%c", lettere);
                lettere++;
                for (y = 0; y < nodi; y++) // colonne
                {
                    if (pesi[k][y] == MAX)
                    {
                        if (detect() == 0)
                        {
                            wprintf(L"\tINF\t\t ");
                        }
                        else if (detect() == 1)
                        {
                            wprintf(L"\t%lc\t", 8734);
                        }
                    }
                    else
                    {
                        wprintf(L"\t%d\t\t", pesi[k][y]);
                    }
                }
                wprintf(L"\n");
            }
        }
        break;
    case 2:
        for (i = 0; i < nodi; i++) // input non orientato
        {
            for (j = 0; j < nodi; j++)
            {
                if (i != j)
                {
                    if (pesi[i][j] == MAX)
                    {
                        do
                        {
                            wprintf(L"\nil nodo %c e' collegato al nodo %c\n(0=no,1=si)\n", 65 + i, 65 + j);
                            scanf("%d", &scelta);
                            if (scelta == 1)
                            {
                                do
                                {
                                    wprintf(L"inserire peso tra %c e %c: ", 65 + i, 65 + j);
                                    scanf("%d", &pesi[i][j]);

                                } while (pesi[i][j] < 0); // i pesi inseriti devono essere positivi e diversi da 0
                            }
                            else
                            {
                                pesi[i][j] = 9998;
                            }
                            pesi[j][i] = pesi[i][j];
                        } while (scelta < 0 || scelta > 1);
                    }
                }
            }
            // output tabellare ad ogni in input di righa, come lo vuole Capretti (cioè`quasi perchè non sappiamo farlo priprio come vuole Capretti).
            pulisci();
            wprintf(L"\\");
            // aggiungere if che se i nodi sono più di 21 stampa a numeri o bho
            for (cont = 0; cont < nodi; cont++)
            {
                wprintf(L"\t%c", lettere);
                lettere++;
            }
            lettere = 65;
            for (k = 0; k <= i; k++) // righe
            {
                wprintf(L"\n");
                wprintf(L"%c", lettere);
                lettere++;
                for (y = 0; y < nodi; y++) // colonne
                {
                    if (pesi[k][y] == MAX || pesi[k][y] == 9998)
                    {
                        if (detect() == 0)
                        {
                            wprintf(L"\tINF\t\t ");
                        }
                        else if (detect() == 1)
                        {
                            wprintf(L"\t%lc\t", 8734);
                        }
                    }
                    else
                    {
                        wprintf(L"\t%d\t\t", pesi[k][y]);
                    }
                }
                wprintf(L"\n");
            }
        }
        for (i = 0; i < nodi; i++)
        {
            for (j = 0; j < nodi; j++)
            {
                if (pesi[i][j] == 9998)
                {
                    pesi[i][j] = MAX;
                }
            }
        }
        break;
    }
    if (detect() == 0)
    {
        outputWindows(c, r, pesi, nodi);
    }
    else if (detect() == 1)
    {
        outputLinux(c, r, pesi, nodi);
    }
}
void outputWindows(size_t c, size_t r, int pesi[c][r], int nodi)
{
    pulisci();
    int i, j;
    int lettere = 65;
    wprintf(L"\\");
    // aggiungere if che se i nodi sono più di 21 stampa a numeri o bho
    for (i = 0; i < nodi; i++)
    {
        wprintf(L"\t%c", lettere);
        lettere++;
    }
    lettere = 65;
    for (i = 0; i < nodi; i++)
    {
        wprintf(L"\n");
        wprintf(L"%c", lettere);
        lettere++;
        for (j = 0; j < nodi; j++)
        {
            if (pesi[i][j] == MAX)
            {
                wprintf(L"\tINF ");
            }
            else
            {
                wprintf(L"\t%d ", pesi[i][j]);
            }
        }
    }
}

void outputLinux(size_t c, size_t r, int pesi[c][r], int nodi)
{
    pulisci();
    int i, j;
    int lettere = 65;
    wprintf(L"\\");
    // aggiungere if che se i nodi sono più di 21 stampa a numeri o bho
    for (i = 0; i < nodi; i++)
    {
        wprintf(L"\t%c", lettere);
        lettere++;
    }
    lettere = 65;
    for (i = 0; i < nodi; i++)
    {
        wprintf(L"\n");
        wprintf(L"%c", lettere);
        lettere++;
        for (j = 0; j < nodi; j++)
        {
            if (pesi[i][j] == MAX)
            {
                wprintf(L"\t%lc ", 8734);
            }
            else
            {
                wprintf(L"\t%d ", pesi[i][j]);
            }
        }
    }
}
void pulisci()
{
    if (detect() == 0)
    {
        system("cls");
    }
    else if (detect() == 1)
    {
        system("clear");
    }
}
void default5(size_t c, size_t r, int matrice[c][r]) // Esempio da internet (con una freccia cambiata di verso)
{
    matrice[0][0] = MAX;
    matrice[0][1] = 2;
    matrice[0][2] = MAX;
    matrice[0][3] = MAX;
    matrice[0][4] = MAX;

    matrice[1][0] = MAX;
    matrice[1][1] = MAX;
    matrice[1][2] = 1;
    matrice[1][3] = MAX;
    matrice[1][4] = MAX;

    matrice[2][0] = MAX;
    matrice[2][1] = MAX;
    matrice[2][2] = MAX;
    matrice[2][3] = MAX;
    matrice[2][4] = 5;

    matrice[3][0] = 2;
    matrice[3][1] = MAX;
    matrice[3][2] = 4;
    matrice[3][3] = MAX;
    matrice[3][4] = 1;

    matrice[4][0] = MAX;
    matrice[4][1] = 3;
    matrice[4][2] = MAX;
    matrice[4][3] = MAX;
    matrice[4][4] = MAX;
}
void default10(size_t c, size_t r, int matrice[c][r]) // Esempio dal libro pag.205 (Orientamento fatto da noi)
{
    matrice[0][0] = MAX;
    matrice[0][1] = 1;
    matrice[0][2] = 3;
    matrice[0][3] = MAX;
    matrice[0][4] = MAX;
    matrice[0][5] = MAX;
    matrice[0][6] = MAX;
    matrice[0][7] = MAX;
    matrice[0][8] = MAX;
    matrice[0][9] = MAX;

    matrice[1][0] = MAX;
    matrice[1][1] = MAX;
    matrice[1][2] = MAX;
    matrice[1][3] = MAX;
    matrice[1][4] = 2;
    matrice[1][5] = 9;
    matrice[1][6] = 4;
    matrice[1][7] = MAX;
    matrice[1][8] = MAX;
    matrice[1][9] = MAX;

    matrice[2][0] = MAX;
    matrice[2][1] = MAX;
    matrice[2][2] = MAX;
    matrice[2][3] = MAX;
    matrice[2][4] = MAX;
    matrice[2][5] = MAX;
    matrice[2][6] = MAX;
    matrice[2][7] = 6;
    matrice[2][8] = MAX;
    matrice[2][9] = MAX;

    matrice[3][0] = MAX;
    matrice[3][1] = MAX;
    matrice[3][2] = MAX;
    matrice[3][3] = MAX;
    matrice[3][4] = MAX;
    matrice[3][5] = 9;
    matrice[3][6] = MAX;
    matrice[3][7] = 3;
    matrice[3][8] = 4;
    matrice[3][9] = MAX;

    matrice[4][0] = MAX;
    matrice[4][1] = MAX;
    matrice[4][2] = 2;
    matrice[4][3] = MAX;
    matrice[4][4] = MAX;
    matrice[4][5] = MAX;
    matrice[4][6] = 5;
    matrice[4][7] = MAX;
    matrice[4][8] = MAX;
    matrice[4][9] = MAX;

    matrice[5][0] = MAX;
    matrice[5][1] = MAX;
    matrice[5][2] = MAX;
    matrice[5][3] = MAX;
    matrice[5][4] = MAX;
    matrice[5][5] = MAX;
    matrice[5][6] = MAX;
    matrice[5][7] = MAX;
    matrice[5][8] = MAX;
    matrice[5][9] = MAX;

    matrice[6][0] = MAX;
    matrice[6][1] = MAX;
    matrice[6][2] = MAX;
    matrice[6][3] = MAX;
    matrice[6][4] = MAX;
    matrice[6][5] = MAX;
    matrice[6][6] = MAX;
    matrice[6][7] = MAX;
    matrice[6][8] = MAX;
    matrice[6][9] = 4;

    matrice[7][0] = MAX;
    matrice[7][1] = MAX;
    matrice[7][2] = MAX;
    matrice[7][3] = MAX;
    matrice[7][4] = MAX;
    matrice[7][5] = MAX;
    matrice[7][6] = MAX;
    matrice[7][7] = MAX;
    matrice[7][8] = MAX;
    matrice[7][9] = MAX;

    matrice[8][0] = MAX;
    matrice[8][1] = MAX;
    matrice[8][2] = MAX;
    matrice[8][3] = MAX;
    matrice[8][4] = MAX;
    matrice[8][5] = MAX;
    matrice[8][6] = MAX;
    matrice[8][7] = MAX;
    matrice[8][8] = MAX;
    matrice[8][9] = MAX;

    matrice[9][0] = MAX;
    matrice[9][1] = MAX;
    matrice[9][2] = MAX;
    matrice[9][3] = MAX;
    matrice[9][4] = MAX;
    matrice[9][5] = MAX;
    matrice[9][6] = MAX;
    matrice[9][7] = MAX;
    matrice[9][8] = 1;
    matrice[9][9] = MAX;
}
void custom(size_t c, size_t r, int matrice[c][r])
{
    matrice[0][0] = MAX;
    matrice[0][1] = 12;
    matrice[0][2] = MAX;
    matrice[0][3] = MAX;
    matrice[0][4] = 87;
    matrice[0][5] = MAX;
    matrice[0][6] = MAX;

    matrice[1][0] = MAX;
    matrice[1][1] = MAX;
    matrice[1][2] = 11;
    matrice[1][3] = MAX;
    matrice[1][4] = MAX;
    matrice[1][5] = MAX;
    matrice[1][6] = MAX;

    matrice[2][0] = MAX;
    matrice[2][1] = MAX;
    matrice[2][2] = MAX;
    matrice[2][3] = MAX;
    matrice[2][4] = 43;
    matrice[2][5] = 35;
    matrice[2][6] = 8;

    matrice[3][0] = 19;
    matrice[3][1] = MAX;
    matrice[3][2] = MAX;
    matrice[3][3] = MAX;
    matrice[3][4] = MAX;
    matrice[3][5] = MAX;
    matrice[3][6] = MAX;

    matrice[4][0] = MAX;
    matrice[4][1] = 23;
    matrice[4][2] = MAX;
    matrice[4][3] = 10;
    matrice[4][4] = MAX;
    matrice[4][5] = 17;
    matrice[4][6] = MAX;

    matrice[5][0] = MAX;
    matrice[5][1] = MAX;
    matrice[5][2] = MAX;
    matrice[5][3] = MAX;
    matrice[5][4] = MAX;
    matrice[5][5] = MAX;
    matrice[5][6] = MAX;

    matrice[6][0] = MAX;
    matrice[6][1] = MAX;
    matrice[6][2] = MAX;
    matrice[6][3] = MAX;
    matrice[6][4] = MAX;
    matrice[6][5] = 11;
    matrice[6][6] = MAX;
}

// djikstra mob
/* void djikstra(int pesi[][100], int nodi)
{
    int prec[nodi];
    int costi[nodi];
    int visit[nodi];
    int i,j,k,z,costmin,nextnode,part,app;
    printf("\ninserire nodo di partenza: ");
    scanf("%d",&i);
    printf("\ninserire nodo di arrivo: ");
    scanf("%d",&j);
    i--;      //quarto nodo = nodo 3
    j--;      //quarto nodo = nodo 3
    part=i;
    printf("\n%d\n",part);
    for(k=0;k<nodi;k++)
    {
        visit[k]=0;
        prec[k]=i;
        costi[k]=pesi[i][k];
    }
    visit[i]=1;
    while(visit[j]!=1)
    {
        for(k=0;k<nodi;k++)
        {
            if(visit[k]!=1 && k!=i)
            {
                app=pesi[i][k]+costi[i];
                if(app<costi[k])
                {
                    costi[k]=pesi[i][k]+costi[i];
                    printf("\ncosto %d: %d",k+1,costi[k]);
                    prec[k]=i;
                }
            }
        }
        costmin=MAX;
        for(k=0;k<nodi;k++)
        {
            if(costi[k]<costmin && visit[k]!=1)
            {
                costmin=costi[k];
                printf("\ncosto minore: %d",costmin);
                nextnode=k;
                printf("\nnextnode: %d",nextnode);
            }
        }
        visit[nextnode]=1;
        i=nextnode;
    }
    printf("\ncosto minimo: %d\n",costi[j]);
    printf("percorso minimo: ");
    printf("%d",j+1);
    j=prec[j];
    do
    {
        printf("->%d",j+1);
        j=prec[j];
    }while(j!=part);
    printf("->%d",j+1);
    printf("\n");
} */