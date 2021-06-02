#include <stdio.h>
#include <stdlib.h>

//Declaração da estrutura que será enserida na lista
//Por conveniência eu defini o nome da estrutura como "no"
typedef struct no
{
	int valor;
	int grau;
	struct no *prox;
}no;

//Declaração da função que irá criar o nó
//Nessa função será recebido o valor de coeficiente e o grau desse monomio
//Declaro uma variavel tipo nó de nome novo e aloco o espaço na memória, caso exista espaço, e insiro na variavel novo
//o valor do coeficiente e o grau. Após isso retorno o novo nó.
no *criaNo (int valor, int grau)
{
	no *novo;
	novo = (no*) malloc(sizeof(no));
	if(novo == NULL)
	{
		printf ( "ERRO: problemas com a alocacao de memoria . \n " );
		exit(1);
	}

	novo->valor = valor;
	novo->grau = grau;
	novo->prox = NULL;
	return novo;
}

//Declaração da funcão que irá inserir os nós nas listas L1,L2 e a lista de saída
//Essa função receberá a lista e alocará um elemento de forma ordenada com os valores de coeficiente e expoente.
//Dada a importância e oo tamanho da lista, irei explicar bloco por bloco.

no *insereOrd (no *L, int valor, int grau)
{
    //Declaro uma variavel tipo nó de nome novo e aloco o espaço na memória
	no *novo = criaNo(valor, grau);
	no *aux = L, *pred = NULL;

    //Verifica se a lista é vazia caso for coloco o novo nó como primeiro elemento.
	if(L == NULL)L = novo;

	else
	{  //Se não, percorreremos a lista até encotrarmos o final e o grau do novo nó a ser inserido for menor que os graus da lista
		while (aux != NULL && grau < aux->grau )
		{
			pred = aux;
			aux = aux->prox;
		}

        //Essa condicional verifica se já existe um elemento com valor de expoente igual ao que eu quero inserir,
        //Se existir, só soma o valor de novo ao valor do nó que já está na lista e o código já pula para o fim
        if(aux!=NULL && aux->grau == grau) aux->valor = aux->valor + valor;
        else
        {   //Caso não, verifica se o elemento deve ser inserido no início da lista
            if(pred == NULL)
            {
                novo->prox = aux;
                L = novo;
            }
            else
            {//Se não eu insere no meio
                novo->prox = aux;
                pred->prox = novo;
            }

        }

	}
    //Retorna a lista L
	return L;
}

//Declaração da funcão que irá somar os nós das listas L1 e L2
//Para isso eu declaro um nó auxiliar que recebe o valor de L2, e um soma que receberá a L1
//Então, percorre toda a lista 2 que está armazenada no auxiliar inserindo os elementos na lista soma
//Para isso eu uso a lógica da função de inserção ordenada
no *somaListas (no *L, no *L2)
{
	no *aux = L2;
	no *soma = L;
	int valor, grau;

	while (aux != NULL)
	{
        soma = insereOrd(soma,aux->valor,aux->grau);
   		aux = aux->prox;

	}
	return soma;
}

//Declaração da funcão que irá subtrair os nós das listas L1 e L2
//Para isso eu uso exatamente a mesma lógica da função de soma, eu só trato o sinal da lista L2, multiplicando-os por -1
no *subListas (no *L, no *L2)
{
	no *aux = L2;
	no *sub = L;
	int valor, grau;

	while (aux != NULL)
	{
        sub = insereOrd(sub,(-1)*aux->valor,aux->grau);
   		aux = aux->prox;

	}
	return sub;
}

//Declaração da funcão que irá multiplicar as listas L1 e L2

no *multListas (no *L, no *L2)
{	
	//Para isso eu irei criar duas auxiliares que irão receber os valores de L1 e L2, respectivamente.
    no *aux = L;
    no *aux2 = L2;
    no *mult = NULL;
    int novoValor, novoGrau;

    //é criado um while que percorre todos os elementos da L1 e outro dentro que percorre L2.
    while(aux != NULL)
    {
        while(aux2 != NULL)
        {	
        	//Assim, é multiplicado todos os elementos de L2 pelo elemento atual de L1, e passo como parâmetro para a inserção
			//o novo expoente e o novo coeficiente
			//Após isso, seta aux2 para o iníco de L2 e repete o processo. Isso acontecerá até o final de L1
            novoValor = aux->valor * aux2->valor;
            novoGrau = aux->grau + aux2->grau;
            mult = insereOrd(mult, novoValor, novoGrau);
            aux2 = aux2->prox;
        }
        aux2 = L2;
        aux = aux->prox;
    }

    //Retorna a lista mult
    return mult;
}

