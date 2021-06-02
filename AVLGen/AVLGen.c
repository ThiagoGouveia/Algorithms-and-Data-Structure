//inclusão do cabeçalho AVL genérica
#include "AVLGen.h"



//Criacao do no AVL
noAVL* criaNo(void *info)
{

    noAVL *novo = (noAVL*) calloc(1, sizeof(noAVL));

    if(novo == NULL)
    {
    	printf("ERRO: nao foi possivel alocar no\n");
    	return 0;
    }

    novo->info = info;

    return novo;

}


//insere no na arvore
noAVL* insereAVL(noAVL* raiz, void *info, int (*compara) (void*, void*))
{

	//caso base
    //checa se a arvore/subarvore é vazia
    //caso seja, retorna o nó criado
    if(raiz == NULL)
    {
    	noAVL *novo = criaNo(info);
        return novo;
    }

    else//senao
    {
       //caso um nó de mesmo valor ao inserido pelo usuário seja encontrado retorna somente a raiz da subárvore
  		if(compara(info, raiz->info) == 0)
        {
        	printf("Elemento ja esta na arvore\n");
       		return raiz;
   		}

   		//caso o valor inserido pelo usuario seja maior que o no atual, fazemos a recursão a direita
        else if(compara(info, raiz->info) >= 1)
   	    {
			raiz->dir = insereAVL(raiz->dir, info, compara);
        }

        else//caso nao, fazemos a recursao a esquerda
        {
        	raiz->esq = insereAVL(raiz->esq, info, compara);
       	}
	}

	//atualiza a altura do nó atual da recursão
	raiz->altura = 1 + getMaiorInteiro(getAltura(raiz->esq), getAltura(raiz->dir));
	//retorna o nó passando pela função de balanceamento, que será responsável por verificar se o nó precisa ou não de ser balanceado
   	return balanceamentoAVL(raiz);
}


//Deleta árvore
void deletaAVL(noAVL* raiz)
{
    if(raiz == NULL)return raiz;

    //deleta recursivamente subarvore a esquerda
    deletaAVL(raiz->esq);
    //deleta recursivamente subarvore a direita
    deletaAVL(raiz->dir);

    free(raiz);

}


//busca elemento
void buscaAVL(noAVL* raiz, void *info, int (*compara) (void*, void*), void (*imprime) (void*))
{
    noAVL *aux = raiz;


    //checa se a arvore é vazia
    if(raiz == NULL)return 0;


    else
    {   //percorre a lista até encontrar o fim ou um no procurado
        //chama a função para imprimir
        while(aux != NULL)
        {
            if(compara(info, aux->info) == 0)
            {
                printf("Elemento encontrado\n");
                imprime(aux->info);
                return 1;
            }

             else if(compara(info, aux->info) == 1)
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
        	return 0;
      	}
    }
}



//deleta um determinado no da arvore
noAVL* deletaNoAVL(noAVL* raiz, void *info, int (*compara) (void*, void*))
{


    //checa se a arvore é vazia
    //caso seja, arvore
    if(raiz == NULL)return raiz;


   	//caso o valor inserido pelo usuario seja maior que o no atual, fazemos a recursão a direita
    if(compara(info, raiz->info) >= 1)
   	{
      raiz->dir = deletaNoAVL(raiz->dir, info, compara);
   	}

   	else if(compara(info, raiz->info) <= -1)//caso nao, fazemos a recursao a esquerda
   	{
   	  raiz->esq = deletaNoAVL(raiz->esq, info, compara);
   	}


    else//elemento a ser excluido encontrado
   	{
       	//trata o caso do no excluido sem nenhuma sub arvore
       	if(raiz->esq == NULL && raiz->dir == NULL)
       	{	  		
       		return NULL;
        }

        //trata o caso do no ter uma subarvore à direita
        else if(raiz->esq == NULL && raiz->dir != NULL)
       	{	
       		//copia os dados da no nó a direita, que será excluído
        	noAVL *novo = raiz->dir;
        	raiz->info = novo->info; 
        	//exclui o no repetido da subarvore a direita, atravez da função:
        	raiz->dir = deletaNoAVL(raiz->dir, novo->info, compara);   	
     	  }

       	//trata o caso do no ter uma subarvore à esquerda
       	else if(raiz->esq != NULL && raiz->dir == NULL)
       	{	
       		//análogo ao caso acima
        	noAVL *novo = raiz->esq;
        	raiz->info = novo->info;
        	raiz->esq = deletaNoAVL(raiz->esq, novo->info, compara);

        }

        //trata o caso do no ter duas subarvores
        else if(raiz->esq != NULL && raiz->dir != NULL)
        {

           	noAVL *novo = raiz->dir;

           	//percorre a subárvore a direita, até achar o menor valor dessa subarvore

			while(novo->esq != NULL) novo = novo->esq;

			//copia os valores dos nós atual e novo, e passa novamente a função de remoção para remover a chave de repetida a direita

			raiz->info = novo->info;
			raiz->dir = deletaNoAVL(raiz->dir, novo->info, compara);

        }
   	}

   	//atualiza a altura do nó atual da recursão
   	raiz->altura = 1 + getMaiorInteiro(getAltura(raiz->esq), getAltura(raiz->dir));
   	
   	//retorna o nó passando pela função de balanceamento, que será responsável por verificar se o nó precisa ou não de ser balanceado
  	return balanceamentoAVL(raiz);

}

