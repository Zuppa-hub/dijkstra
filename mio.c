#include <stdio.h>
#include <stdlib.h>

#define angolo_destro_alto 191																//codici ascii
#define angolo_sinistro_alto 218
#define angolo_destro_basso 217
#define angolo_sinistro_basso 192
#define riga 196
#define riga_centrale_alta 194
#define riga_centrale_bassa 193
#define riga_centrale_centro 197
#define riga_sinistra 195
#define riga_destra 180
#define colonna 179

#define MAX 100
#define INF 999

void inserimento(int tabella[][100], int dim);
void matrice_def1();
void matrice_def2();
//void calcolo(int tabella[][100], int dim);
void calcolo(int G[100][100],int n, int startnode);

int main(){
	
	int i,j;
	int tabella[100][100]={INF};
	int pesi[100][100];
	int scelta, scelta1, nodi;
	int fine=0;

	do{
		printf("%c",angolo_sinistro_alto);
		for(i=0;i<47;i++){
			printf("%c",riga);
		}
		printf("%c",angolo_destro_alto);
		printf("\n");
		
		printf("%c 1) Inserimento grafo con 5 nodi predefinito\t%c\n",colonna,colonna);
		printf("%c\t\t\t\t\t\t%c\n",colonna,colonna);
		printf("%c 2) Inserimento grafo con 10 nodi predefinito\t%c\n",colonna,colonna);
		printf("%c\t\t\t\t\t\t%c\n",colonna,colonna);
		printf("%c 3) Inserimento grafo qualsiasi e calcolo\t%c\n",colonna,colonna);
		printf("%c\t\t\t\t\t\t%c\n",colonna,colonna);
		printf("%c 4) Uscita dal programma\t\t\t%c\n",colonna,colonna);
		printf("%c\t\t\t\t\t\t%c\n",colonna,colonna);
		
		printf("%c",angolo_sinistro_basso);
		for(i=0;i<47;i++){
			printf("%c",riga);
		}
		printf("%c",angolo_destro_basso);
		printf("\n");
		
		printf(": ");
		scanf("%d",&scelta);
		
		switch(scelta){
			
			case 1:	
				printf("1) Soluzione default \n2)dati inseriti dall'utente\n");	
				scanf("%d",&scelta1);
				switch(scelta1){
					case 1:	
						matrice_def1();
						break;
					case 2:
						inserimento(tabella, 5);				//chiamata alla funzione per il nodo predefinito 5x5
						break;
				}
				break;
					
			case 2:
				printf("1) Soluzione default \n2)dati inseriti dall'utente\n");		
				scanf("%d",&scelta1);
				switch(scelta1){
					case 1:	
						matrice_def2();
						break;
					case 2:
						inserimento(tabella, 10);				//chiamata alla funzione per il nodo predefinito 5x5
						break;
				}
				break;
			
			case 3:
				printf("1) Soluzione default \n2)dati inseriti dall'utente\n");		
				scanf("%d",&scelta1);
				switch(scelta1){
					case 1:	
						printf("ciao\n");
						break;
					case 2:
						printf("Quanti nodi vuoi inserire?\n");
						scanf("%d",&nodi);
						inserimento(tabella, nodi);				//chiamata alla funzione per il nodo predefinito 5x5
						break;
				}
				break;
			
			case 4:
				fine=1;
				break;
		}
	}while(fine==0);
}

