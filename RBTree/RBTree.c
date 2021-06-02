//inclusão do cabeçalho ABB genérica
#include "RBTree.h"

//Criacao do no RB
noRB* criaNo(struct artigo a)
{

    noRB *novo = (noRB*) calloc(1, sizeof(noRB));

    if(novo == NULL)
    {
    	printf("ERRO: nao foi possivel alocar no\n");
    	return 0;
    }


    novo->info = a;

    return novo;

}

//Rotação à esquerda
noRB* rotacaoEsquerda(noRB* T, noRB* w)
{	
	noRB *v;

	//nó v vai receber a subárvore a direita de w
	v = w->dir;
	//e a direita de w vai receber a esquerda de v
	w->dir = v->esq;

	//Se o no a esquerda de v nao for externo, atualiza o  pai do nó a esquerda de v, que passará a apontar para w 
	if(v->esq != externo)v->esq->pai = w;

	//o pai de v receberá o pai de v
	v->pai = w->pai;

	//se o nó w for raiz, T recebe V
	if(w->pai == externo)T = v;
	else
	{	//se w for estiver à esquerda do seu pai, o pai receberá v à esquerda
		if(w == w->pai->esq)w->pai->esq = v;
		//senão, o pai receberá v à direita
		else w->pai->dir = v;
	}

	//a esquerda de v receberá w
	v->esq = w;
	//v passará a ser pai de w
	w->pai = v;

	//retorna raiz
	return T;

}

//Rotação à direita
//Analogo ao processo anterior, só que do outro lado
noRB* rotacaoDireita(noRB* T, noRB* w)
{
	noRB *v;

	v = w->esq;
	w->esq = v->dir;

	if(v->dir != externo)v->dir->pai = w;

	v->pai = w->pai;

	if(w->pai == externo)T = v;
	
	else
	{
		if(w == w->pai->dir)w->pai->dir = v;
		else w->pai->esq = v;
	}

	v->dir = w;
	w->pai = v;

	return T;
}


//insere no na arvore
noRB* insereRB(noRB* raiz, struct artigo a)
{
    
   	noRB *novo = criaNo(a);
   	noRB *ant = externo;
   	noRB *aux = raiz;

	//percorre a lista até encontrar o nó externo ou um no já existente
    while(aux != externo)
    {	

        ant = aux;
        if(aux->info.id == novo->info.id)
        {
            printf("Elemento ja esta na arvore\n");
            return raiz;
        }

        else if(aux->info.id > novo->info.id)
        {
            aux = aux->esq;
        }

        else
        {
            aux = aux->dir;
        }
    }

    novo->pai = ant;

    //caso a árvore estiver vazia o novo vai receber raiz
    if(ant == externo) raiz = novo;

    else
    {	//decide se o no será alocado na subarvore à direita ou esquerda
    	if(ant->info.id > novo->info.id) ant->esq = novo;
    	else ant->dir = novo;
    }

    //o novo nó receberá as folhas externas e a cor vermelha
    novo->esq = externo;
    novo->dir = externo;
    novo->cor = true;

    //retorna a raiz balanceada
    return RBInsertFixup(raiz, novo);
}


noRB* RBInsertFixup(noRB* T, noRB* q)
{
	noRB *v, *w, *t;

	//enquanto o pai de q for vermelho
	while(q->pai->cor == true)
	{	
		//v é o pai 
		v = q->pai;
		//w é o avô
		w = v->pai;

		//se o pai estivar na subárvore à esquerda do avô
		if(v == w->esq)
		{	
			//t(tio) vai receber a subárvore à direita do avô
			t = w->dir;
			//se a cor do tio for vermelha
			if(t->cor == true) //Caso 1
			{	
				v->cor = false;
				t->cor = false;
				w->cor = true;
				q = w;
			}
			else//senao
			{	//se q estiver na subárvore à direita do pai
				if(q == v->dir)//Caso 2
				{
					q = v;
					T = rotacaoEsquerda(T, q);
				}
				//Caso 3
				q->pai->cor = false;
				w->cor = true;
				T = rotacaoDireita(T, w);
			}
		}
		
		else//Mesmo processo do que foi esplicado acima, só trocando o lado do pai
		{
			t = w->esq;
			if(t->cor == true) //Caso 1
			{	
				
				v->cor = false;
				t->cor = false;
				w->cor = true;
				q = w;
			}
			else
			{
				if(q == v->esq)//Caso 4
				{
					q = v;
					T = rotacaoDireita(T, q);
				}
				//Caso 5
				q->pai->cor = false;
				w->cor = true;
				T = rotacaoEsquerda(T, w);
			}
		}
	}

	//raiz sempre será preta 
	T->cor = false;
	//retorna raiz
	return T;
}

