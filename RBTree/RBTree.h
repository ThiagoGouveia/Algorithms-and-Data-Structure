//Trabalho realizado por:
//Thiago Rodrigues Gouveia da Silva
//Victor Cezari Nascimento 

//declaração do cabeçalho
#ifndef _RBTREE_H
#define _RBTREE_H

//declaração das bibliotecas necessárias para a execução do código
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>

//declaração da estrutura que armazenará os elementos do artigo
struct artigo
{
	int id;
	int ano;
	char autor[200];
	char titulo[200];
	char revista[200];
	char DOI[20];
	char palavraChave[200];
};


//declaração da estrutura dos nos da árvore rubro negra
typedef struct no
{
	struct no *dir, *esq, *pai;
	bool cor;
	struct artigo info;

}noRB;

//nó sentinela que irá ficar nas folhas da árvore
noRB *externo;

//protótipos das função que estarão sendo implementadas no arquivo "AbbGen.c"

//Criacao do no RB
noRB* criaNo(struct artigo a);

//rotações à esquerda e direita
noRB* rotacaoEsquerda(noRB* T, noRB* w);
noRB* rotacaoDireita(noRB* T, noRB* w);

//insere no na arvore
noRB* insereRB(noRB* raiz, struct artigo a);

//Correção de balanceamento
noRB* RBInsertFixup(noRB* T, noRB* q);

//transfere o pai de u para o nó v
noRB* RBTransferePai(noRB* T, noRB* u , noRB* v);

//função que retorna o menor valor da subárvore à direita
noRB* sucessor(noRB* z);

//deleta um determinado no da arvore
noRB* removeRB(noRB* T, noRB* z);

//corrige as violações na remoção
noRB* RBDeleteFixup(noRB* T, noRB* x);

//Deleta árvore
void deletaRB(noRB* raiz);

//busca elemento
noRB* buscaRB(noRB* raiz, int id);

//imprime as chaves
void imprimeChaveTab (noRB* raiz, int nivel);

//Percuro preOrdem
void preOrdem(noRB* raiz, int nivel);

//Percuro em ordem
void emOrdem(noRB* raiz, int nivel);

//Percuro pós ordem
void posOrdem(noRB* raiz, int nivel);








#endif
