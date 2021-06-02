#include <stdio.h>
#include <stdlib.h>

//Definição da estrutura
//O que vale comentar é o ponteiro vet, que irá receber o vetor
//Nele será alocado o espaço informado pelo usuário
typedef struct listaC
{
    int *vet, tamanho, inicio, fim, ocupado;

}listaC;


//Função para criação da lista, nela o usuário definirá um tamanho 

listaC *criaLista(listaC *L)
{

	int tamanho;

	printf("Insira o tamanho para a lista: ");
    scanf("%d", &tamanho);
   	printf("\n");

   	//tratamento para que o usuário sempre digite um número maior que 0
	while(0 >= tamanho)
	{
		printf("Tamanho invalido\n");
		printf("Insira o tamanho para a lista: ");
    	scanf("%d", &tamanho);
   		printf("\n");

	}

	//Alocação do ponteiro tipo lista circular e o tamanho do vetor
    L = (listaC*) malloc(sizeof(listaC));
    L->vet = (int*) calloc(tamanho, sizeof(int));

    //tratamento para caso a alocação falhe
    if(L == NULL)
    {
        printf ( "ERRO: problemas com a alocacao de memoria . \n " );
        exit(1);
    }

    //inicialização das variáveis contidas na estrutura
    L->fim = 0;
    L->inicio = 0;
    L->ocupado = 0;
    L->tamanho = tamanho;

    for(int i = 0; i < tamanho; i++)L->vet[i] = 0;


    return L;

}

// função que insere no inicio
listaC *insereInicio(listaC *L)
{
	//primeiro eu vejo se a lista está completamente ocupada, informo ao usuario e retorno pra main
    if(L->tamanho == L->ocupado)
    {
        printf("Lista Cheia\n\n");
        return L;
    }

    //Senão eu peço para o usuário digitar o valor do elemento a ser inserido e armazeno em uma variável
    int elemento = 0;
    printf("Digite o elemento a ser armazenado: ")/
    scanf("%d", &elemento);
    printf("\n");

    //Se a lista não tiver nenhum elemento eu simplesmente incremento ocupado e insiro na primeira posição
    if(L->ocupado == 0)
    {
        L->ocupado++;
        L->vet[0] = elemento;
    }

    //caso nao eu verifico se inicio é igual a zero e a lista está completamente ocupada
    //incremento ocupado, inicio vai receber o fim da lista e o elemento será inserido no novo fim.
    else if(L->inicio == 0 && L->ocupado > 0)
    {
        L->ocupado++;
        L->inicio = L->tamanho - 1;
        L->vet[L->inicio] = elemento;

    }

    //senao, incremento ocupado, inicio recebe a posição anterior e insiro no novo inicio
    else
    {
        L->ocupado++;
        L->inicio--;
        L->vet[L->inicio] = elemento;
    }
    return L;
}



listaC *insereFim(listaC *L)
{	
	//primeiro eu vejo se a lista está completamente ocupada, informo ao usuario e retorno pra main
    if(L->tamanho == L->ocupado)
    {
        printf("Lista Cheia\n\n");
        return L;
    }

    //Senão eu peço para o usuário digitar o valor do elemento a ser inserido e armazeno em uma variável
    int elemento = 0;
    printf("Digite o elemento a ser armazenado: ")/
    scanf("%d", &elemento);
    printf("\n");


    //Se a lista não tiver nenhum elemento eu simplesmente incremento ocupado e insiro na primeira posição
    if(L->ocupado == 0)
    {
        L->ocupado++;
        L->vet[0] = elemento;
    }

    //caso não eu verifico se o fim chegou ao final e a lista ainda tem espaços vazios
    //incremento ocupado, coloco o fim na primeira posição e insiro no novo fim
    else if(L->fim == (L->tamanho - 1) && L->ocupado < L->tamanho)
    {
        L->ocupado++;
        L->fim = 0;
        L->vet[L->fim] = elemento;
    }

    //senao, incremento ocupado, incremento o fim e insiro no novo fim.
    else
    {
        L->ocupado++;
        L->fim++;
        L->vet[L->fim] = elemento;
    }

    return L;

}