//função que transfere o pai de u para v 
noRB* RBTransferePai(noRB* T, noRB* u , noRB* v)
{	
	//se u for raiz da árvore
	if(u->pai == externo) T = v;
	else//senao
	{	//se u for filho a esquerda do pai, v vira filho à esquerda do pai de u
		if(u == u->pai->esq)u->pai->esq = v;
		else u->pai->dir = v;//caso contrario, v vira filho à direita do pai de u
	}

	v->pai = u->pai;//atualiza o nó pai

	//retorna raiz
	return T;
}

//no que retorna o menor valor da subárvore à direita do no atual
noRB* sucessor(noRB* z)
{
	noRB *aux = z->dir;
	noRB *ant = z;

	//percorre até o final
	while(aux != externo)
	{
		ant = aux;
		aux = aux->esq;
	}

	//retorna o nó anterior ao externo
	return ant;
}


//deleta um determinado no da arvore
noRB* removeRB(noRB* T, noRB* z)
{
	noRB *x;
	noRB *y = z;
	bool corDeY = y->cor;

	//se o no a ser removido não tiver filho à esquerda
	if(z->esq == externo)
	{	
		//x vai receber z à direita 
		x = z->dir;
		//transfere o pai
		T = RBTransferePai(T, z, z->dir);
	}

	else//senao
	{	
		//se o no a ser removido não tiver filho à direita
		if(z->dir == externo)
		{	
			//x recebe o nó a esquerda de z
			x = z->esq;
			//transfere o pai
			T = RBTransferePai(T, z, z->esq);
		}

		else//senao, caso ambas subárvores a direita e esquerda tenham filhos
		{	

			//y recebe o sucessor
			y = sucessor(z);
			//atualiza a variável cor de y
			corDeY = y->cor;
			//x vai receber o nó à direita de y 
			x = y->dir;

			//se z for pai de y(sucessor), o pai de x vai receber y
			if(y->pai == z) x->pai = y;
			else//senao
			{	
				//transfere o pai
				T = RBTransferePai(T, y, y->dir);
				//a direita de y vai receber esquerda de z
				y->dir = z->dir;
				//aponta o ponteiro pai do nó a direita de y para y
				y->dir->pai = y;
			}

			//transfere o pai
			T = RBTransferePai(T, z, y);
			//troca a esquerdade y pela de z
			y->esq = z->esq;
			//troca o pai do nó à esquerda de y por y 
			y->esq->pai = y;
			//a cor de y vai ser a cor de z
			y->cor = z->cor;
		}
	}

	//se a cor de y for preta, performa o balanceamento
	if(corDeY == false)T = RBDeleteFixup(T, x);

	//retorna a raiz
	return T;
}

