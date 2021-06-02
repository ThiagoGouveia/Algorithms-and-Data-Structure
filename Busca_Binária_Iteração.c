#include <stdio.h>
#include <stdlib.h>
#include <locale.h>



//primeira função preenche o vetor incializado na main
//os parâmetros necessários são o próprio vetor e seu tamanho.
//pra isso é utilizado um laço, onde para cada iteração, uma mensagem é imprimida
//pedindo o valor a ser lido e armazenado no vetor.

void preenche_vetor(int *v, int n)
{
    int i = 0;                                                  // 1
	for(i = 0; i < n; i++)                                      //2n+1
	{
		int x = 0;                                              //n
		printf("entre com um valor para a posição %d \n", i );  //n
		scanf("%d",&x);                                         //n
		v[i] = x;                                               //n

	}                                                           //1+2n+1+4n = 6n+2
}                                                               //O(n)

//na segunda função temos a impressão na tela do vetor criado e preenchido
//para isso é novamente utilizado um laço imprimindo cada valor armazenado no vetor

void imprime_vetor(int *v,int n)
{
    int i = 0;                                                  // 1
    printf("\nseu vetor: ");                                    // 1
	for(i = 0; i < n; i++)                                      // 2n+1
	{
		printf("|%d|", v[i] );                                  // n
	}
	printf("\n");                                               //1
}                                                               //1+1+2n+1+n+1 = 3n+4
                                                                //O(n)

//A busca binária por iterarção só receberá dois parâmetros, o vetor e o seu tamanho
//O elemento a ser buscado será armazenado na variável x
//A busca será feita com um laço com condição a seguinte condição de parada:
//O laço terminará assim que o valor do início ultrapassar o fim
//A primeira instrução do laço é setar o meio, pra isso terá a soma do inicio e fim, e a
//divisão por 2. Isso porque o início ou fim vão variar a cada iteração
//A primeira condicional será a condição de parada, nela o algoritmo perguntará se o elemento
//escolhido pelo usuário é igual ao elemento armazenado no vetor com indice meio. Se for, printará
//a mensagem na tela, e sairá da função utilizando o return.
//A segunda condicional testará se o elemento x é menor que o armazenado no meio do vetor
//Caso for, a variável fim receberá o meio-1 ou seja o primeiro elemento à esquerda do meio,
//desconciderando todos os elementos à direita do meio.
//A terceira condicional testará se o elemento x é maior que o armazenado no meio do vetor
//Caso for, a variável inicio receberá o meio+1 ou seja o primeiro elemento à direita do meio,
//desconciderando todos os elementos à esquerda do meio.
//Caso a primeira condicional não seja verdadeira em nenhuma das iterações, será printado a mensagem
//"O elemento informado não existe no vetor."

void busca_binaria(int *v, int n)
{
	int x = 0;                                                  // 1
	int inicio = 0;                                             // 1
	int fim = n-1;                                              // 1
    int meio = 0;                                               // 1

    printf("Digite o elemento a ser buscado: \n");              // 1
    scanf("%d", &x);                                            // 1


    while(fim >= inicio)                                        //log(n) pois n/2^k -> n/2^k = 1(no final o array só vai ter um elemento) -> n = 2^k -> log(n) = log(2^k)(multiplicando os dois lados por log)
    {                                                           //log(n) = k*log(2) -> como log(2) = 1 o resultado é k = log(n) onde k = numero de iterações e n = tamanho do vetor, lembrado que o log é binária
        meio = (inicio + fim)/2;                                //log(n)

        if(v[meio] == x)                                        //log(n)
        {
            printf("Elemento encontrado na posição %d\n",meio); // 1
            return 0;                                           // 1
        }

        else if(v[meio] > x)                                    //log(n)
        {
            fim = meio - 1;                                     //log(n)

        }

        else if(v[meio] < x)                                    //log(n)
        {
            inicio = meio + 1;                                  //log(n)

        }

    }

    printf("O elemento informado não existe no vetor.\n");     // 1

}                                                              //1+1+1+1+1+1+3*log(n)+1+1+4*log(n)+1 = 7*log(n) + 9
                                                               //O(log(n))

//na main será perguntado o usuário o tamanho do vetor, armazenado na variável n
//e o vetor será declarada na variável v dinamicamente
//após isso será chamadas as funções de preenchimento do vetor, impressão do vetor e
//a será realizado a busca

int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "Portuguese");                           // 1

	int n, i;                                                  // 1
	int *v = NULL;                                             // 1
	printf("Informe o tamanho do vetor: ");                    // 1
	scanf("%d",&n);                                            // 1

	v = (int*) calloc(n ,sizeof(int));                         // 1

	preenche_vetor(v, n);                                      // 1
    imprime_vetor(v,n);                                        // 1
    busca_binaria(v, n);                                       // 1



	return 0;                                                  // 1

                                                               // 9
                                                               //O(1)
}


//preenche_vetor = 6n+2
//imprime_vetor = 3n+4
//busca_binaria = 7*log(n) + 9
//main = 10
//soma = 6n+2 + 3n+4 + 7*log(n) + 9 + 10 = 7*log(n) + 9n + 25
//Ordem = O(log(n))
