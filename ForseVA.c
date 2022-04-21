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

//    cose da fare
// partenza arrivo a lettere        - FATTO
// percorso finale                  - DA FARE
// sistemare stampe                 - FATTO, e come poi
// sistemare commenti               - DA FARE
// altri cammini possibili          - DA FARE MA NON SI SA COME

// libreirie generiche
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <limits.h>
#include <string.h>

#ifdef _WIN32 // se siamo su windows include le librerie specifiche per windows
#include <windows.h>
#elif __linux__        // altrimenti per linux
#include <unistd.h>    //sleep
#include <sys/ioctl.h> //righe colonne
#endif

#define MAX ((int)(~0u >> 1u)) // massimo valore che può immagazzinare una variabile di tipo intero

void inizializza(size_t, size_t, int[*][*], int nodi);                           // Funzione di inizializzazione a MAX
void default5(size_t, size_t, int[*][*]);                                        // Matrice di default a 5 nodi
void default10(size_t, size_t, int[*][*]);                                       // Matrice di default a 10 nodi
void custom(size_t, size_t, int[*][*]);                                          // matrice di default a nodi variabili contiene 7 nodi
void pulisci();                                                                  // pulisce lo schermo
int detect();                                                                    // restituiisce il sistema operativo dove è in esecuzione il programma
void splash(int righe);                                                          // restituisce il numero di colonne
int scelta(int righe);                                                           // scelta del grafo tra custom e default
void inserimento(size_t, size_t, int pesi[*][*], int nodi, int flag, int righe); // input
void outputWindows(size_t, size_t, int pesi[*][*], int nodi);                    // output per windows, senza il simbolo dell'infinito, non supportato
void outputLinux(size_t, size_t, int pesi[*][*], int nodi);                      // output per linux con il simbolo dell'infinito al posto di INF
void output(size_t, int mat[*][*], int nodi);
void dijkstra(size_t, size_t, int pesi[*][*], int nodi);
int visitato(int visit[], int nodi, int arrivo);
void stamparobe(int visit[], int costi[], int prec[], int nodi);
int prendirighe();
void percorso(int costi[], int dest, int part, int prec[], int nodi);

