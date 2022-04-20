// ANDREA CAZZATO
// FRANCESCO ROSSI

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
#include <limits.h>

#define MAX ((int)(~0u >> 1u))
void inizializza(size_t, size_t, int[*][*], int nodi); // Funzione di inizializzazione a MAX
void default5(size_t, size_t, int[*][*]);              // Matrice di default a 5 nodi
void default10(size_t, size_t, int[*][*]);             // Matrice di default a 10 nodi
void custom(size_t, size_t, int[*][*]);                // matrice di default a nodi variabili contiene 7 nodi
void pulisci();
int detect();
void splash(); // restituisce il numero di colonne
int scelta();  // scelta del grafo tra custom e default
void inserimento(size_t, size_t, int pesi[*][*], int nodi, int flag);
void outputWindows(size_t, size_t, int pesi[*][*], int nodi);
void outputLinux(size_t, size_t, int pesi[*][*], int nodi);
void output(size_t, int mat[*][*], int nodi);
int main()
{

    setlocale(LC_ALL, "en_US.UTF-8");
    int mat5[5][5];    // matrice da riempire con i dati di default, in caso di input dell'utente sovrascrivre e inserire i dati.
    int mat10[10][10]; // stessa cosa
    int Grafo;
    int nodi;
    int sceltaNODi, sceltaDEF;
    size_t DIM; // dimensione matrice
    do
    {
        wprintf(L" --- DIJSKTRA ---\n\n");
        wprintf(L"1) Grafo a 5 nodi\n2) Grafo a 10 nodi\n3) Grafo a nodi variabili\n?) Premi qualsiasi altro numero per uscire\n\n\n");
        wprintf(L"Opzione: ");
        scanf("%d", &sceltaNODi);
        pulisci();
        switch (sceltaNODi)
        {
        case 1:
            DIM = 5;
            nodi = 5;
            inizializza(DIM, DIM, mat5, nodi);
            sceltaDEF = scelta();
            switch (sceltaDEF)
            {
            case 1:
                default5(DIM, DIM, mat5);
                output(DIM, mat5, nodi);
                // dikstra
                break;
            case 2:
                inserimento(DIM, DIM, mat5, nodi, 0);
                output(DIM, mat5, nodi);
                // disra
                break;
            }
            break;
        case 2:
            DIM = 10;
            nodi = 10;
            inizializza(DIM, DIM, mat10, nodi);
            sceltaDEF = scelta();
            switch (sceltaDEF)
            {
            case 1:
                default10(DIM, DIM, mat10);
                output(DIM, mat10, nodi);
                // dikstra
                break;
            case 2:
                inserimento(DIM, DIM, mat10, nodi, 0);
                output(DIM, mat10, nodi);
                // disra
                break;
            }
            break;
        case 3:
            sceltaDEF = scelta();
            if (sceltaDEF == 1)
            {
                DIM = 7;
                nodi = 7;
            }
            else if (sceltaDEF == 2)
            {
                do
                {
                    wprintf(L"Inserire il numero di nodi: ");
                    scanf("%d", &nodi);
                    if (nodi < 3)
                    {
                        wprintf(L"\nIl numero di nodi deve essere maggiore di 2\n");
                    }
                } while (nodi < 3);
                DIM = nodi;
            }
            int MATcustom[DIM][DIM];
            inizializza(DIM, DIM, MATcustom, nodi);
            switch (sceltaDEF)
            {
            case 1:
                custom(DIM, DIM, MATcustom);
                output(DIM, MATcustom, nodi);
                // distra
                break;
            case 2:
                inserimento(DIM, DIM, MATcustom, nodi, 1);
                output(DIM, MATcustom, nodi);
                //  distra
                break;
            }
            break;
        }
    } while (sceltaNODi > 0 && sceltaNODi < 4);
    wprintf(L"\n");
    system("PAUSE");
    pulisci();
}
void output(size_t DIM, int mat[DIM][DIM], int nodi)
{
    if (detect() == 0)
    {
        outputWindows(DIM, DIM, mat, nodi);
    }
    else if (detect() == 1)
    {
        outputLinux(DIM, DIM, mat, nodi);
    }
}
void outputWindows(size_t c, size_t r, int pesi[c][r], int nodi)
{
    pulisci();
    int i, j;
    if (nodi < 26)
    {
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
    else // stampo a numeri
    {
        int cont = 0;
        wprintf(L"\\");
        for (cont = 0; cont < nodi; cont++)
        {
            wprintf(L"\t%d", cont);
        }
        for (i = 0; i < nodi; i++)
        {
            wprintf(L"\n");
            wprintf(L"%d", i);
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
}
void outputLinux(size_t c, size_t r, int pesi[c][r], int nodi)
{
    pulisci();
    int i, j;
    if (nodi < 26)
    {
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
    else
    {
        wprintf(L"\\");
        int cont = 0;
        for (i = 0; i < nodi; i++)
        {
            wprintf(L"\t%d", cont);
            cont++;
        }
        cont = 0;
        for (i = 0; i < nodi; i++)
        {
            wprintf(L"\n");
            wprintf(L"%d", cont);
            cont++;
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
}
void inserimento(size_t c, size_t r, int pesi[c][r], int nodi, int flag) // funzione per l'impot di una matrice nodi per nodi al momento statica
{

    setlocale(LC_ALL, "en_US.UTF-8");

    int i, j; // indici per i clicli principali
    int k, y; // indici per i clicli secondari
    int scelta, scelta1;
    int cont = 0;
    int lettere = 65;
    fflush(stdout);
    fflush(stdin);
    if (flag == 1)
    {
        do
        {
            wprintf(L"il grafo e' orientato?\n 1) SI\n 2) NO\n");
            scanf("%d", &scelta);
        } while (scelta != 1 && scelta != 2); // controllo input
    }
    else if (flag == 0)
    {
        scelta = 1;
    }
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
                        wprintf(L"il nodo %c e' collegato al nodo %c\n1) SI\n 2) NO)\n", 65 + i, 65 + j);
                        scanf("%d", &scelta1);
                    } while (scelta1 != 1 && scelta1 != 2);
                    if (scelta1 == 1)
                    {
                        do
                        {
                            wprintf(L"inserire peso tra %c e %c: ", 65 + i, 65 + j);
                            scanf("%d", &pesi[i][j]);
                        } while (pesi[i][j] < 1); // i pesi inseriti devono essere positivi e diversi da 0
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
                            wprintf(L"\tINF\t");
                        }
                        else if (detect() == 1)
                        {
                            wprintf(L"\t%lc\t", 8734);
                        }
                    }
                    else
                    {
                        wprintf(L"\t%d\t", pesi[k][y]);
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

                                } while (pesi[i][j] < 1); // i pesi inseriti devono essere positivi e diversi da 0
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
}
void inizializza(size_t c, size_t r, int matrice[c][r], int nodi)
{
    int i, j;
    for (i = 0; i < nodi; i++)
    {
        for (j = 0; j < nodi; j++)
        {
            matrice[i][j] = MAX;
        }
    }
}
int scelta()
{
    int sceltaDEF;
    do
    {
        wprintf(L"1) Soluzione di Default\n2) Soluzione con dati inseriti dall'utente\n");
        scanf("%d", &sceltaDEF);
        if (sceltaDEF != 1 && sceltaDEF != 2)
        {
            wprintf(L"Opzione non valida,riprova\n");
        }
    } while (sceltaDEF != 1 && sceltaDEF != 2);
    return sceltaDEF;
}
/*void splash()
{
    if (detect() == -1)
    {
        wprintf(L"PIATTAFORMA NON SUPPORTATA");
        exit(-1);
    }
    // per centrare le scritte
    wprintf(L" _                                     _        \n");
    wprintf(L"| |                                   | |       \n");
    wprintf(L"| |__   ___ _ ____   _____ _ __  _   _| |_ ___  \n");
    wprintf(L"| '_ \\ / _ \\ '_ \\ \\ / / _ \\ '_ \\| | | | __/ _ \\ \n");
    wprintf(L"| |_) |  __/ | | \\ V /  __/ | | | |_| | || (_) |\n");
    wprintf(L"|_.__/ \\___|_| |_|\\_/ \\___|_| |_|\\__,_|\\__\\___/ \n");
    wprintf(L"Impementazione dell'algoritmo di dijkstra\n");
    //sleep(1);
    pulisci();
}*/
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
void pulisci() // pulisce lo schermo
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
