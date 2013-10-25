/*

	Dada a matriz adjacência apresenta os valores : numero de arestas, cinturra,grau maximo e grau minimo.
	OBS: sem peso nas arestas

*/

#include <stdio.h>
#include <stdlib.h> 

#define MIN(a,b) (((a)<(b) && (a))?(a):(b))
#define MAX 100000
#define INF 9999
int grau[MAX];
int visited[MAX];
int fila[MAX];

int num_arestas(int **A, int n);
int grau_maximo(int **A, int n);
int grau_minimo(int **A, int n);
int cintura(int **A, int n);



#include <stdio.h>
#include <stdlib.h> 

#define MIN(a,b) (((a)<(b) && (a))?(a):(b))
#define MAX 100000
#define INF 9999 /*numero que será inserido no vetor de distancia*/
int grau[MAX]; /*graus encontrados na matriz*/
int visited[MAX];
int fila[MAX];



int num_arestas(int **A, int n);
int grau_maximo(int **A, int n);
int grau_minimo(int **A, int n);
int cintura(int **A, int n);
int BFS(int **A,int n,int i);


int main(void)
{

	printf("\t\tMatriz Adjacência Simétrica\t\n\n");

	int n = 0;
	int i,j;


	printf("Entre com o numero de vertices:\n");
	scanf("%d",&n);

	if (n <= 0)
	{
		printf("Grafo Invalido\n");
	}
	else
	{

		int **A = (int**) malloc (sizeof(int*)*(n));

		if (A == NULL)
		{
			printf("ERROR\n");
			exit(1);
		}
		
		for (i = 0; i < n; i++)
		{
			A[i] = (int*) malloc (sizeof(int)*(n));

			if (A[i] == NULL)
			{
				printf("ERROR\n");
				exit(1);
			}
			for (j = 0; j < n; j++)
			{
				A[i][j] = 0;	
			}
		}

		/*
			Preenchimento da matriz A
		*/
		for (i = 0; i < n-1; i++)
		{
			for (j = i+1; j < n; j++)
			{
				if ( i != j )
				{
					printf("%d chega em %d? (0/1) ", i,j);
					scanf("%d",&A[i][j]);
					A[j][i] = A[i][j]; /* faz espelhamento dos valores*/
						
				}
			}
		}
		
		/*
			Chamadas das funções
		*/
		
		printf("E(G) = %d \n",num_arestas(A,n));
		printf("delta(G) = %d \n",grau_maximo(A,n));
		printf("sigma(G) = %d \n",grau_minimo(A,n));
		int girth = cintura(A,n);

		if (girth >= 3)
		{
			printf("g(G) = %d \n\n",girth);
		}
		else
		{
			printf("g(G) = infinito\n\n");
		}
		
		/* 
			imprime matriz adjacência
		*/
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				printf("\t%d\t", A[i][j]);
				
			}
			printf("\n");
		}
	}

	return 0;
}

int num_arestas(int **A, int n) {

	int arestas = 0,i,j;

	/*
		percorre acima da diagonal principal para obter numero de arestas
	*/
	for (i = 0; i < n-1; i++)
	{
			for (j = i+1; j < n; j++)
			{
				arestas += A[i][j];
			}
	}

	return arestas;
}

int grau_maximo(int **A, int n) {

	if (A == NULL || n < 1)
	{
		return 0;
	}

	int grau_maximo = 0,i = 0,j;
	int max = 0;

	while( i < n)
	{
		for (j = i+1; j < n; j++)
		{
			if (A[i][j] == 1)
			{
				grau_maximo++;
			}	
		}
		grau[i] = grau_maximo;

		/*
			Verifica se o numero atual é maior que o anterior.
		*/

		if ( grau_maximo > max && (grau_maximo <= ((n*(n-1))/2)) && grau_maximo != 0 )
		{
			max = grau_maximo > max ? grau_maximo : max; /* teste se grau_maximo encontrado é maior que o valor atual de minimo*/
			
		}
		grau_maximo = 0;
		i++;
	}
	return max;
}

int grau_minimo(int **A, int n) {

	int *grau,k = 0,j = 0;
	int min = n+1;

	grau = (int*) malloc (sizeof(int)*n);

	if (n < 1 || grau == NULL || A == NULL)
	{
		return 0;
	}
	while (k < n)
	{	
		grau[k] = 0;
	
		for (j = 0 ; j < n; j++)
		{

			if (A[k][j] == 1)
			{
				grau[k] = grau[k] + A[k][j];
				
			}	

		}
		/*
			Verifica se atual é menor que o anterior.
		*/
		min = grau[k] < min && (grau[k] <= ((n*(n-1))/2)) && grau != 0 ? grau[k] : min; /* teste se grau encontrado é menor que o valor atual de minimo*/
		k ++;
	}

	return min;
}

/*

	Função percorre a matriz utilizando a função BSF() para obter a cintura , ou seja, o menor ciclo de um grafo,
	seguindo os conceitos de grafos simples.

*/

int cintura(int **A, int n) {

	/*
		condição garante mais chances de ter cintura o grafo
	*/
	if (n < 3 || A == NULL)
	{
		printf("ERROR OU INFINITO\n");
		return 0;
	}

	
	int origem,girth = n+1;

	for (origem = 0; origem < n; origem++)
	{

		int cintura_origem = BSF(A,n,origem); /* percorre por largura */

		/*
			Verifica se a cintura da origem é menor que a anterior, caso for substitui
		
		*/	
		if (girth > cintura_origem)
		{
			girth = cintura_origem;
		}
		
	}
	return girth;
}

/*
	Função que obtêm a cintura apartir de uma origem. 
	
*/

int BSF(int **A,int n, int origem) {

	int i,girth = n+1,*distancia;
	int ini, fim;

	distancia = (int*) malloc (sizeof(int)*n);

	if (distancia == NULL)
	{
		printf("Erro na alocação de memória\n");
		exit(1);
	}

	/*
		Preenche vetor de distancia com um numero 'infinito'
	*/
	for( i = 0; i < n; i++)
	{
		  	distancia[i] = INF;
	}

	distancia[origem] = 0;

	ini = fim = 0;

	fila[fim++] = origem; 

	while(ini != fim) 
	{
		int no = fila[ini++];

		for( i = 0; i < grau[no]; i++) 
		{
		    int viz = A[no][i];
		    
		    if(distancia[viz] == INF ) 
		    {
		    	
				fila[fim++] = viz;
				distancia[viz] = distancia[no] + 1;
		    }
		    else
		    {
		    	int temp = MIN(girth,distancia[no] + distancia[viz] +1);
		    	girth = temp >= 3 ? temp : girth;
		    	
		    }
		}
	}
	return girth;
}