//remove no inicio
listaC *removeInicio(listaC *L)
{	
	//se a lista tiver vazia, informo o usuário e volto para a main
    if(L->ocupado == 0)
    {
        printf("Lista Vazia\n");
        return L;
    }

    //caso nao, e inicio estiver como ultima posição 
    //inicio vai receber a primeira posição e ocupado vai decrementar
    else if(L->inicio == (L->tamanho - 1))
    {
        L->vet[L->inicio] = 0;
        L->inicio = 0;
        L->ocupado--;
    }

    //senao, inicio vai receber a próxima posição e decremento ocupado
    //vale salienar que eu estou zerando o valor onde estou removendo 
    else
    {
        L->vet[L->inicio] = 0;
        L->inicio++;
        L->ocupado--;
    }

    return L;

}

//remove no inicio
listaC *removeFim(listaC *L)
{
	//se a lista tiver vazia, informo o usuário e volto para a main
    if(L->ocupado == 0)
    {
        printf("Lista Vazia\n");
        return L;
    }

    //caso nao, e fim estiver como primeira posição,
    //o fim vai para o ultima posição da lista e decremento ocupado  
    else if(L->fim == 0)
    {
        L->vet[L->fim] = 0;
        L->fim = L->tamanho - 1;
        L->ocupado--;
    }

    //senao, decremento fim e ocupado
    else
    {
        L->vet[L->fim] = 0;
        L->fim--;
        L->ocupado--;
    }

    return L;
}

//imprime a lista 
void imprimeLista(listaC *L)
{	
	//se a lista tiver vazia, informo o usuário e volto para a main
    if(L->ocupado == 0)
    {
        printf("Lista Vazia\n");
        return 0;
    }

    //Se inicio for maior que fim, printo todos elementos de inicio até o fim 
    //e depois printo todos os elementos do começo até o fim
    else if(L->inicio > L->fim)
    {
        printf("Sua lista:  ");
        for(int i = L->inicio; i < L->tamanho; i++)printf("%d\t", L->vet[i]);

        for(int i = 0; i <= L->fim; i++)printf("%d\t", L->vet[i]);
    }
	
	//senao, printo todos  os elementos de inicio até o fim 
    else
    {
        printf("Sua lista:  ");
        for(int i = L->inicio; i <= L->fim; i++)printf("%d\t", L->vet[i]);
    }

    printf("\n\n");

}

//somatorio da lista
//eu uso a mesma logica da impressão, porém somo os resultados em uma variavel 

void somaLista(listaC *L)
{
    int soma = 0;

    if(L->ocupado == 0)
    {
        printf("Lista Vazia\n");
        return 0;
    }

    else if(L->inicio > L->fim)
    {

        for(int i = L->inicio; i < L->tamanho; i++)soma+=L->vet[i];

        for(int i = 0; i <= L->fim; i++)soma+=L->vet[i];
    }

    else
    {

        for(int i = L->inicio; i <= L->fim; i++)soma += L->vet[i];

    }



    printf("Seu somatorio: %d\n\n",soma);

}

//main
int main(int argc, char const *argv[])
{	
	//declaração das variaveis
	listaC *L = NULL;
	int escolha = 0;

	//criação da lista
    L = criaLista(L);

    //loop que só irá ser parado quando o usuário informar
   	while(escolha != 7)
   	{	
   		//todas as escolhas posíveis do usuário
   		printf("1 - Insere inicio\n2 - Insere fim\n3 - Remove incio\n4 - Remove fim\n5 - Imprime somatorio\n6 - Imprime lista\n7 - Finaliza programa\n\n");
   		printf("Sua escolha: ");
   		scanf("%d", &escolha);
   		printf("\n");

   		//switch case que executa a função de acordo com a escolha do usuário
   		switch (escolha)
    	{
        	case 1:
         	L = insereInicio(L);
        	break;

        	case 2:
        	L = insereFim(L);
        	break;

        	case 3:
        	removeInicio(L);
        	break;

        	case 4:
            removeFim(L);
            break;

            case 5:
            somaLista(L);
            break;

            case 6:
            imprimeLista(L);
            break;
    }


   	}

	return 0;
}
