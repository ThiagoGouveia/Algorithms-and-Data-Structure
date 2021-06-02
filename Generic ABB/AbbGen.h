//declaração do cabeçalho
#ifndef _ABBGEN_H
#define _ABBGEN_H

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

}noABB;

//protótipos das função que estarão sendo implementadas no arquivo "AbbGen.c"

//Criacao do no ABB
noABB* criaNo(void *info);

//insere no na arvore
noABB* insereABB(noABB* raiz, void *info, int (*compara) (void*, void*));

//Deleta árvore
void deletaABB(noABB* raiz);

//busca elemento
void buscaABB(noABB* raiz, void *info, int (*compara) (void*, void*), void (*imprime) (void*));

//deleta um determinado no da arvore
noABB* deletaNoABB(noABB* raiz, void *info, int (*compara) (void*, void*));


//Percuro preOrdem
void preOrdem(noABB* raiz, int nivel, void (*imprimeChave) (void*));

//Percuro em ordem
void emOrdem(noABB* raiz, int nivel, void (*imprimeChave) (void*));

//Percuro pós ordem
void posOrdem(noABB* raiz, int nivel, void (*imprimeChave) (void*));








#endif