//corrige as violações na remoção
noRB* RBDeleteFixup(noRB* T, noRB* x)
{
	noRB *w;

	//enquanto não chegar na raiz da árvore
	while(x != T && x->cor == false)
	{	
		//se o no removido estiver à esquerda do pai
		if(x == x->pai->esq)
		{	
			//w vai ser o irmao
			w = x->pai->dir;

			//se a cor do irmao for vermelha
			if(w->cor == true)//caso 1
			{	
				//irmao é pintado de preto
				w->cor = false;
				//pai é pintado de vermelho
				x->pai->cor = true;
				//aplica a rotação à esquerda
				T = rotacaoEsquerda(T, x->pai);
				//atualiza o irmao
				w = x->pai->dir;
			}

			//se as cores do filho de w forem pretas
			if(w->esq->cor == false && w->dir->cor == false)//caso 2
			{	
				//a cor de w vira vermelho
				w->cor = true;
				//x sobe e aponta para seu pai
				x = x->pai;
			}

			//senao
			else
			{	
				//se o nó à direita de w for preto
				if(w->dir->cor == false)//caso 3
				{	
					//o da esquerda também será
					w->esq->cor = false;
					//a cor de w será vermelha 
					w->cor = true;
					//performa a rotação a direita 
					T = rotacaoDireita(T, w);
					//w vai receber o nó à direita do pai
					w = x->pai->dir;
				}

				//caso 4
				w->cor = x->pai->cor;
				//pinta o pai de x de preto
				x->pai->cor = false;
				//pinta a direita de w de preto
				w->dir->cor = false;
				//performa a rotação à esquerda
				T = rotacaoEsquerda(T, x->pai);
				//x recebe a raiz
				x = T;
			}
		}

		else//Mesmo processo do que foi esplicado acima, só trocando o lado do pai
		{
			w = x->pai->esq;

			if(w->cor == true)
			{
				w->cor = false;
				x->pai->cor = true;
				T = rotacaoDireita(T, x->pai);
				w = x->pai->esq;
			}

			if(w->esq->cor == false && w->dir->cor == false)
			{
				w->cor = true;
				x = x->pai;
			}

			else
			{
				if(w->esq->cor == false)
				{
					w->dir->cor = false;
					w->cor = true;
					T = rotacaoEsquerda(T, w);
					w = x->pai->esq;
				}

				
				w->cor = x->pai->cor;
				x->pai->cor = false;
				w->esq->cor = false;
				T = rotacaoDireita(T, x->pai);
				x = T;
			}
		}
	}

	//atualiza a cor de x para preto
	x->cor = false;

	//retorna raiz
	return T;
}

//Deleta árvore
void deletaRB(noRB* raiz)
{
    if(raiz == externo)return raiz;

    deletaRB(raiz->esq);
    deletaRB(raiz->dir);


    free(raiz);

}


//busca elemento
noRB* buscaRB(noRB* raiz, int id)
{
    noRB *aux = raiz;
    //checa se a arvore é vazia
    if(raiz == externo)
    {
    	printf("Arvore vazia\n");
        return 0;
    }

    else
    {   
       	//percorre a lista até encontrar o externo 
        while(aux != externo)
        {	
        	//se achar o elemento retorna o próprio
            if(aux->info.id == id)
            {	
            	printf("Artigo encontrado\n");
                return aux;
            }

      		//senão, caminha para a direita caso id for maior que o nó atual
            else if(id > aux->info.id)
            {
                aux = aux->dir;
            }

            else//ou para direita se for menor 
            {
                aux = aux->esq;
            }
        }

        //se arvore for vazia, ou elemento não for encontrado, printa a mensagem e retorna o no atual
      	if(aux == externo)
      	{
        	printf("Elemento nao encontrado\n");
        	return aux;
      	}
    }
}

//imprime as chaves
void imprimeChaveTab (noRB* raiz, int nivel)
{
    int i = 0;

    while(i < nivel)
    {
        printf("\t");
        i++;
    }
    printf("%d:%d\n ",raiz->info.id,raiz->cor);
}

//Percuro preOrdem
void preOrdem(noRB* raiz, int nivel)
{
    if(raiz != externo)
    {
        printf("\t");
        imprimeChaveTab(raiz, nivel);
        preOrdem(raiz->esq, nivel+1);
        preOrdem(raiz->dir, nivel+1);
    }
}

//Percuro em ordem
void emOrdem(noRB* raiz, int nivel)
{
    if (raiz != externo)
    {
        emOrdem(raiz->esq, nivel+1);
        printf("\t");
        imprimeChaveTab(raiz, nivel);
        emOrdem(raiz->dir, nivel+1);
    }
}

//Percuro pós ordem
void posOrdem(noRB* raiz, int nivel)
{
    if (raiz != externo)
    {
        posOrdem(raiz->esq, nivel+1);
        posOrdem(raiz->dir, nivel+1);
        printf("\t");
        imprimeChaveTab(raiz, nivel);
    }    
}




