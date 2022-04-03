void inserimento(int pesi[][MAX], int nodi) // funzione per l'impot di una matrice nodi per nodi al momento statica
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