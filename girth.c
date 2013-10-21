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
int T[MAX];

int DFS(int i,int **A,int n);
int LCA(int x,int y);
int num_arestas(int **A, int n);
int grau_maximo(int **A, int n);
int grau_minimo(int **A, int n);
int cintura(int **A, int n);


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


		for(i = 0;i < n; i++){ 

	        visited[i] = 0;
		}

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

		for (i = 0; i < n-1; i++)
		{
			for (j = i+1; j < n; j++)
			{
				if ( i != j )
				{
					printf("%d chega em %d? (0/1) ", i,j);
					scanf("%d",&A[i][j]);

					A[j][i] = A[i][j];
						
				}
			}
		}
		
		/*
			Copia da matriz para manipular na função que calcula numero de arestas
		*/
		int **temp = (int**) malloc (sizeof(int*)*(n));

		for (i = 0; i < n; i++)
		{
			temp[i] = (int*) malloc (sizeof(int)*(n));

			if (temp[i] == NULL)
			{
				exit(1);
			}

			for (j = 0; j < n; j++)
			{
				temp[i][j] = A[i][j];
				
			}
		}
		printf("E(G) = %d \n",num_arestas(temp,n));
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
		
		
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				printf(" %d", A[i][j]);
				
			}
			printf("\n");
		}
	}

	return 0;
}

int num_arestas(int **A, int n) {

	int arestas = 0,i,j;

	for (i = 0; i < n-1; i++)
	{
			for (j = i+1; j < n; j++)
			{
				if (A[i][j] == 1 && A[j][i] == 1)
				{
					arestas = arestas + 1;
					A[j][i] = 0;
					A[j][i] = 0;
				}	
				else if (A[i][j] == 1)
				{
					arestas++;
				}
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
		if ( grau_maximo > max && (grau_maximo <= ((n*(n-1))/2)) && grau_maximo != 0 )
		{
			max = grau_maximo > max ? grau_maximo : max; /* teste se grau_maximo encontrado é maior que o valor atual de minimo*/
			//printf("%d\n",max );
		}
		grau_maximo = 0;
		i++;
	}
	return max;
}

int grau_minimo(int **A, int n) {

	int *grau,k = 0,j = 0;
	int min = 9999;

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
		min = grau[k] < min && (grau[k] <= ((n*(n-1))/2)) && grau != 0 ? grau[k] : min; /* teste se grau encontrado é menor que o valor atual de minimo*/
		k = k + 1;
	}
	return min;
}
int DFS(int v,int **A,int n)
{
   /* int i = 0;

    visited[v] = 1;

    for( ;i < n; i++) {

        if(!visited[A[v][i]])
        {
        	printf("%d   %d\n",v,i );
            DFS(i,A,n);
        }
    }
    return v;*/
}

int LCA(int x,int y) /* ultimo ancestral comun*/
{/*
        while(visited[x] != visited[y]) {

        	if(L[x] > L[y])
        	{
        		x = visited[x];
        	}
            else
            {
            	 y = visited[y];
            }
        }
                
        while( x != y)
        {
        	if(L[x] > L[y])
        	{
        		 x = T[x];
        	}
            else
            {
            	 y = T[y];
            }
                       
        } */return 0;            
}

int cintura(int **A, int n) {

	if (n < 3 || A == NULL)
	{
		printf("ERROR OU INFINITO\n");
		return 0;
	}

	int girth = 9999,orig,i,distancia[n];
	int ini, fim;

	for (orig = 0; orig < n; orig++)
	{

		for( i = 0; i < n; i++)
		{
		  	distancia[i] = INF;
		}

		distancia[orig] = 0;

		ini = fim = 0;

		fila[fim++] = orig;

		while(ini != fim) 
		{
			int no = fila[ini++];
			
			printf("grau:%d\n",grau[no]);

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
			    	int temp = MIN(girth,distancia[no] + distancia[viz] );
			    	girth = temp >= 3 ? temp : girth;
			    	printf("%d\n",girth );
			    }
			}
		}
		
	}
	printf("%d\n",girth );
	return girth;
}