int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");
    int righe = prendirighe(); // wprintf(L"r=%d\n", righe);
    splash(righe);
    int mat5[5][5];    // matrice da riempire con i dati di default, in caso di input dell'utente sovrascrivre e inserire i dati.
    int mat10[10][10]; // stessa cosa
    int Grafo;
    int nodi;
    int sceltaNODi, sceltaDEF;
    size_t DIM; // dimensione matrice
    do
    {
        righe = prendirighe();
        wprintf(L"%*s --- DIJSKTRA ---\n\n", righe - 9, "");
        wprintf(L"%*s1) Grafo a 5 nodi\n%*s2) Grafo a 10 nodi\n%*s3) Grafo a nodi variabili\n%*s?) Premi qualsiasi altro numero per uscire\n\n\n", righe - 9, "", righe - 9, "", righe - 12, "", righe - 21, "");
        wprintf(L"%*sOpzione: ", righe - 5, "");
        scanf("%d", &sceltaNODi);
        pulisci();
        switch (sceltaNODi)
        {
        case 1:
            DIM = 5;
            nodi = 5;
            inizializza(DIM, DIM, mat5, nodi);
            sceltaDEF = scelta(righe);
            switch (sceltaDEF)
            {
            case 1:
                default5(DIM, DIM, mat5);
                output(DIM, mat5, nodi);
                dijkstra(DIM, DIM, mat5, nodi);
                break;
            case 2:
                inserimento(DIM, DIM, mat5, nodi, 0, righe);
                output(DIM, mat5, nodi);
                dijkstra(DIM, DIM, mat5, nodi);
                break;
            }
            break;
        case 2:
            DIM = 10;
            nodi = 10;
            inizializza(DIM, DIM, mat10, nodi);
            sceltaDEF = scelta(righe);
            switch (sceltaDEF)
            {
            case 1:
                default10(DIM, DIM, mat10);
                output(DIM, mat10, nodi);
                dijkstra(DIM, DIM, mat10, nodi);
                break;
            case 2:
                inserimento(DIM, DIM, mat10, nodi, 0, righe);
                output(DIM, mat10, nodi);
                dijkstra(DIM, DIM, mat10, nodi);
                break;
            }
            break;
        case 3:
            sceltaDEF = scelta(righe);
            if (sceltaDEF == 1)
            {
                DIM = 7;
                nodi = 7;
            }
            else if (sceltaDEF == 2)
            {
                int cont = 0;
                do
                {
                    wprintf(L"%*sInserire il numero di nodi: ", righe - 14, "");
                    scanf("%d", &nodi);
                    if (nodi < 3)
                    {
                        wprintf(L"\n%*sIl numero di nodi deve essere maggiore di 2\n", righe - 21, "");
                        cont++;
                        if (cont > 3)
                        {
                            wprintf(L"%*sSbagliare e' umano, perseverare e' diabolico\n", righe - 20, "");
                        }
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
                dijkstra(DIM, DIM, MATcustom, nodi);
                break;
            case 2:
                inserimento(DIM, DIM, MATcustom, nodi, 1, righe);
                output(DIM, MATcustom, nodi);
                dijkstra(DIM, DIM, MATcustom, nodi);
                break;
            }
            break;
        }
        wprintf(L"\n");
        if (detect() == 1)
        {
            char tmp[0];
            wprintf(L"%*sPremi un tasto per continuare...\n", righe - 16, "");
            scanf("%s", tmp);
        }
        else
            system("PAUSE");
        pulisci();
    } while (sceltaNODi > 0 && sceltaNODi < 4);
}
int prendirighe()
{
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return ((csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2);
#elif __linux__
    struct winsize ws; // struct dinamica per allocare il numero di righe e colonne del terminale in base alla dimensione dello schermo
    ioctl(1, TIOCGWINSZ, &ws);
    int colonne = ws.ws_col; // prendo le colonne
    colonne = colonne / 2;   // colonne /2 per arribvare al centro dello schermo
    return colonne;
#endif
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
    fflush(stdout);
    setlocale(LC_ALL, "en_US.UTF-8");
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
void inserimento(size_t c, size_t r, int pesi[c][r], int nodi, int flag, int righe) // funzione per l'imput di una matrice nodi per nodi al momento statica
{
    int i, j; // indici per i cicli principali
    int k, y; // indici per i cicli secondari
    int scelta, scelta1;
    int cont = 0;
    int lettere = 65;
    fflush(stdout);
    fflush(stdin);
    if (flag == 1)
    {
        do
        {
            wprintf(L"%*sil grafo e' orientato?\n%*s 1) SI\n %*s2) NO\n", righe - 11, "", righe - 1, "", righe - 1, "");
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
                        wprintf(L"%*sil nodo %c e' collegato al nodo %c\n%*s1) SI\n%*s2) NO)\n", righe - 17, "", 65 + i, 65 + j, righe - 1, "", righe - 1, "");
                        scanf("%d", &scelta1);
                    } while (scelta1 != 1 && scelta1 != 2);
                    if (scelta1 == 1)
                    {
                        do
                        {
                            wprintf(L"%*sinserire peso tra %c e %c: ", righe - 12, "", 65 + i, 65 + j);
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
                            wprintf(L"%*sil nodo %c e' collegato al nodo %c\n%*s1) SI\n%*s2) NO)\n", righe - 17, "", 65 + i, 65 + j, righe - 1, "", righe - 1, "");
                            scanf("%d", &scelta);
                            if (scelta == 1)
                            {
                                do
                                {
                                    wprintf(L"%*sinserire peso tra %c e %c: ", righe - 12, "", 65 + i, 65 + j);
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
void dijkstra(size_t c, size_t r, int pesi[c][r], int nodi)
{
    int part, dest;  // nodo di partenza e di destinazione
    int prec[nodi];  // vettori di predecessori
    int costi[nodi]; // vettori dei costi
    int visit[nodi]; // vettori di visitati
    int i = 0, j = 0;
    int Cmin; // costo minimo
    int prossimoNodo;
    int attuale = part;
    int cont = 0;
    char Npart[1], Ndest[1];
    do
    {
        if (nodi < 26)
        {
            wprintf(L"\ninserire nodo di partenza: \nEs Nodo A");
            fflush(stdin);
            scanf("%s", Npart);
            toupper(Npart[0]);
            part = Npart[0] - 65;
        }
        else
        {
            wprintf(L"\nInserisci il nodo di partenza \nEs Nodo 0");
            fflush(stdin);
            scanf("%d", &part);
        }
        if (part < 0 || part > nodi)
        {
            wprintf(L"\nNodo non valido");
        }
    } while (part < 0 || part > nodi);
    fflush(stdin);
    do
    {
        if (nodi < 26)
        {
            wprintf(L"\ninserire nodo di destinazione: \nEs Nodo C");
            scanf("%s", Ndest);
            toupper(Ndest[0]);
            // fgets(Ndest, 1, stdin);
            dest = Ndest[0] - 65;
        }
        else
        {
            wprintf(L"\nInserisci il nodo di destinazione \nEs Nodo 2");
            scanf("%d", &dest);
        }
        if (dest < 0 || dest >= nodi)
        {
            wprintf(L"\nNodo non valido");
        }
    } while (dest < 0 || dest >= nodi);
    if (part == dest)
    {
        wprintf(L"\nIl nodo di partenza e di arrivo coincidono");
        return;
    }
    for (i = 0; i < nodi; i++) // inizializzazione
    {
        costi[i] = pesi[part][i];
        if (costi[i] != MAX)
        {
            prec[i] = part;
        }
        else
        {
            prec[i] = -1;
        }
        visit[i] = 0;
    }
    visit[part] = 1;

    while (visitato(visit, nodi, dest) == 1)
    {
        Cmin = MAX;
        for (i = 0; i < nodi; i++)
        {
            if (costi[i] < Cmin && visit[i] == 0 && i != dest)
            {
                Cmin = costi[i];
                attuale = i;
                cont = 0;
            }
            else if (Cmin == MAX && visit[i] == 0 && i != dest)
            {
                attuale = i;
                cont = 1;
            }
        }
        if (cont == 1)
        {
            visit[attuale] = 1;
        }
        else
        {
            for (i = 0; i < nodi; i++)
            {
                if (pesi[attuale][i] != MAX && visit[i] == 0)
                {
                    if (costi[attuale] + pesi[attuale][i] < costi[i])
                    {
                        costi[i] = costi[attuale] + pesi[attuale][i];
                        prec[i] = attuale;
                    }
                }
            }
            visit[attuale] = 1;
        }
        // stamparobe(visit, costi, prec, nodi);
    }
    percorso(costi, dest, part, prec, nodi);
}
void percorso(int costi[], int dest, int part, int prec[], int nodi)
{
    int percorso[nodi]; // vettore del percorso minimo
    int i = 0;
    int j = 0;

    if (costi[dest] == MAX)
    {
        wprintf(L"\nNon esiste un percorso tra i nodi inseriti");
    }
    else
    {
        wprintf(L"\nIl percorso minimo e' di %d", costi[dest]);
        wprintf(L"\nIl percorso e': ");
        for (i = dest; prec[i] != -1; i = prec[i]) // risale il percorso al contrario
        {
            percorso[j] = i;
            j++;
        }
        wprintf(L"%c --> ", part + 65);
        for (j = j - 1; j > 0; j--)
        {
            wprintf(L"%c --> ", percorso[j] + 65);
        }
        j = 0;
        wprintf(L"%c", percorso[j] + 65);
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
int scelta(int righe)
{
    int sceltaDEF;
    do
    {
        wprintf(L"%*s1) Soluzione di Default\n%*s2) Soluzione con dati inseriti dall'utente\n", righe - 11, "", righe - 21, "");
        scanf("%d", &sceltaDEF);
        if (sceltaDEF != 1 && sceltaDEF != 2)
        {
            wprintf(L"%*sOpzione non valida,riprova\n", righe - 13, "");
        }
    } while (sceltaDEF != 1 && sceltaDEF != 2);
    return sceltaDEF;
}
void splash(int righe)
{
    pulisci();
    if (detect() == -1)
    {
        wprintf(L"PIATTAFORMA NON SUPPORTATA");
        exit(-1);
    }
    righe = righe - 26;
    wprintf(L"%*s _                                     _        \n", righe, "");
    wprintf(L"%*s| |                                   | |       \n", righe, "");
    wprintf(L"%*s| |__   ___ _ ____   _____ _ __  _   _| |_ ___  \n", righe, "");
    wprintf(L"%*s| |'_ \\ / _ \\ '_ \\ \\ / / _ \\ '_ \\| | | | __/ _ \\ \n", righe, "");
    wprintf(L"%*s| |_) |  __/ | | \\ V /  __/ | | | |_| | || (_) |\n", righe, "");
    wprintf(L"%*s|_.__/ \\___|_| |_|\\_/ \\___|_| |_|\\__,_|\\__\\___/ \n", righe, "");
#ifdef _WIN32
    Sleep(3000);
#elif __linux__
    sleep(3);
#endif
    pulisci();
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
int visitato(int visit[], int nodi, int arrivo)
{
    int i, cont = 0;
    for (i = 0; i < nodi; i++)
    {
        if (visit[i] == 0 && i != arrivo)
            cont = 1;
    }
    if (cont == 1)
        return 1; // tutti esplorati
    return 0;
}
void stamparobe(int visit[], int costi[], int prec[], int nodi)
{
    int i;
    wprintf(L"\n\n\nVisitati:");
    for (i = 0; i < nodi; i++)
    {
        wprintf(L"\n%d", visit[i]);
    }

    wprintf(L"\n\n\nCosti:");
    for (i = 0; i < nodi; i++)
    {
        wprintf(L"\n%d", costi[i]);
    }

    wprintf(L"\n\n\nPrec:");
    for (i = 0; i < nodi; i++)
    {
        wprintf(L"\n%d", prec[i]);
    }
}