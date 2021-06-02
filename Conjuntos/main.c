//inclusão do cabeçalho conjunto
#include "conjunto.h"


int main(int argc, char const *argv[])
{	
	//declaração dos ponteiros e variáveis
	listaConjunto *L;
	L = NULL;
	char nome[100];
	char nome2[100];
	char enter[1];
	int valor, escolha = 0;

	//loop que possibilita o programa funcionar até o usuário escolher finalizar
	while(escolha != 14)
    {
    	//print do menu e armazenamento da escolha na variável escolha
        printf("1 - Cria conjunto \n2 - Insere no conjunto \n3 - Imprime conjunto \n4 - Esvazia conjunto \n5 - Verifica conjunto vazio \n6 - Uniao conjunto \n7 - Intersecao conjunto \n8 - Complemento relativo conjunto \n9 - Remove elemento do conjunto \n10 - Exclui conjunto \n11 - Verifica conjuntos iguais \n12 - Verifica elemento conjunto \n13 - Verifica se eh subconjunto \n14 - Sair\n\n");
        printf("Digite sua escolha: ");
        scanf("%d", &escolha);
        printf("\n");
        setbuf(stdin, NULL);
        switch (escolha)
        {	//insere no final
        	//pergunta ao usuario o nome do conjunto a ser criado e passa como parâmetro
            case 1:
            	printf("Digite o nome do conjunto: ");
				scanf("%[^\n]",nome);
    			scanf("%c",&enter);
                L = insereFinalListaConjunto(L, nome);
                break;

            //insere elemento no conjunto selecionado
            //pergunta ao usuario o nome do conjunto em que o elemento será inserido e armazena o elemento na variavel valor
            case 2:
            	printf("Digite o nome do conjunto: ");
				scanf("%[^\n]",nome);
    			scanf("%c",&enter);
    			printf("Digite o valor: ");
    			scanf("%d", &valor);
    			printf("\n");	
                L = insereElementoConjunto(L, valor, nome);
                break;

            //imprime o conjunto
            //pergunta ao usuario o nome do conjunto que será impresso e passo como parâmetro
            case 3:
                printf("Digite o nome do conjunto: ");
				scanf("%[^\n]",nome);
    			scanf("%c",&enter);
                 printf("conjunto %s: ",nome);
    			imprimeConjunto(L, nome);
                break;

            //esvazia o conjunto
            //pergunta ao usuario o nome do conjunto a ser esvaziado e passo como parâmetro
            case 4:
            	printf("Digite o nome do conjunto: ");
				scanf("%[^\n]",nome);
    			scanf("%c",&enter);
                L = esvaziaConjunto(L, nome);
                break;

            //conjunto vazio
            //pergunta ao usuario o nome do conjunto a ser verificado e passo como parâmetro
           	//se a função retornar true, printo conjunto vazio, senao, conjunto nao vazio
            case 5:
               	printf("Digite o nome do conjunto: ");
				scanf("%[^\n]",nome);
    			scanf("%c",&enter);
    			if(conjuntoVazio(L,nome)) printf("Conjunto vazio\n");
    			else printf("Conjunto nao vazio\n");
                break;

            //uniao de conjuntos
            //pergunta ao usuario o nome dos conjuntos a serem unidos e passo como parâmetro
            case 6:
                printf("Digite o nome do conjunto: ");
				scanf("%[^\n]",nome);
    			scanf("%c",&enter);
    			printf("Digite o nome do segundo conjunto: ");
				scanf("%[^\n]",nome2);
    			scanf("%c",&enter);
    			L = uniaoConjuntos(L, nome, nome2);
                break;

            //intersecao de conjuntos
            //pergunta ao usuario os nomes dos conjuntos para fazer intersecao e passo como parâmetro
            case 7:
                printf("Digite o nome do conjunto: ");
				scanf("%[^\n]",nome);
    			scanf("%c",&enter);
    			printf("Digite o nome do segundo conjunto: ");
				scanf("%[^\n]",nome2);
    			scanf("%c",&enter);
    			L = intersecaoConjuntos(L, nome, nome2);
                break;

            //subtração de conjuntos
            //pergunta ao usuario os nomes dos conjuntos para a serem subtraidos e passo como parâmetro
            case 8:
                printf("Digite o nome do conjunto: ");
				scanf("%[^\n]",nome);
    			scanf("%c",&enter);
    			printf("Digite o nome do segundo conjunto: ");
				scanf("%[^\n]",nome2);
    			scanf("%c",&enter);
    			L = complementoRelativoConjuntos(L, nome, nome2);
                break;

            //remove elemento
            //pergunta ao usuario o nome do conjunto em que o elemento será removido e o elemento em si, passo como parâmetro
            case 9:
            	printf("Digite o nome do conjunto: ");
				scanf("%[^\n]",nome);
    			scanf("%c",&enter);
    			printf("Digite o valor: ");
    			scanf("%d", &valor);
    			printf("\n");	
                L = removeElemento(L, nome, valor);
                break;

            //exclui conjunto
            ////pergunta ao usuario o nome do conjunto a ser excluido e passo como parâmetro
            case 10:
            	printf("Digite o nome do conjunto: ");
				scanf("%[^\n]",nome);
    			scanf("%c",&enter);
                L = excluiConjunto(L, nome);
                break;

            //pergunta ao usuario o nome dos conjuntos a serem verificados e os passo como parâmetro
          	//se a função retornar true, printo conjuntos iguais, senao, conjuntos diferentes
            case 11:
            	printf("Digite o nome do conjunto: ");
				scanf("%[^\n]",nome);
    			scanf("%c",&enter);
    			printf("Digite o nome do segundo conjunto: ");
				scanf("%[^\n]",nome2);
    			scanf("%c",&enter);
    			if(conjuntosIguais(L, nome, nome2)) printf("conjuntos iguais\n");
				else printf("conjuntos diferentes\n");
				break;

			//pergunta ao usuario o nome do conjunto e o elemento a ser verificado e passo como parâmetro
			//se a função retornar true printa elemento esta no conjunto, senao, elemento nao esta no conjunto.
			case 12:
				printf("Digite o nome do conjunto: ");
				scanf("%[^\n]",nome);
    			scanf("%c",&enter);
    			printf("Digite o valor: ");
    			scanf("%d", &valor);
    			printf("\n");
    			if(verificaElementoConjunto(L, nome,valor)) printf("elemento esta no conjunto\n");
				else printf("elemento nao esta no conjunto\n");
				break;

			//pergunta ao usuario o nome dos conjuntos a serem verificados e os passo como parâmetro
          	//se a função retornar true, printa conjunto contem conjunto, senao, conjunto nao contem conjunto.
			case 13:
				printf("Digite o nome do conjunto: ");
				scanf("%[^\n]",nome);
    			scanf("%c",&enter);
    			printf("Digite o nome do segundo conjunto: ");
				scanf("%[^\n]",nome2);
    			scanf("%c",&enter);
				if(conjuntoContemConjunto(L, nome, nome2)) printf("conjunto contem conjunto\n");
				else printf("conjunto nao contem conjunto\n");
				break;

        }

        printf("\n");

    }	

    return 0;
}