void inserimento(int tabella[][100], int dim){
	int i, j, inizio, fine;
	int x,y;
	int costo, end=0, err=0;
	
//	for(i=0;i<dim;i++){															//inizializzazione matrice a infinito	
//		for(j=0;j<dim;j++){
//			tabella[i][j]=INF;
//		}
//	}
//
//	do{
//		do{
//			printf("\nInserisci il nodo inizio per costo\t");
//			scanf("%d",&i);
//			if(i>=dim || i<0)
//				printf("Errore!");
//		}while(i>=dim || i<0);
//		
//		do{
//			err=0;
//			printf("Inserisci il nodo arrivo per costo\t");
//			scanf("%d",&j);	
//			if(j==i)
//				err=1;
//			if(j>=dim || j<0 || err==1)
//				printf("Errore!\n");
//		}while(j>=dim || j<0 || err==1);
//		
//		do{
//			printf("Inserisci il costo\t");
//			scanf("%d",&costo);
//			if(costo<=0)
//				printf("Errore! Numero inferiore a 0\n");	
//		}while(costo<=0);
//		
//		tabella[i][j]=costo;
//		
//		printf("\nPremi 0 per continuare, -1 per uscire\t");
//		scanf("%d",&end);
//					
//	}while(end!=-1);
//	
//	for(i=0;i<dim;i++)
//	{															//stampa matrice
//		printf("\n");
//		for(j=0;j<dim;j++)
//		{
//			printf("\t%d",tabella[i][j]);
//		}
//	}
//	printf("\n");
//	do{
//			printf("\nInserisci il nodo inizio per calcolo\t");
//			scanf("%d",&inizio);
//			if(inizio>=dim || inizio<0)
//				printf("Errore!");
//	}while(inizio>=dim || inizio<0);
//	do{
//			err=0;
//			printf("Inserisci il nodo arrivo per costo\t");
//			scanf("%d",&fine);	
//			if(fine==inizio)
//				err=1;
//			if(fine>=dim || fine<0 || err==1)
//				printf("Errore!\n");
//	}while(fine>=dim || fine<0 || err==1);
//	
//	calcolo(tabella,fine,inizio);
}

void matrice_def1(){
	int i, j;
	int fine=4;
	int inizio=0;
	int tabella[100][100]={	{999,10,999,30,100},                     
				   	  		{999,999,50,999,999},                   
				  			{999,999,999,20,10},                    
				   			{999,999,999,999,60},                    
				   			{999,999,999,999,999}};
	
	for(i=0;i<5;i++)
	{															//stampa matrice
		printf("\n");
		for(j=0;j<5;j++)
		{
			printf("\t%d",tabella[i][j]);
		}
	}
	printf("\n");
	
	calcolo(tabella,fine,inizio);
	
}

void calcolo(int G[100][100],int n, int startnode){
	int cost[MAX][MAX],distance[MAX],pred[MAX];
	int visited[MAX],count,mindistance,nextnode,i,j;
	n++;
	//pred[] stores the predecessor of each node
	//count gives the number of nodes seen so far
	//create the cost matrix
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	if(G[i][j]==0)
		cost[i][j]=INF;
	else
		cost[i][j]=G[i][j];
	//initialize pred[],distance[] and visited[]
	for(i=0;i<n;i++)
	{
		distance[i]=cost[startnode][i];
		pred[i]=startnode;
		visited[i]=0;
	}
	distance[startnode]=0;
	visited[startnode]=1;
	count=1;
	while(count<n)
	{
		mindistance=INF;
		//nextnode gives the node at minimum distance
		for(i=0;i<n;i++)
			if(distance[i]<mindistance&&!visited[i])
			{
				mindistance=distance[i];
				nextnode=i;
			}
			//check if a better path exists through nextnode
				visited[nextnode]=1;
			for(i=0;i<n;i++)
				if(!visited[i])
					if(mindistance+cost[nextnode][i]<distance[i])
					{
						distance[i]=mindistance+cost[nextnode][i];
						pred[i]=nextnode;
					}
		count++;
	}
	
	//print the path and distance of each node
//	printf("\nDistance of node%d=%d",n-1,distance[n-1]);
//	printf("\nPath=%d",n-1);
//			j=n;
//			do
//			{
//			j=pred[j];
//			printf("<-%d",j);
//			}while(j!=startnode);
			
	for(i=0;i<n;i++){
		if(i!=startnode)
		{
			j=i;
		}	
	}
	
	printf("\nDistance of node%d=%d",i-1,distance[i-1]);
	printf("\nPath=%d",i-1);
	do
	{
		j=pred[j];
		printf("<-%d",j);
	}while(j!=startnode);
}

void matrice_def2(){
	
}
