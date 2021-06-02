//Thiago Rodrigues Gouveia da Silva
//Victor Cezari Nascimento

//declaração do cabeçalho
#ifndef _HUFFMAN_H
#define _HUFFMAN_H

//declaração das bibliotecas necessárias para a execução do código
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct no
{
	struct no *esq, *dir;
	char simbolo;
	int frequencia;

}noHeap;

typedef struct heap
{
	noHeap **heap;
	int tamanho;
	int tamanhoMax;
}heapMin;

typedef struct Huffman
{
   char *caractere;
   int *frequencia;
   int *bit;
   unsigned char codigo[255][8];
   int tamanho;

}tabelaHuffman;


//cria o nó que será inserido na heap
noHeap *criaNo(int frequencia, char simbolo);

//cria a heap 
heapMin *criaHeapMin(int tamanhoMax);

//Heapify mínimo
void minHeapify(heapMin *A, int i);

//função que insere um nó na heap
void insereHeap(heapMin *A, noHeap *no);

//Função que extrai mínimo, e retorna para ser inserido na árvore de Huffman
noHeap *extraiMin(heapMin *A);

//Função que dado um vetor, assegura as propriedades do heap
void ConstruirHeapMin(heapMin *A);

//função que preenche o vetor heap e retorna o novo heap já passando pela função de construir 
heapMin *preencheHeap(char *simbolo, int *frequencia, int tamanho);

//imprime tabela de frequencia
void imprimeTabelaFreq(char *simbolo, int *frequencia, int tamanho);

//constroi a árvore de Huffman
noHeap *Huffman(heapMin *A);

//Constroi a tabela de Huffman
tabelaHuffman *codigoHuffman(noHeap *raiz, int i, char codigo[], tabelaHuffman *t, int tamanho, char *simbolo, int *frequencia);

//Função que retorna a frequencia do caractere para armazenar na tabela de huffman
int getFrequencia(tabelaHuffman *t, int tamanho, char *simbolo, int *frequencia);

//Imprime a tabela de Huffman
void imprimeTabelaHuffman(tabelaHuffman *t);

//Comprime o arquivo
void comprimirArquivo(tabelaHuffman *t, char nomeArquivo[]);

//Descomprime o arquivo
void descomprimirArquivo(noHeap *raiz, tabelaHuffman *t);



#endif