//Rotação direita
noAVL* LL(noAVL* v)
{	
	//seta u para receber a subarvore a esquerda de v
	noAVL *u = v->esq;
	//seta T2 para receber a subarvore a direita de u
	noAVL *T2 = u->dir;

	//aponta a direta de u para v
	u->dir = v;
	//a esquerda de v reve subarvore T2 
	v->esq = T2;

	//atualiza as alturas
	v->altura = 1 + getMaiorInteiro(getAltura(v->esq), getAltura(v->dir));
	u->altura = 1 + getMaiorInteiro(getAltura(u->esq), getAltura(u->dir));

	//retorna u, a nova raiz da subárvore
	return u;
}

//Rotação esquerda
noAVL* RR(noAVL* v)
{
	//seta u para receber a subarvore a direita de v
	noAVL *u = v->dir;
	//seta T2 para receber a subarvore a esquerda de u
	noAVL *T2 = u->esq;

	//aponta a esquerda de u para v
	u->esq = v;
	//a direita de v reve subarvore T2 
	v->dir = T2;

	//atualiza as alturas
	v->altura = 1 + getMaiorInteiro(getAltura(v->esq), getAltura(v->dir));
	u->altura = 1 + getMaiorInteiro(getAltura(u->esq), getAltura(u->dir));

	//retorna u, a nova raiz da subárvore
	return u;
}

//Rotação dupla direita
noAVL* LR(noAVL* raiz)
{	
	//performa a rotação a esquerda na subárvore a esquerda
	raiz->esq = RR(raiz->esq);
	//retorna rotação a direita aplicada à raiz da árvore
	return LL(raiz);
}

//Rotação dupla esquerda
noAVL* RL(noAVL* raiz)
{	
	//performa a rotação a direita na subárvore a direita
	raiz->dir = LL(raiz->dir);
	//retorna rotação a esquerda aplicada à raiz da árvore
	return RR(raiz);
}

//retorna altura do nó, se for null retorna -1
int getAltura(noAVL* raiz)
{
	if(raiz == NULL) return -1;
	else return raiz->altura;
}

//retorna balanceamento
int getBalanceamento(noAVL* raiz)
{
	return getAltura(raiz->esq) - getAltura(raiz-> dir);
}

//compara inteiros
int getMaiorInteiro(int x, int y)
{
	if(x > y) return x;
	else return y;
}

//verifica a necessidade de balancear a arvore/subarbore
noAVL* balanceamentoAVL(noAVL* raiz)
{	
	//verifica os 4 casos de balanceamento.
	//fator de balanceamento de v	//fator de balanceamento de u 	//rotação
	//			 2								 1						LL
	//			-2								-1						RR
	//			 2								-1						LR
	//			-2								 1						RL 	
	if(getBalanceamento(raiz) == 2 && getBalanceamento(raiz->esq) == 1)return LL(raiz);
	else if(getBalanceamento(raiz) == -2 && getBalanceamento(raiz->dir) == -1)return RR(raiz);	
	else if(getBalanceamento(raiz) == 2 && getBalanceamento(raiz->esq) == -1)return LR(raiz);	
	else if(getBalanceamento(raiz) == -2 && getBalanceamento(raiz->dir)== 1)return RL(raiz);
	else return raiz;
}

//Percuro preOrdem
void preOrdem(noAVL* raiz, int nivel, void (*imprimeChave) (void*))
{
    if(raiz != NULL)
    {
        imprimeChave(raiz->info);
        preOrdem(raiz->esq, nivel+1, imprimeChave);
        preOrdem(raiz->dir, nivel+1, imprimeChave);
    }

}

//Percuro em ordem
void emOrdem(noAVL* raiz, int nivel, void (*imprimeChave) (void*))
{
    if (raiz != NULL)
    {
        emOrdem(raiz->esq, nivel+1, imprimeChave);
        imprimeChave(raiz->info);
        emOrdem(raiz->dir, nivel+1, imprimeChave);
    }

}

//Percuro pós ordem
void posOrdem(noAVL* raiz, int nivel, void (*imprimeChave) (void*))
{
    if (raiz != NULL)
    {
        posOrdem(raiz->esq, nivel+1, imprimeChave);
        posOrdem(raiz->dir, nivel+1, imprimeChave);
        imprimeChave(raiz->info);
    }

}



