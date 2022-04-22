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

//    	cose da fare
// partenza arrivo a lettere        - FATTO
// percorso finale                  - FATTO
// modifica dati					- FATTO
// sistemare stampe                 - FATTO, e come poi
// sistemare commenti               - FATTO
// altri cammini possibili          - DA FARE, lo faremo mai?
// sistemare lettere                - FATTO
// scrittura su file                - FATTO

// librerie generiche
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#ifdef _WIN32 // se siamo su windows include le librerie specifiche per windows
#include <windows.h>
// per controllare se un file esiste
#include <io.h>
#define F_OK 0
#define access _access
// fine esistenza file
#elif __linux__        // altrimenti librerie specifiche per linux
#include <unistd.h>    //sleep
#include <sys/ioctl.h> //righe colonne
#include <unistd.h>
#endif
#define MAX ((int)(~0u >> 1u)) // massimo valore che pu� immagazzinare una variabile di tipo intero

// PROTOTIPI FUNZIONI

void inizializza(size_t, size_t, int[*][*], int nodi);                                                                        // Funzione di inizializzazione a MAX
void default5(size_t, size_t, int[*][*]);                                                                                     // Matrice di default a 5 nodi
void default10(size_t, size_t, int[*][*]);                                                                                    // Matrice di default a 10 nodi
void custom(size_t, size_t, int[*][*]);                                                                                       // matrice di default a nodi variabili contiene 7 nodi
void pulisci();                                                                                                               // pulisce lo schermo
int detect();                                                                                                                 // restituiisce il sistema operativo dove � in esecuzione il programma
void splash(int righe);                                                                                                       // restituisce il numero di colonne
int scelta(int righe);                                                                                                        // scelta del grafo tra custom e default
void inserimento(size_t, size_t, int pesi[*][*], int nodi, int flag, int righe);                                              // input
void outputWindows(size_t, size_t, int pesi[*][*], int nodi);                                                                 // output per windows, senza il simbolo dell'infinito, non supportato
void outputLinux(size_t, size_t, int pesi[*][*], int nodi);                                                                   // output per linux con il simbolo dell'infinito al posto di INF
void output(size_t, int mat[*][*], int nodi);                                                                                 // stampa della matrice
void dijkstra(FILE *fp, size_t, size_t, int pesi[*][*], int nodi);                                                            // calcolo
int visitato(int visit[], int nodi, int arrivo);                                                                              // controllo se tutti i nodi sono visitati
void stamparobe(int visit[], int costi[], int prec[], int nodi);                                                              // stampa tutti i vettori (prec, costi, visit)
int prendirighe();                                                                                                            // trova la dimensione della finestra per adattare la stampa
int percorso(int Vpercorso[], int costi[], int dest, int part, int prec[], int nodi);                                         // risale il percorso e lo stampa
void modifica(size_t, size_t, int pesi[*][*], int nodi, int flag);                                                            // modifica i dati di una matrice
void stampaFILE(FILE *fp, size_t, size_t, int pesi[*][*], int nodi, int Vpercorso[], int part, int jFILE, int min, int dest); // stampa su file

