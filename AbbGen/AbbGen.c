//inclusão do cabeçalho ABB genérica
#include "AbbGen.h"



//Criacao do no ABB
noABB* criaNo(void *info)
{

    noABB *novo = (noABB*) calloc(1, sizeof(noABB));

    if(novo == NULL)
    {
    	printf("ERRO: nao foi possivel alocar no\n");
    	return 0;
    }

    novo->info = info;

    return novo;

}


//insere no na arvore
noABB* insereABB(noABB* raiz, void *info, int (*compara) (void*, void*))
{

    noABB *novo = criaNo(info);
    noABB *aux = raiz;
    noABB *ant = NULL;

    //checa se a arvore é vazia
    if(raiz == NULL)
        raiz = novo;

    else//senao
    {
        //percorre a lista até encontrar o nó folha ou um no já existente
        while(aux != NULL)
        {
            if(compara(novo->info, aux->info) == 0)
            {
                printf("Elemento ja esta na arvore\n");
                return raiz;
            }

            else if(compara(novo->info, aux->info) == 1)
            {

                ant = aux;
                aux = aux->dir;
            }

            else
            {
                ant = aux;
                aux = aux->esq;
            }
        }

        if(compara(novo->info, ant->info) == 1) ant->dir = novo;
        else ant->esq = novo;
    }
    return raiz;
}


//Deleta árvore
void deletaABB(noABB* raiz)
{
    if(raiz == NULL)return raiz;

    deletaABB(raiz->esq);
    deletaABB(raiz->dir);


    free(raiz);

}


//busca elemento
void buscaABB(noABB* raiz, void *info, int (*compara) (void*, void*), void (*imprime) (void*))
{
    noABB *aux = raiz;
    noABB *aux2 = criaNo(info);//no criado para armazenar a informação genérica que o usuário irá definir

    //checa se a arvore é vazia
    if(raiz == NULL)
    {
        free(aux2);
        return 0;
    }

    else
    {   //percorre a lista até encontrar o fim ou um no procurado
        //chama a função para imprimir
        while(aux != NULL)
        {
            if(compara(aux2->info, aux->info) == 0)
            {
                printf("Elemento encontrado\n");
                imprime(aux->info);
                free(aux2);
                return 1;
            }

             else if(compara(aux2->info, aux->info) == 1)
            {
                aux = aux->dir;
            }

            else
            {
                aux = aux->esq;
            }
        }

      if(aux == NULL)
      {
        printf("Elemento nao encontrado\n");
        free(aux2);
        return 0;
      }
    }
}



//deleta um determinado no da arvore
noABB* deletaNoABB(noABB* raiz, void *info, int (*compara) (void*, void*))
{
    noABB *aux = raiz;
    noABB *aux2 = criaNo(info);//no criado para armazenar a informação genérica que o usuário irá definir
    noABB *ant = NULL;
    noABB *suc = NULL;

    //arvore vazia
    if(raiz == NULL)return raiz;


    else
    {
        //percorre até achar o id
        ant = aux;
        while(aux != NULL && compara(aux2->info, aux->info) != 0)
        {

            if(compara(aux2->info, aux->info) == 1)
            {
                ant = aux;
                aux = aux->dir;
            }

            else
            {
                ant = aux;
                aux = aux->esq;
            }
        }

        //se nao achar o id nao existe na arvore
        if(aux == NULL)
        {
            printf("Elemento nao encontrado\n");
            return raiz;
        }


        else
        {
            //senao
            //trata o caso do no excluido sem nenhuma sub arvore
            if(aux->esq == NULL && aux->dir == NULL)
            {

                if(compara(ant->info, aux->info) == 1)
                {
                    ant->esq = NULL;
                    free(aux);
                }

                else if(compara(ant->info, aux->info) == -1)
                {
                    ant->dir = NULL;
                    free(aux);
                }

                else
                {
                    raiz = NULL;
                    free(aux);
                }
            }

            //trata o caso do no ter uma subarvore à esquerda
            else if(aux->esq == NULL && aux->dir != NULL)
            {
                if(aux == ant)
                {
                    aux = aux->dir;
                    ant->info = aux->info;

                    ant->dir = aux;
                    free(aux);
                }

                else if(compara(ant->info, aux->info) == 1)
                {
                    ant->esq = aux->dir;
                    free(aux);
                }

                else if(compara(ant->info, aux->info) == -1)
                {
                    ant->dir = aux->dir;
                    free(aux);
                }
            }

            //trata o caso do no ter uma subarvore à esquerda
            else if(aux->esq != NULL && aux->dir == NULL)
            {
                if(aux == ant)
                {
                    aux = aux->esq;
                    ant->info = aux->info;

                    ant->esq = aux;
                    free(aux);
                }

                else if(compara(ant->info, aux->info) == 1)
                {
                    ant->esq = aux->esq;
                    free(aux);
                }

                else if(compara(ant->info, aux->info) == -1)
                {
                    ant->dir = aux->esq;
                    free(aux);
                }
            }

            //trata o caso do no ter duas subarvores
            else if(aux->esq != NULL && aux->dir != NULL)
            {
                suc = aux->dir;
                ant = suc;

                //acha o sucessor
                while(suc->esq != NULL)
                {
                    suc = suc->esq;
                }

                noABB *temp = criaNo(aux->info);

                aux->info = suc->info;
                suc->info = temp->info;

                //se sucessor for um no folha simplesmente aponta aux->dir pra NULL
                if(suc->esq == NULL && suc->dir == NULL)
                {
                    aux->dir = NULL;
                }

                //senao chama funcao de deletar passando o info do sucessor
                else ant = deletaNoABB(ant, suc->info, compara);


            }
        }
    }


    return raiz;
}





//Percuro preOrdem
void preOrdem(noABB* raiz, int nivel, void (*imprimeChave) (void*))
{
    if(raiz != NULL)
    {
        printf("\t");
        imprimeChave(raiz->info);
        preOrdem(raiz->esq, nivel+1, imprimeChave);
        preOrdem(raiz->dir, nivel+1, imprimeChave);
    }

    printf("\n");
}

//Percuro em ordem
void emOrdem(noABB* raiz, int nivel, void (*imprimeChave) (void*))
{
    if (raiz != NULL) {
        emOrdem(raiz->esq, nivel+1, imprimeChave);
        printf("\t");
        imprimeChave(raiz->info);
        emOrdem(raiz->dir, nivel+1, imprimeChave);
    }
    printf("\n");
}

//Percuro pós ordem
void posOrdem(noABB* raiz, int nivel, void (*imprimeChave) (void*))
{
    if (raiz != NULL) {

        posOrdem(raiz->esq, nivel+1, imprimeChave);
        posOrdem(raiz->dir, nivel+1, imprimeChave);
        printf("\t");
        imprimeChave(raiz->info);
    }
    printf("\n");
}



