#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//primeira função preenche o vetor incializado na main
//os parâmetros necessários são o próprio vetor e seu tamanho.
void preenche_vetor(int *v, int n)
{
    int i = 0;
    //pra isso é utilizado um laço, onde para cada iteração, uma mensagem é imprimida
	//pedindo o valor a ser lido e armazenado no vetor.
	for(i = 0; i < n; i++)
	{
		int x = 0;
		printf("entre com um valor para a posição %d \n", i );
		scanf("%d",&x);
		v[i] = x;

	}
}

//na segunda função temos a impressão na tela do vetor criado e preenchido
//para isso é novamente utilizado um laço imprimindo cada valor armazenado no vetor
void imprime_vetor(int *v,int n)
{
    int i = 0;
    printf("\nseu vetor: ");
	for(i = 0; i < n; i++)
	{
		printf("|%d|", v[i] );
	}
	printf("\n");
}

// a primeira função busca um elemento escolhido pelo usuário dentro do vetor.
// Para isso recebe como parâmetro o proprio vetor, o tamanho do vetor, o elemento a ser buscado, o inicio, meio e fim.


void busca_binaria_recursiva(int *v, int n, int x, int inicio, int meio, int fim)
{	
	//A primeira condicional é para verificar se o elemento está presente no meio do vetor,caso sim,
	//printará a posição do elemento, e finalizará a função.
    if(v[meio] == x)
    {   printf("Elemento encontrado na posição %d\n", meio);
        return 0;
    }

    //Se a condicional não for verdadeira, o algoritmo passará para a segunda condicional
	// essa verificará se o posição inicio não é maior que o fim
	//ou seja, o vetor já foi totalmente verificado, sendo o caso retornará então a mensagem
	//"O elemento informado não existe no vetor.", e finalizará a função.
    else if(inicio > fim)
    {
        printf("O elemento informado não existe no vetor.\n");
        return 0;
    }

    //a terceira condicional verificara se o meio do vetor é maior que o elemento procurado
	//caso for, chamará novamente a função, passando como parametro a nova posição de fim
	//fazendo assim um 'slicing' à esquerda, desconciderando todos os elementos à direita do meio.
    else if(v[meio] > x)
    {
        return busca_binaria_recursiva(v, n, x, inicio, (inicio + fim)/2, meio - 1);
    }

    //a quarta condicional verificara se o meio do vetor é menor que o elemento procurado
	//caso for, chamará novamente a função, passando como parametro a nova posição de inicio
	//fazendo assim um 'slicing' à direita, desconciderando todos os elementos à esquerda do meio.
    else if(v[meio] < x)
    {
        return busca_binaria_recursiva(v, n, x, meio + 1, (inicio + fim)/2, fim);
    }

}






int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "Portuguese");
    //Na main serão declarados o tamanho(n), o ponteiro(v)
	int n, i;
	int *v = NULL;

	//Em seguida perguntará o tamanho do vetor ao usuário e  alocará a memória para o vetor
	printf("Informe o tamanho do vetor: ");
	scanf("%d",&n);

	v = (int*) calloc(n ,sizeof(int));

	//Assim então, chamará a função de preenchimento e logo após imprimirá o vetor na tela.
	preenche_vetor(v, n);
    imprime_vetor(v,n);


	//Feito isso, será perguntado ao usuário qual elemento ele deseja que seja buscado.
    int x = 0;
    printf("Digite o elemento a ser buscado: ");
    scanf("%d", &x);

    //Chamará então a função de busca
    busca_binaria_recursiva(v, n, x, 0, (n-1)/2, (n-1));



	return 0;
}