int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");
    int righe = prendirighe(); // wprintf(L"r=%d\n", righe);
    splash(righe);
    int mat5[5][5];    // matrice da riempire con i dati di default, in caso di input dell'utente sovrascrivre e inserire i dati.
    int mat10[10][10]; // stessa cosa
    int Grafo;
    int nodi;
    int sceltaNODI, sceltaDEF;
    FILE *fp;
    size_t DIM; // dimensione matrice
    do
    {
        righe = prendirighe(); // per centrare la scritta
        wprintf(L"%*s --- DIJSKTRA ---\n\n", righe - 9, "");
        wprintf(L"%*s1) Grafo a 5 nodi\n%*s2) Grafo a 10 nodi\n%*s3) Grafo a nodi variabili\n%*s    Premi qualsiasi altro numero per uscire\n\n\n", righe - 9, "", righe - 9, "", righe - 12, "", righe - 21, "");
        wprintf(L"%*sOpzione: ", righe - 5, "");
        scanf("%d", &sceltaNODI);
        pulisci();
        switch (sceltaNODI) // scelta dei nodi del grafo
        {
        case 1: // 5 nodi, quindi la matrice sarà 5x5
            DIM = 5;
            nodi = 5;
            inizializza(DIM, DIM, mat5, nodi); // portiamo tutto a max inizializzando la matrice
            sceltaDEF = scelta(righe);         // grafo default o personalizzato
            switch (sceltaDEF)
            {
            case 1:                                 // grafo default
                default5(DIM, DIM, mat5);           // riempio con la matrice di default
                output(DIM, mat5, nodi);            // stampo la matrice reindirizzando alle funzioni specifiche per windows e linux
                dijkstra(fp, DIM, DIM, mat5, nodi); // calcolo il cammio minimo
                break;
            case 2:
                inserimento(DIM, DIM, mat5, nodi, 0, righe); // input personalizzato
                output(DIM, mat5, nodi);
                dijkstra(fp, DIM, DIM, mat5, nodi);
                break;
            }
            break;
        case 2: // matrice 10*10 stessa cosa della matrice a 5 nodi
            DIM = 10;
            nodi = 10;
            inizializza(DIM, DIM, mat10, nodi);
            sceltaDEF = scelta(righe);
            switch (sceltaDEF)
            {
            case 1:
                default10(DIM, DIM, mat10);
                output(DIM, mat10, nodi);
                dijkstra(fp, DIM, DIM, mat10, nodi);
                break;
            case 2:
                inserimento(DIM, DIM, mat10, nodi, 0, righe); // lo 0 serve alla funzione di output per non chiedere se è orientato o meno, visto che è orientato
                output(DIM, mat10, nodi);
                dijkstra(fp, DIM, DIM, mat10, nodi);
                break;
            }
            break;
        case 3: // matrice a nodi personalizzati
            sceltaDEF = scelta(righe);
            if (sceltaDEF == 1) // la matrice di default è a 7 nodi
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
                    if (nodi < 3) // controlli
                    {
                        wprintf(L"\n%*sIl numero di nodi deve essere maggiore di 2\n", righe - 21, "");
                        cont++;
                        if (cont > 3)
                        {
                            wprintf(L"%*sSbagliare e' umano, perseverare e' diabolico\n", righe - 20, ""); // easter egg
                        }
                    }
                } while (nodi < 3);
                DIM = nodi; // la dimensione della matrice varia in base al numero di nodi
            }
            int MATcustom[DIM][DIM]; // dichiarazioned ella matrice
            inizializza(DIM, DIM, MATcustom, nodi);
            switch (sceltaDEF)
            {
            case 1:                           // matrice di default a nodi personalizzati
                custom(DIM, DIM, MATcustom);  // riempio la matrice con i dati di default
                output(DIM, MATcustom, nodi); // stampo la matrice
                dijkstra(fp, DIM, DIM, MATcustom, nodi);
                break;
            case 2:
                inserimento(DIM, DIM, MATcustom, nodi, 1, righe); // flag 1, chiedo se il grafo è orientato o meno
                output(DIM, MATcustom, nodi);
                dijkstra(fp, DIM, DIM, MATcustom, nodi);
                break;
            }
            break;
        }
        // fine di un iterazione del while, pulisco lo shcermo
        wprintf(L"\n");
        if (detect() == 1) // system pouse per linux
        {
            char tmp[0];
            wprintf(L"%*sPremi un tasto per continuare...\n", righe - 16, "");
            scanf("%s", tmp);
        }
        else // system pause nativo per windows
            system("PAUSE");
        pulisci();
    } while (sceltaNODI > 0 && sceltaNODI < 4); // il ciclo termina quando si inserisono valori non compresi tra 1 e 3
}
int prendirighe() // funzione che restituisce il numero di colonne del terminale così da adattare l'interfaccia
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
void output(size_t DIM, int mat[DIM][DIM], int nodi) // indirizzamento alle fuznioni specifiche per l'output
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
    if (nodi < 26) // se i nodi sono più di 26 stampo a numeri
    {
        int lettere = 65;
        wprintf(L"\\");
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
                    wprintf(L"\tINF "); // non è presento il simbolo dell, infinito quindi stampo INF
                }
                else
                {
                    wprintf(L"\t%d ", pesi[i][j]); // tampo i dati della matirce se sono presenti (!=MAX)
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
    fflush(stdout);                   // pulisco il buffer video
    setlocale(LC_ALL, "en_US.UTF-8"); // inizializzo wprintf in modo da stampare i caratteri in UTF-8, tra qui l'infinito
    pulisci();
    int i, j;
    if (nodi < 26)
    {
        int lettere = 65;
        wprintf(L"\\");
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
                    wprintf(L"\t%lc ", 8734); // infinito
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
    int orient, scelta1, scelta;
    int cont = 0;
    int lettere = 65; // per lka stampa a lettere se possibile
    fflush(stdout);
    fflush(stdin);
    if (flag == 1) // flag passata tramite parametro, chiedo se è oruientato solo nella terza opzione
    {
        do
        {
            wprintf(L"%*sil grafo e' orientato?\n%*s 1) SI\n %*s2) NO\n", righe - 11, "", righe - 1, "", righe - 1, "");
            scanf("%d", &orient);
        } while (orient != 1 && orient != 2); // controllo input
    }
    else if (flag == 0)
    {
        orient = 1; // nella prima e seconda il grafo è orientato
    }
    switch (orient)
    {
    case 1: // input orientato
        for (i = 0; i < nodi; i++)
        {
            for (j = 0; j < nodi; j++)
            {
                if (i != j)
                {
                    if (nodi < 26) // stampa a lettere solo se ci sono abbastanza lettere
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
                    else
                    {
                        do
                        {
                            wprintf(L"%*sil nodo %d e' collegato al nodo %d\n%*s1) SI\n%*s2) NO)\n", righe - 17, "", i, j, righe - 1, "", righe - 1, "");
                            scanf("%d", &scelta1);
                        } while (scelta1 != 1 && scelta1 != 2);
                        if (scelta1 == 1)
                        {
                            do
                            {
                                wprintf(L"%*sinserire peso tra il nodo %d e il nodo %d: ", righe - 12, "", i, j);
                                scanf("%d", &pesi[i][j]);
                            } while (pesi[i][j] < 1); // i pesi inseriti devono essere positivi e diversi da 0
                        }
                    }
                }
            }
            // output tabellare
            pulisci();
            wprintf(L"\\");
            if (nodi < 26)
            {
                for (cont = 0; cont < nodi; cont++) // stampo le lettere in orizzontale in base ai nodi
                {
                    wprintf(L"\t%c", 65 + cont);
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
                            if (detect() == 0) // stampo o inf o infinitito a seconda del sistema operativo
                            {
                                wprintf(L"\tINF");
                            }
                            else if (detect() == 1)
                            {
                                wprintf(L"\t%lc", 8734);
                            }
                        }
                        else
                        {
                            wprintf(L"\t%d", pesi[k][y]);
                        }
                    }
                    wprintf(L"\n");
                }
            }
            else
            {
                for (cont = 0; cont < nodi; cont++) // stmpo a numeri se i nuodi sono più id 26
                {
                    wprintf(L"\t%d", cont);
                }
                cont = 0;
                for (k = 0; k <= i; k++) // righe
                {
                    wprintf(L"\n");
                    wprintf(L"%d", cont);
                    cont++;
                    for (y = 0; y < nodi; y++) // colonne
                    {
                        if (pesi[k][y] == MAX)
                        {
                            if (detect() == 0)
                            {
                                wprintf(L"\tINF");
                            }
                            else if (detect() == 1)
                            {
                                wprintf(L"\t%lc", 8734);
                            }
                        }
                        else
                        {
                            wprintf(L"\t%d", pesi[k][y]);
                        }
                    }
                    wprintf(L"\n");
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
                        if (nodi < 26) // lettere
                        {
                            do
                            {
                                wprintf(L"%*sil nodo %c e' collegato al nodo %c\n%*s1) SI\n%*s2) NO)\n", righe - 17, "", 65 + i, 65 + j, righe - 1, "", righe - 1, "");
                                scanf("%d", &scelta);
                                if (scelta == 1)
                                {
                                    do // controllO
                                    {
                                        wprintf(L"%*sinserire peso tra %c e %c: ", righe - 12, "", 65 + i, 65 + j);
                                        scanf("%d", &pesi[i][j]);
                                    } while (pesi[i][j] < 1); // i pesi inseriti devono essere positivi e diversi da 0
                                }
                                else
                                {
                                    pesi[i][j] = 9998; // se non si vuole collegare il nodo allora il peso è infinito ma non andrà richiesto essedo il grafo non orientato
                                }                      // quindi temporaneamente sarà 9998, ma poi sarà portao a MAX
                                pesi[j][i] = pesi[i][j];
                            } while (scelta < 1 || scelta > 2); // controllo
                        }
                        else // numeri
                        {
                            do
                            {
                                wprintf(L"%*sil nodo %d e' collegato al nodo %d\n%*s1) SI\n%*s2) NO)\n", righe - 17, "", i, j, righe - 1, "", righe - 1, "");
                                scanf("%d", &scelta);
                                if (scelta == 1)
                                {
                                    do
                                    {
                                        wprintf(L"%*sinserire peso tra il nodo %d e il nodo %d: ", righe - 12, "", i, j);
                                        scanf("%d", &pesi[i][j]);
                                    } while (pesi[i][j] < 1); // i pesi inseriti devono essere positivi e diversi da 0
                                }
                                else
                                {
                                    pesi[i][j] = 9998;
                                }
                                pesi[j][i] = pesi[i][j];
                            } while (scelta < 1 || scelta > 2);
                        }
                    }
                }
            }
            // output tabellare, stesso ragionamneto precente
            pulisci();
            wprintf(L"\\");
            if (nodi < 26)
            {
                for (cont = 0; cont < nodi; cont++)
                {
                    wprintf(L"\t%c", 65 + cont);
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
                                wprintf(L"\tINF");
                            }
                            else if (detect() == 1)
                            {
                                wprintf(L"\t%lc", 8734);
                            }
                        }
                        else
                        {
                            wprintf(L"\t%d", pesi[k][y]);
                        }
                    }
                    wprintf(L"\n");
                }
            }
            else
            {
                for (cont = 0; cont < nodi; cont++)
                {
                    wprintf(L"\t%d", cont);
                }
                cont = 0;
                for (k = 0; k <= i; k++) // righe
                {
                    wprintf(L"\n");
                    wprintf(L"%d", cont);
                    cont++;
                    for (y = 0; y < nodi; y++) // colonne
                    {
                        if (pesi[k][y] == MAX || pesi[k][y] == 9998)
                        {
                            if (detect() == 0)
                            {
                                wprintf(L"\tINF");
                            }
                            else if (detect() == 1)
                            {
                                wprintf(L"\t%lc", 8734);
                            }
                        }
                        else
                        {
                            wprintf(L"\t%d", pesi[k][y]);
                        }
                    }
                    wprintf(L"\n");
                }
            }
        }
        for (i = 0; i < nodi; i++) // riportiamo a max sul grafo non orientato i nodi che hanno 9998
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
    modifica(c, r, pesi, nodi, orient); // se si vuole modificare qualcosa nella matrice
}
void dijkstra(FILE *fp, size_t c, size_t r, int pesi[c][r], int nodi)
{
    int part, dest;      // nodo di partenza e di destinazione
    int prec[nodi];      // vettori di predecessori
    int costi[nodi];     // vettori dei costi
    int visit[nodi];     // vettori di visitati
    int Vpercorso[nodi]; // vettore contenetnte il percorso
    int i = 0, j = 0;
    int Cmin; // costo minimo
    int prossimoNodo;
    int attuale = part;
    int cont = 0;
    char Npart[1], Ndest[1];
    int scelta;
    int CminFILE; // costo minimo da stmpare nel file
    do            // input con relatrivi controlli per la partenza e l'arrivo
    {
        if (nodi < 26) // input a lettere
        {
            wprintf(L"\ninserire nodo di partenza: \n(Es: A): ");
            fflush(stdin);
            scanf("%s", Npart);
            Npart[0] = toupper(Npart[0]); // se inseriamo una lettera minuscola diventa grande
            part = Npart[0] - 65;         // convertiamo la lettera in un numero
        }
        else // numeri
        {
            wprintf(L"\nInserisci il nodo di partenza \n(Es: 0): ");
            fflush(stdin);
            scanf("%d", &part);
        }
        if (part < 0 || part > nodi)
        {
            wprintf(L"\nNodo non valido");
        }
    } while (part < 0 || part > nodi); // la partenza non puo' essere minore di 0 o maggiore dei nodi
    fflush(stdin);
    // input della destinazione, stella logica della partenza
    do
    {
        if (nodi < 26) // input partyenza
        {
            wprintf(L"\ninserire nodo di destinazione: \n(Es: C): ");
            scanf("%s", Ndest);
            Ndest[0] = toupper(Ndest[0]);
            dest = Ndest[0] - 65;
        }
        else
        {
            wprintf(L"\nInserisci il nodo di destinazione \n(Es: 2, Il primo nodo e' 0 ): ");
            scanf("%d", &dest);
        }
        if (dest < 0 || dest >= nodi)
        {
            wprintf(L"\nNodo non valido");
        }
    } while (dest < 0 || dest >= nodi);
    if (part == dest) // controllo
    {
        wprintf(L"\nIl nodo di partenza e di arrivo coincidono");
        return;
    }
    for (i = 0; i < nodi; i++) // inizializzazione vettore costi precedenti e visitati
    {
        costi[i] = pesi[part][i];
        if (costi[i] != MAX) // se ci sono collegamenti
        {
            prec[i] = part;
        }
        else
        {
            prec[i] = -1;
        }
        visit[i] = 0;
    }
    visit[part] = 1;                         // la partenza sarà sempre visitata
    while (visitato(visit, nodi, dest) == 1) // finche non visiamo tutti i nodi continuaimo ad esplorare
    {
        Cmin = MAX;                // il costo minimo iniziale è infinito
        for (i = 0; i < nodi; i++) // per il numero di nodi nel grafo
        {
            if (costi[i] < Cmin && visit[i] == 0 && i != dest) // se abbiamo un nodo che non sia la destinazione, non è visitato e il costo minimo è minore di quello attuale sostituiamo il costo minimo con quello attuale e il nodo attuale diventerà il prossimo
            {
                Cmin = costi[i];
                attuale = i;
                cont = 0;
            }
            else if (Cmin == MAX && visit[i] == 0 && i != dest) // SE il nodo non è esplorabile non aggiorniamo il costo e lo segmamo come visitato
            {
                attuale = i;
                cont = 1;
            }
        }
        if (cont == 1) // segmamo come visitato
        {
            visit[attuale] = 1;
        }
        else
        {
            for (i = 0; i < nodi; i++)
            {
                if (pesi[attuale][i] != MAX && visit[i] == 0) // se non è visitato e se possiamo arrivarci
                {
                    if (costi[attuale] + pesi[attuale][i] < costi[i]) // se conviene andare al nodo successivo
                    {
                        costi[i] = costi[attuale] + pesi[attuale][i]; // aggiorniamo il costo totale
                        prec[i] = attuale;                            // riempiamo il vettore dei precedenti
                    }
                }
            }
            visit[attuale] = 1; // nodo visitato, riempiamo il vettore dei visitati
        }
        // stamparobe(visit, costi, prec, nodi);
    }
    int jFILE = percorso(Vpercorso, costi, dest, part, prec, nodi); // stampiamo il percorso restituendo la posizione di partenza del vettore percorso
    if (jFILE != -1)
    {
        do // stampa su file domanda con relativi controlli
        {
            wprintf(L"\nVuoi stampare i risultati nel file?\n1) Si\n2) No\n");
            scanf("%d", &scelta);
        } while (scelta != 1 && scelta != 2);
        if (scelta == 1)
        {
            CminFILE = costi[dest];
            stampaFILE(fp, c, r, pesi, nodi, Vpercorso, part, jFILE, CminFILE, dest);
            wprintf(L"\nFatto!\n");
        }
        else
        {
            wprintf(L"\nNon stampero' nel file");
        }
    }
}
int percorso(int Vpercorso[], int costi[], int dest, int part, int prec[], int nodi)
{
    int i = 0;
    int j = 0;
    int flag = 0;
    int jFILE;
    for (int i = 0; i < nodi; i++) // inizialzione
    {
        Vpercorso[i] = -1;
    }
    if (costi[dest] == MAX) // controllo
    {
        wprintf(L"\nNon esiste un percorso tra i nodi inseriti");
        return -1; // codice errore
    }
    else
    {
        wprintf(L"\nIl percorso minimo e' di %d", costi[dest]);
        wprintf(L"\nIl percorso e': ");
        for (i = dest; prec[i] != -1; i = prec[i]) // risale il percorso al contrario
        {
            Vpercorso[j] = i;
            j++;
        }
        for (i = 0; i < nodi; i++)
        {
            if (Vpercorso[i] > 26)
            {
                flag = 1; // stampo il percorso a lettere
            }
        }
        jFILE = j;
        if (flag == 0)
        {
            wprintf(L"%c --> ", part + 65); // partenza
            for (j = j - 1; j > 0; j--)     // nodi di mezzo
            {
                wprintf(L"%c --> ", Vpercorso[j] + 65);
            }
            j = 0;
            wprintf(L"%c", Vpercorso[j] + 65); // arrivo
        }
        else
        {
            wprintf(L"%d --> ", part);
            for (j = j - 1; j > 0; j--)
            {
                wprintf(L"%d --> ", Vpercorso[j]);
            }
            j = 0;
            wprintf(L"%d", Vpercorso[j]);
        }
    }
    return jFILE;
}
void inizializza(size_t c, size_t r, int matrice[c][r], int nodi)
{
    int i, j;
    for (i = 0; i < nodi; i++)
    {
        for (j = 0; j < nodi; j++)
        {
            matrice[i][j] = MAX; // inizializzo la matrice dei pesi a max (infinito) per eseguire l'input
        }
    }
}
int scelta(int righe)
{
    int sceltaDEF;
    do // scelta con input controllato
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
void splash(int righe) // spash screen di benvenuto
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
    Sleep(2000);
#elif __linux__
    sleep(2);
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
    if (detect() == 0) // windows
    {
        system("cls");
    }
    else if (detect() == 1) // linux
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
void custom(size_t c, size_t r, int matrice[c][r]) // matrice presa da internet
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
int visitato(int visit[], int nodi, int arrivo) // controlla se tutti i nodi sono esplorati
{
    int i, cont = 0;
    for (i = 0; i < nodi; i++)
    {
        if (visit[i] == 0 && i != arrivo) // se il nodo non è stato esplorato e non è l'arrivo
            cont = 1;
    }
    if (cont == 1)
        return 1;
    return 0; // tutti esploarti
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
void modifica(size_t c, size_t r, int pesi[c][r], int nodi, int flag) // consente di modificare archi del grafo una volta presi in input
{
    int mod;
    char part[1]; // per le lettere
    char dest[1];
    int p, d;
    do
    {
        wprintf(L"\nVuoi modificare qualche dato?\n1) SI\n2) NO)\n\nScelta: ");
        scanf("%d", &mod);
        if (mod == 1)
        {
            if (nodi < 26)
            {
                // input a lettere portandole maiuscole
                wprintf(L"\nQuale arco vuoi modificare?\nNodo di partenza (Es. A): ");
                scanf("%s", part);
                part[0] = toupper(part[0]);
                p = part[0] - 65;
                wprintf(L"\nNodo di arrivo (Es E): ");
                scanf("%s", dest);
                dest[0] = toupper(dest[0]);
                d = dest[0] - 65; // convertiamo a numero
            }
            else // numeri
            {
                wprintf(L"\nQuale arco vuoi modificare?\nNodo di partenza (Es. 0): ");
                scanf("%d", &p);
                wprintf(L"\nNodo di arrivo (Es 4): ");
                scanf("%d", &d);
            }
            if (p == d) // controllo
            {
                wprintf(L"\n\nErrore - Hai inserito lo stesso nodo\n\n");
            }
            else if (p > nodi || d > nodi)
            {
                wprintf(L"Impossibile modificare l'arco selezionato\n");
            }
            else
            {
                wprintf(L"\n\n\n\t\t\t%d\n\n\n", flag);
                wprintf(L"\n\nInserisci nuovo valore: ");
                scanf("%d", &pesi[p][d]);
                if (flag == 2) // se il grafo non è orentato
                {
                    pesi[d][p] = pesi[p][d];
                }
                output(c, pesi, nodi); // stampiamo la matrice aggiornata
            }
        }
        else
        {
            return;
        }
    } while (mod != 1); // finche non si dicita un numero diverso da 1
}
void stampaFILE(FILE *fp, size_t c, size_t r, int pesi[c][r], int nodi, int Vpercorso[], int part, int jFILE, int min, int dest)
{
    // controllo esistenza del file
    if (access("Dijkstra.txt", F_OK) == 0)
    {
        fp = fopen("Dijkstra.txt", "a"); // il file esiste lo apro in append
    }
    else
    {
        fp = fopen("Dijkstra.txt", "w"); // il file non esiste lo creo e lo apro in write
    }
    fprintf(fp, "Calcolo del cammino minimo con Dijkstra con un grafo a %d nodi\n", nodi);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t); // prendo l'orario e la data corrente
    fprintf(fp, "Cammino minimo creato in data: %d-%02d-%02d orario: %02d:%02d:%02d\n\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    // variabili
    int i, j;
    int flag = 0;
    // stampo la matrice
    if (nodi < 26) // se i nodi sono più di 26 stampo a numeri
    {
        int lettere = 65;
        fprintf(fp, "\\");
        for (i = 0; i < nodi; i++)
        {
            fprintf(fp, "\t%c", lettere);
            lettere++;
        }
        lettere = 65;
        for (i = 0; i < nodi; i++)
        {
            fprintf(fp, "\n");
            fprintf(fp, "%c", lettere);
            lettere++;
            for (j = 0; j < nodi; j++)
            {
                if (pesi[i][j] == MAX)
                {
                    fprintf(fp, "\tINF ");
                }
                else
                {
                    fprintf(fp, "\t%d ", pesi[i][j]);
                }
            }
        }
    }
    else // stampo a numeri
    {
        int cont = 0;
        fprintf(fp, "\\");
        for (cont = 0; cont < nodi; cont++)
        {
            fprintf(fp, "\t%d", cont);
        }
        for (i = 0; i < nodi; i++)
        {
            fprintf(fp, "\n");
            fprintf(fp, "%d", i);
            for (j = 0; j < nodi; j++)
            {
                if (pesi[i][j] == MAX)
                {
                    fprintf(fp, "\tINF ");
                }
                else
                {
                    fprintf(fp, "\t%d ", pesi[i][j]);
                }
            }
        }
    }
    fprintf(fp, "\n\n");
    // stampo il costo minimo
    j = jFILE;
    if (nodi < 26)
    {
        fprintf(fp, "Costo minimo per andare da %c a %c: %d\n", part + 65, dest + 65, min);
    }
    else
    {
        fprintf(fp, "Costo minimo per andare da %d a %d: %d\n", part, dest, min);
    }
    // stampo il percorso minimo
    fprintf(fp, "\nPercorso minimo: \n");
    for (i = 0; i < nodi; i++)
    {
        if (Vpercorso[i] > 26)
        {
            flag = 1; // stampo il percorso a lettere
        }
    }
    if (flag == 0)
    {
        fprintf(fp, "%c --> ", part + 65);
        for (j = j - 1; j > 0; j--)
        {
            fprintf(fp, "%c --> ", Vpercorso[j] + 65);
        }
        j = 0;
        fprintf(fp, "%c", Vpercorso[j] + 65);
    }
    else
    {
        fprintf(fp, "%d --> ", part);
        for (j = j - 1; j > 0; j--)
        {
            fprintf(fp, "%d --> ", Vpercorso[j]);
        }
        j = 0;
        fprintf(fp, "%d", Vpercorso[j]);
    }
    fprintf(fp, "\n\n");
    fclose(fp); // chiudo il file
}