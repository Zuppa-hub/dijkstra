//NON PROVATO, NON FUNZIONERÀ MAI. 


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
void inizializza(int matrice[][MAX], int n);
void default5(int matrice[][5]);
void default10(int matrice[][10]);
void custom(int matrice[][7]); // matrice di default a nodi variabili contiene 7 nodi
int detect();

int main()
{
    int mat5[5][5];          // matrice da riempire con i dati di default, in caso di input dell'utente sovrascrivre e inserire i dati.
    int mat10[10][10];       // stessa cosa
    int MATcustom[MAX][MAX]; // matrice con i dati inseriti dall'utente
    int Grafo;
    int scelta;
    int nodi;
    do
    {
        wprintf(L"\t\t\t --- DIJSKTRA ---\n\n");
        wprintf(L"\t\t\t1) Grafo a 5 nodi\n\t\t\t2) Grafo a 10 nodi\n\t\t\t3) Grafo a nodi variabili\n\n");
        wprintf(L"Opzione: ");
        scanf("%d", &Grafo);
        switch (Grafo)
        {
        case 1:
            wprintf(L"1)Grafo di Default\n2)Grafo con dati inseriti dall'utente\n3)Altri cammini minimi\n\n");
            wprintf(L"Opzione: ");
            scanf("%d", &scelta);
            switch (scelta)
            {
            case 1:
                default5(mat5);
                // lancio funzione che fa dijkstra
                break;
            case 2:
                inizializza(mat5, 5);
                if (detect() == 0)
                {
                    inserimentoWindows(mat5, 5);
                }
                else if (detect() == 1)
                {
                    inserimentoLinux(mat5, 5);
                }
                else
                {
                    wprintf(L"Sistema non supportato\n");
                }
                // lancio funzione che fa dijkstra
                break;
            case 3:
                inizializza(mat5, 5);
                if (detect() == 0)
                {
                    inserimentoWindows(mat5, 5);
                }
                else if (detect() == 1)
                {
                    inserimentoLinux(mat5, 5);
                }
                else
                {
                    wprintf(L"Sistema non supportato\n");
                }
                // lancio funzione che fa dijksra
                // altri cammini minimi
                break;
            default:
                wprintf(L"Scelta non valida, riprova\n\n");
                break;
            }
        case 2:
            wprintf(L"1)Grafo di Default\n2)Grafo con dati inseriti dall'utente\n3)Altri cammini minimi\n\n");
            wprintf(L"Opzione: ");
            scanf("%d", &scelta);
            switch (scelta)
            {
            case 1:
                default10(mat10);
                // lancio funzione che fa dijkstra
                break;
            case 2:
                inizializza(mat10, 10);
                if (detect() == 0)
                {
                    inserimentoWindows(mat10, 10);
                }
                else if (detect() == 1)
                {
                    inserimentoLinux(mat10, 10);
                }
                else
                {
                    wprintf(L"Sistema non supportato\n");
                }
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
        case 3:
            wprintf(L"1)Grafo di Default\n2)Grafo con dati inseriti dall'utente\n3)Altri cammini minimi\n\n");
            wprintf(L"Opzione: ");
            scanf("%d", &scelta);
            switch (scelta)
            {
            case 1:
                custom(MATcustom);
                //  lancio funzione che fa dijkstra
                break;
            case 2:
                inizializza(MATcustom, MAX);
                do
                {
                    wprintf(L"Digita il numero di nodi");
                    scanf("%d", &nodi);
                } while (nodi > 0);
                if (detect() == 0)
                {
                    inserimentoWindows(MATcustom, nodi);
                }
                else if (detect() == 1)
                {
                    inserimentoLinux(MATcustom, nodi);
                }
                else
                {
                    wprintf(L"Sistema non supportato\n");
                }
                // lancio funzione che fa dijkstra
                break;
            case 3:
                inizializza(MATcustom, MAX);
                do
                {
                    wprintf(L"Digita il numero di nodi");
                    scanf("%d", &nodi);
                } while (nodi > 0);
                if (detect() == 0)
                {
                    inserimentoWindows(MATcustom, nodi);
                }
                else if (detect() == 1)
                {
                    inserimentoLinux(MATcustom, nodi);
                }
                else
                {
                    wprintf(L"Sistema non supportato\n");
                }
                // lancio funzione che fa dijksra
                // altri cammini minimi
                break;
            default:
                wprintf(L"scelta non valida, riprova");
                break;
            }
        }
    } while (Grafo != 1 && Grafo != 2 && Grafo != 3);
}

///
/// FUNZIONI
///

void inizializza(int matrice[][MAX], int n)
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

void inserimentoWindows(int pesi[][MAX], int nodi) // funzione per l'impot di una matrice nodi per nodi al momento statica
{
    setlocale(LC_ALL, "en_US.UTF-8");
    int i, j;
    int scelta;
    wprintf(L"inserire numero nodi: ");
    scanf("%d", &nodi);

    for (i = 0; i < nodi; i++) // inizioalizzazione matrice pesi
    {
        for (j = 0; j < nodi; j++)
        {
            pesi[i][j] = MAX;
        }
    }
    do
    {
        wprintf(L"il grafo è orientato?\n 1) si\n 2) no\n");
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
                            wprintf(L"il nodo %c e' collegato al nodo %c\n(0=no,1=si)\n", 65 + i, 65 + j);
                            scanf("%d", &scelta);
                            pesi[j][i] = 9998;
                            if (scelta == 1)
                            {
                                do
                                {
                                    wprintf(L"inserire peso tra %c e %c: ", 65 + i, 65 + j);
                                    scanf("%d", &pesi[i][j]);

                                } while (pesi[i][j] < 0); // i pesi inseriti devono essere positivi e diversi da 0
                            }
                        } while (scelta < 0 || scelta > 1);
                    }
                    else if (pesi[i][j] == 9998)
                    {
                        pesi[i][j] = pesi[j][i];
                    }
                }
            }
        }
        break;
    }
    for (i = 0; i < nodi; i++)
    {
        wprintf(L"\n");
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
void inserimentoLinux(int pesi[][MAX], int nodi) // funzione per l'impot di una matrice nodi per nodi al momento statica
{
    setlocale(LC_ALL, "en_US.UTF-8");
    int i, j;
    int scelta;
    wprintf(L"inserire numero nodi: ");
    scanf("%d", &nodi);

    for (i = 0; i < nodi; i++) // inizioalizzazione matrice pesi
    {
        for (j = 0; j < nodi; j++)
        {
            pesi[i][j] = MAX;
        }
    }
    do
    {
        wprintf(L"il grafo è orientato?\n 1) si\n 2) no\n");
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
                            wprintf(L"il nodo %c e' collegato al nodo %c\n(0=no,1=si)\n", 65 + i, 65 + j);
                            scanf("%d", &scelta);
                            pesi[j][i] = 9998;
                            if (scelta == 1)
                            {
                                do
                                {
                                    wprintf(L"inserire peso tra %c e %c: ", 65 + i, 65 + j);
                                    scanf("%d", &pesi[i][j]);

                                } while (pesi[i][j] < 0); // i pesi inseriti devono essere positivi e diversi da 0
                            }
                        } while (scelta < 0 || scelta > 1);
                    }
                    else if (pesi[i][j] == 9998)
                    {
                        pesi[i][j] = pesi[j][i];
                    }
                }
            }
        }
        break;
    }
    for (i = 0; i < nodi; i++)
    {
        wprintf(L"\n");
        for (j = 0; j < nodi; j++)
        {
            if (pesi[i][j] == MAX)
            {
                wprintf(L"%lc ", 8734);
            }
            else
            {
                wprintf(L"%d ", pesi[i][j]);
            }
        }
    }
}

void default5(int matrice[][5]) // Esempio da internet (con una freccia cambiata di verso)
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

void default10(int matrice[][10]) // Esempio dal libro pag.205 (Orientamento fatto da noi)
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
void custom(int matrice[][7])
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