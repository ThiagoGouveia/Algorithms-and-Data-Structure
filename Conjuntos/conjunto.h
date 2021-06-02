//declaração do cabeçalho
#ifndef _CONJUNTO_H
#define _CONJUNTO_H

//declaração das bibliotecas necessárias para a execução do código
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>

//declaração da estrutura no que armazenará os elementos do conjunto
typedef struct no
{
	struct no *prox;
	int valor;
}no;

//declaração da estrutura conjunto que será uma lista de conjuntos, que terá um apontamento para uma lista 
//que serão armazenados os elementos do conjunto
typedef struct conjunto
{
	struct no *lista, *prox;
	char nome[100];
}listaConjunto;

//protótipos das função que estarão sendo implementadas no arquivo "conjunto.c"

//cria no
no *criaNo (int valor);
//cria noLista
listaConjunto *criaNoListaConjunto (char *nome[]);
//insereFinal
listaConjunto *insereFinalListaConjunto(listaConjunto *L, char *nome[]);
//insere elemento num conjunto específico
listaConjunto *insereElementoConjunto(listaConjunto *L, int valor, char *nome[]);
//imprime conjunto
void imprimeConjunto(no *L, char *nome[]);
//esvazia um conjunto
listaConjunto *esvaziaConjunto(listaConjunto *L, char *nome[]);
//verifica se o conjunto eh vazio
bool conjuntoVazio(listaConjunto *L,char *nome[]);
//uniao de conjuntos
listaConjunto *uniaoConjuntos(listaConjunto *L, char *nome[], char *nome2[]);
//intersecao de conjuntos
listaConjunto *intersecaoConjuntos(listaConjunto *L, char *nome[], char *nome2[]);
//complemento relativo
listaConjunto *complementoRelativoConjuntos(listaConjunto *L, char *nome[], char *nome2[]);
//exclui conjunto
listaConjunto *excluiConjunto(listaConjunto *L, char *nome[]);
//conjuntos iguais
bool conjuntosIguais(listaConjunto *L, char *nome[], char *nome2[]);
//elemento esta no conjunto
bool verificaElementoConjunto(listaConjunto *L, char *nome[], int valor);
//conjunto contem conjunto
bool conjuntoContemConjunto(listaConjunto *L, char *nome[], char *nome2[]);
//remove elemento do conjunto
listaConjunto *removeElemento(listaConjunto *L, char *nome[], int valor);


#endif
