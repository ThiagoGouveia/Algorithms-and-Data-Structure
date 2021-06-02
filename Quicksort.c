#include <stdio.h>
#include <stdlib.h>
#include<time.h>

void Quicksort(int *vet, int esq, int dir)
{

	imprimeVetor(vet, 10);

	int pivo;

	if(esq < dir)
	{
		pivo = Particao(vet, esq, dir);
		Quicksort(vet, esq, pivo - 1);
		Quicksort(vet, pivo + 1, dir);
	}
}


int Particao(int *vet, int esq, int dir)
{

	int pivo, i , j, temp;

	i = esq-1;
	pivo = vet[dir];

	for(j = esq; j <= dir - 1; j++)
	{

		if(vet[j] <= pivo)
		{
			i++;

			temp = vet[i];
			vet[i] = vet[j];
			vet[j] = temp;

		}
	}

	temp = vet[i+1];

	vet[i+1] = vet[dir];
	vet[dir] = temp;

	return i + 1;
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

	int tamanho = 10;
	int *vet = (int*) calloc(tamanho, sizeof(int));

	//srand(time(NULL));

	for (int i=0; i < tamanho; i++)
    {
         vet[i] = rand() % 10;
    }


    imprimeVetor(vet, tamanho);

	Quicksort(vet, 0, tamanho - 1);

	imprimeVetor(vet, tamanho);


	return 0;
}