//Declaração da função que imprime as listas





void imprimeLista(no *L)
{
	no *aux = L;

	//Nela é percorrido a lista inteira, e imprime. Para essa impressão é colocada algumas condições somente
		//por questões estéticas na hora da saída.
	while (aux != NULL)
	{		
		//É verificado se grau ou valor são iguais a zero, e printo somente o valor
        if(aux->grau == 0 || aux->valor == 0)printf("(%d)", aux->valor);
        //Caso não, verifica se o expoente é igual a 1 e só printo o valor do coeficiente multiplicado por X
        else if(aux->grau == 1)printf("(%d*X) ", aux->valor);
        //Senão, é impresso o coeficiente multiplicado por X elevado ao expoente
        else printf("(%d*X^%d) ", aux->valor,aux->grau);



		aux = aux->prox;
		//enquanto aux for diferente de NULL é impresso o caractere '+', só por questão de vizualização
        if(aux != NULL)printf(" + ");
	}
}

//Como a main está muito grande eu vou comentar cada bloco

int main(int argc, char const *argv[])
{
    //Crio a lista 1, 2 e resultado e aponto elas pra NULL
	no *lista1, *lista2, *resultado;
	lista1 = lista2 = NULL;
	int i = 1, valor , grau, escolha;

    //Pergunto ao usuário qual das opções ele quer
    printf("0 - INTERROMPE\n1 - SOMA\n2- SUBTRAI\n3-MULTIPLICA\nEscolha uma das opcoes acima:\n" );
    scanf("%d", &escolha);

    //Caso o usuário escolha uma opção inválida eu dou a possibilidade dele escolher uma opção válida
    while(0 > escolha > 3)
    {
        printf("Escolha invalida, digite novamente\n");
        printf("0 - INTERROMPE\n1 - SOMA\n2- SUBTRAI\n3-MULTIPLICA\nEscolha uma das opcoes acima:\n" );
        scanf("%d", &escolha);
    }

    //Se ele tiver escolhido por parar o programa, ou seja, a opção "0", eu simplesmente saio da função
    if(escolha == 0)return 0;

    //Se o programa chegou até aqui, eu faço um laço que irá perguntar ao usuário os valores de coeficiente e expoente
    // Eu chamo a função de inserção ordenada e dou a oportunidade de ele continuar inserindo mais monomios
   	while(i != 0){
        printf("Digite um valor inteiro para o coeficiente(primeira expressao): ");
        scanf("%d", &valor);
        printf("\n");

        printf("Digite um valor inteiro para o expoente(primeira expressao): ");
        scanf("%d", &grau);
        printf("\n");

        lista1 = insereOrd(lista1, valor, grau);

        printf("Deseja adicionar mais um monomio a primeira expressao ? (sim = 1 nao = 0)");
        scanf("%d", &i);
        printf("\n");
   	}

    //como i = 0 pois o usuário saiu daquele laço eu torno a setar um valor diferente de 0 para que o usuário possa
    //preencher a lista 2
   	i = 1;
   	while(i != 0){
        printf("Digite um valor inteiro para o coeficiente(segunda expressao): ");
        scanf("%d", &valor);
        printf("\n");

        printf("Digite um valor inteiro para o expoente(segunda expressao): ");
        scanf("%d", &grau);
        printf("\n");

        lista2 = insereOrd(lista2, valor, grau);

        printf("Deseja adicionar mais um monomio a segunda expressao ? (sim = 1 nao = 0)");
        scanf("%d", &i);
        printf("\n");
   	}

    //Após isso eu simplesmente imprimo as duas listas
    printf("Primeiro polinomio simplificado: ");
    imprimeLista(lista1);
	printf("\n");

    printf("Segundo polinomio simplificado: ");
	imprimeLista(lista2);
    printf("\n");

    // Aqui eu vou fazer um switch case que recebe a escolha do usuário que foi feita no início do programa, e
    // a depender da escolha do usuário, chamo a função de soma ou subtração ou multiplicação
	switch (escolha)
    {
        case 1:
        resultado = somaListas(lista1,lista2);
        break;

        case 2:
        resultado = subListas(lista1,lista2);
        break;

        case 3:
        resultado = multListas(lista1,lista2);
        break;
    }

    //impressão do resultado final
    printf("Resultado final: ");
	imprimeLista(resultado);
    printf("\n\n");

	return 0;
}
