//Trabalho realizado por:
//Thiago Rodrigues Gouveia da Silva
//Victor Cezari Nascimento 

//inclusão do cabeçalho ABB genérica
#include "RBTree.h"


//main
int main(int argc, char const *argv[])
{
	noRB *raiz, *aux;
	
	aux = NULL;
    raiz = NULL;
    int ano, id = 0;
    int escolha = 0;
    char autor[200], titulo[200], revista[200], DOI[20], palavraChave[200], enter;
    struct artigo a;

    //inicializa a variavel global externo que será o nó folha da árvore
    externo = (noRB*) calloc(1, sizeof(noRB));
    if(externo == NULL)
    {
    	printf("ERRO: nao foi possivel alocar no\n");
    	return 0;
    }

   //atribui o externo à raiz
   raiz = externo;

    do//enquanto
    {	
    	//imprime menu
        printf("\n0 - Sair\n1 - Insere elemento\n2 - Procura elemento\n3 - Deleta elemento\n4 - Imprime Arvore(pre ordem)\n5 - Imprime Arvore(em ordem)\n6 - Imprime Arvore(pos ordem)\n");
        
        //pergunta a escolha ao usuario
        printf("Sua escolha: ");
        scanf("%d", &escolha);
        printf("\n");
        setbuf(stdin, NULL);
        
        switch(escolha)
        {
            case 1://caso de inserção
           
                printf("O id: ");
                scanf("%d",&a.id);
                scanf("%c",&enter);

                printf("O ano: ");
                scanf("%d",&a.ano);
                scanf("%c",&enter);

                printf("O autor: ");
                scanf("%[^\n]",a.autor);
                scanf("%c",&enter);

                printf("O titulo: ");
                scanf("%[^\n]",a.titulo);
                scanf("%c",&enter);

                printf("A revista: ");
                scanf("%[^\n]",a.revista);
                scanf("%c",&enter);

                printf("O DOI: ");
                scanf("%[^\n]",a.DOI);
                scanf("%c",&enter);

                printf("A palavra chave: ");
                scanf("%[^\n]",a.palavraChave);
                scanf("%c",&enter);
			
                raiz = insereRB(raiz, a);
     
                break;

            case 2://caso de busca

                printf("digite a ID a ser procurada: ");
                scanf("%d", &id);
                printf("\n");
                aux = buscaRB(raiz, id);

                if(aux)
                {
                	printf("O ID: %d\n",aux->info.id);
                	printf("O ano: %d\n", aux->info.ano);
                	printf("O autor: %s\n", aux->info.autor);
                	printf("O titulo: %s\n", aux->info.titulo);
                	printf("A revista: %s\n", aux->info.revista);
                	printf("O DOI: %s\n", aux->info.DOI);
                	printf("A palavra chave: %s\n", aux->info.palavraChave);
                }
               
                break;

            case 3://caso de remoção
            	printf("digite a ID a ser deletada: ");
                scanf("%d", &id);
                printf("\n");
                aux = buscaRB(raiz, id);  
                //verifica se a chave está contida na árvore, e se tiver chama a função de remoção, passando a chave
                if(aux != externo)raiz = removeRB(raiz, aux);     
                break;

            case 4://imprime a árvore em pre ordem
                preOrdem(raiz, 0);
                printf("\n");
                break;

            case 5://imprime a árvore em ordem
                emOrdem(raiz, 0);
                printf("\n");
                break;

            case 6://imprime a árvore em pós ordem
                posOrdem(raiz, 0);
                printf("\n");
                break;

            case 0://quando escolha for zero, sai do laço, mas antes deleta a arvore e libera o espaço de memória de aux
            	deletaRB(raiz);
                free(aux);
                break;
        }

    }while(escolha != 0);



	return 0;
}
