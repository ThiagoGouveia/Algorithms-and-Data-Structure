#include <stdio.h>
#include <stdlib.h>
#include<time.h>

void InsertionSort(int *vet, int tamanho)
{
	int aux, i, j;

	for(j = 1; j < tamanho; j++)
	{

		aux = vet[j];
		i = j - 1;

		while(i >= 0 && vet[i] > aux)
		{
			vet[i + 1] = vet[i];
			i--;
		}

		vet[i+1] = aux;
	}
}

void imprimeVetor(int *vet, int tamanho)
{
	int i = 0;
	while (i < tamanho)
	{
		printf("%d\t", vet[i]);
		i++;
	}
    	printf("\n");
}

int main(int argc, char const *argv[])
{

	int tamanho = 15;
	int *vet = (int*) calloc(tamanho, sizeof(int));

	//srand(time(NULL));

	for (int i=0; i < tamanho; i++)
    	{
         vet[i] = rand() % 10;
    	}




    imprimeVetor(vet, tamanho);

	InsertionSort(vet, tamanho);

	imprimeVetor(vet, tamanho);


	return 0;
}
