//Trbalho realizado por:
//Thiago Rodrigues Gouveia da Silva
//Victor Cezari Nascimento 

//declaração do cabeçalho
#ifndef _AVLGEN_H
#define _AVLGEN_H

//declaração das bibliotecas necessárias para a execução do código
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>

//declaração da estrutura no que armazenará os elementos do conjunto

typedef struct no
{
	struct no *dir, *esq;
	void* info;
	int altura;

}noAVL;

//protótipos das função que estarão sendo implementadas no arquivo "AVLGen.c"

//Criacao do no AVL
noAVL* criaNo(void *info);

//insere no na arvore
noAVL* insereAVL(noAVL* raiz, void *info, int (*compara) (void*, void*));

//Deleta árvore
void deletaAVL(noAVL* raiz);

//busca elemento
void buscaAVL(noAVL* raiz, void *info, int (*compara) (void*, void*), void (*imprime) (void*));

//deleta um determinado no da arvore
noAVL* deletaNoAVL(noAVL* raiz, void *info, int (*compara) (void*, void*));

//Rotação direita
noAVL* LL(noAVL* raiz);

//Rotação esquerda
noAVL* RR(noAVL* raiz);

//Rotação dupla direita
noAVL* LR(noAVL* raiz);

//Rotação dupla esquerda
noAVL* RL(noAVL* raiz);

//Retorna a altura do nó
int getAltura(noAVL* raiz);

//Retorna balanceamento do nó
int getBalanceamento(noAVL* raiz);

//Retorna valor de maior inteiro
int getMaiorInteiro(int x, int y);

//verifica a necessidade de balancear a arvore/subarbore
noAVL* balanceamentoAVL(noAVL* raiz);

//Percuro preOrdem
void preOrdem(noAVL* raiz, int nivel, void (*imprimeChave) (void*));

//Percuro em ordem
void emOrdem(noAVL* raiz, int nivel, void (*imprimeChave) (void*));

//Percuro pós ordem
void posOrdem(noAVL* raiz, int nivel, void (*imprimeChave) (void*));


#endif
