#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#define MAX 999
void inserimento(int pesi[][5], int nodi, int flag);
int main() {
  int mat[5][5];
  inserimento(mat,5,0);
    return 0;
}
void inserimento(int pesi[][5], int nodi, int flag) // funzione per l'impot di una matrice nodi per nodi al momento statica
{
  setlocale( LC_ALL, "en_US.UTF-8" );
    int i, j ; 
    if (flag == 0)
    {
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
    }
    for (i = 0; i < nodi; i++)
    {
      wprintf(L"\n");
        for (j = 0; j < nodi; j++)
        {
          if(pesi[i][j]==MAX)
          {
            wprintf (L"%lc ", 8734);
          }
          else
            {
              wprintf(L"%d ", pesi[i][j]);
            }
            
        }
    }
}