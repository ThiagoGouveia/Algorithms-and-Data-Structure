#include <stdio.h>
#include <stdlib.h>
#include <locale.h>



//primeira fun��o preenche o vetor incializado na main
//os par�metros necess�rios s�o o pr�prio vetor e seu tamanho.
//pra isso � utilizado um la�o, onde para cada itera��o, uma mensagem � imprimida
//pedindo o valor a ser lido e armazenado no vetor.

void preenche_vetor(int *v, int n)
{
    int i = 0;                                                  // 1
	for(i = 0; i < n; i++)                                      //2n+1
	{
		int x = 0;                                              //n
		printf("entre com um valor para a posi��o %d \n", i );  //n
		scanf("%d",&x);                                         //n
		v[i] = x;                                               //n

	}                                                           //1+2n+1+4n = 6n+2
}                                                               //O(n)

//na segunda fun��o temos a impress�o na tela do vetor criado e preenchido
//para isso � novamente utilizado um la�o imprimindo cada valor armazenado no vetor

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

//A busca bin�ria por iterar��o s� receber� dois par�metros, o vetor e o seu tamanho
//O elemento a ser buscado ser� armazenado na vari�vel x
//A busca ser� feita com um la�o com condi��o a seguinte condi��o de parada:
//O la�o terminar� assim que o valor do in�cio ultrapassar o fim
//A primeira instru��o do la�o � setar o meio, pra isso ter� a soma do inicio e fim, e a
//divis�o por 2. Isso porque o in�cio ou fim v�o variar a cada itera��o
//A primeira condicional ser� a condi��o de parada, nela o algoritmo perguntar� se o elemento
//escolhido pelo usu�rio � igual ao elemento armazenado no vetor com indice meio. Se for, printar�
//a mensagem na tela, e sair� da fun��o utilizando o return.
//A segunda condicional testar� se o elemento x � menor que o armazenado no meio do vetor
//Caso for, a vari�vel fim receber� o meio-1 ou seja o primeiro elemento � esquerda do meio,
//desconciderando todos os elementos � direita do meio.
//A terceira condicional testar� se o elemento x � maior que o armazenado no meio do vetor
//Caso for, a vari�vel inicio receber� o meio+1 ou seja o primeiro elemento � direita do meio,
//desconciderando todos os elementos � esquerda do meio.
//Caso a primeira condicional n�o seja verdadeira em nenhuma das itera��es, ser� printado a mensagem
//"O elemento informado n�o existe no vetor."

void busca_binaria(int *v, int n)
{
	int x = 0;                                                  // 1
	int inicio = 0;                                             // 1
	int fim = n-1;                                              // 1
    int meio = 0;                                               // 1

    printf("Digite o elemento a ser buscado: \n");              // 1
    scanf("%d", &x);                                            // 1


    while(fim >= inicio)                                        //log(n) pois n/2^k -> n/2^k = 1(no final o array s� vai ter um elemento) -> n = 2^k -> log(n) = log(2^k)(multiplicando os dois lados por log)
    {                                                           //log(n) = k*log(2) -> como log(2) = 1 o resultado � k = log(n) onde k = numero de itera��es e n = tamanho do vetor, lembrado que o log � bin�ria
        meio = (inicio + fim)/2;                                //log(n)

        if(v[meio] == x)                                        //log(n)
        {
            printf("Elemento encontrado na posi��o %d\n",meio); // 1
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

    printf("O elemento informado n�o existe no vetor.\n");     // 1

}                                                              //1+1+1+1+1+1+3*log(n)+1+1+4*log(n)+1 = 7*log(n) + 9
                                                               //O(log(n))

//na main ser� perguntado o usu�rio o tamanho do vetor, armazenado na vari�vel n
//e o vetor ser� declarada na vari�vel v dinamicamente
//ap�s isso ser� chamadas as fun��es de preenchimento do vetor, impress�o do vetor e
//a ser� realizado a busca

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
