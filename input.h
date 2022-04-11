#define MAX 9999
int indirizzamento(int default5[][5], int default10[][10], int custom[][MAX]) // return numero nodi
{
    int sceltaGrafo;
    int sceltaDefault;
    do
    {
        printf("Digita una delle opzioni: ");
        printf("1) Grafo a 5 nodi\n2) Grafo a 10 nodi\n3) Grafo a nodi variabili scelti dall' utente\n");
        scanf("%d", &sceltaGrafo;
    } while (sceltaGrafo != 1 && sceltaGrafo != 2 && sceltaGrafo != 3);
    switch (sceltaGrafo)
    {
    case 1:
        do
        {
            printf("Ora scegli Capece");
            printf("1) Grafo di defaul a 5 nodi\n2) Grafo con a 5 nodi con pesi inseriti dall' utente");
            scanf("%d", &sceltaDefault);
            switch (sceltaDefault)
            {
            case 1:
                // dijkstra(default5,5,0);
                break;
            case 2:
                // dijkstra(grafo,5,1);
                break;
            default:
                printf("scelta non valida, riprova");
                break;
            }
        } while (scelta != 1 && scelta != 2);
        break;
    case 2:
        do
        {
            printf("Ora scegli Capece");
            printf("1) Grafo di defaul a 10 nodi\n2) Grafo con a 10 nodi con pesi inseriti dall' utente");
            scanf("%d", &sceltaDefault);
            switch (sceltaDefault)
            {
            case 1:
                // dijkstra(default10,10,0);
                break;
            case 2:
                // dijkstra(grafo,10,1);
                break;
            default:
                printf("scelta non valida, riprova");
                break;
            }
        } while (scelta != 1 && scelta != 2);

        break;
    case 3:
        printf(L"inserire numero nodi: ");
        scanf("%d", &nodi);
        printf("Ora scegli Capece");
        printf("1) Grafo di defaul a %d nodi\n2) Grafo con a %d nodi con pesi inseriti dall' utente", nodi, nodi);
        scanf("%d", &sceltaDefault);
        switch (sceltaDefault)
        {
        case 1:
            // dijkstra(grafo,nodi);
            break;
        case 2:
            if (detect() == 0)
            {
                inserimentoWindows(grafo, nodi);
            }
            else if (detect() == 1)
            {
                inserimentoLinux(grafo, nodi);
            }
            else
            {
                printf("Piattaforma non supportata");
                exit(1);
            }
                
            // dijkstra(grafo,nodi);
            break;
        default:
            printf("scelta non valida, riprova");
            break;
        }
        break;
        break;
    default:
        break;
    }
}
void inserimentoLinux(int pesi[][MAX], int nodi, int flag) // funzione per l'impot di una matrice nodi per nodi al momento statica
{
    setlocale(LC_ALL, "en_US.UTF-8");
    int i, j;
    int scelta;
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
                if (i != j && pesi[i][j] != MAX)
                {
                    do
                    {
                        wprintf(L"il nodo %d è collegato al nodo %d\n(0=no,1=si)\n", i, j);
                        scanf("%d", &scelta);
                        if (scelta == 1)
                        {
                            do
                            {
                                wprintf(L"inserire peso tra %d e %d: ", i, j);
                                scanf("%d", &pesi[i][j]);
                                pesi[j][i] = pesi[i][j];
                            } while (pesi[i][j] < 0); // i pesi inseriti devono essere positivi e diversi da 0
                        }
                    } while (scelta != 0 || scelta != 1);
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
void inserimentoWindows(int pesi[][MAX], int nodi) // funzione per l'impot di una matrice nodi per nodi al momento statica
{
    setlocale(LC_ALL, "en_US.UTF-8");
    int i, j;
    int scelta;
    printf("inserire numero nodi: ");
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
        printf("il grafo è orientato?\n 1) si\n 2) no\n");
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
                        printf("il nodo %d è collegato al nodo %d\n(0=no,1=si)\n", i, j);
                        scanf("%d", &scelta);
                    } while (scelta != 0 && scelta != 1);
                    if (scelta == 1)
                    {
                        do
                        {
                            printf("inserire peso tra %d e %d: ", i, j);
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
                if (i != j && pesi[i][j] != MAX)
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
                                pesi[j][i] = pesi[i][j];
                            } while (pesi[i][j] < 0); // i pesi inseriti devono essere positivi e diversi da 0
                        }
                    } while (scelta != 0 || scelta != 1);
                }
            }
        }
        break;
    }
    for (i = 0; i < nodi; i++)
    {
        printf("\n");
        for (j = 0; j < nodi; j++)
        {
            if (pesi[i][j] == MAX)
            {
                printf("\tINF ");
            }
            else
            {
                printf("\t%d ", pesi[i][j]);
            }
        }
    }
}