//Thiago Rodrigues Gouveia da Silva
//Victor Cezari Nascimento


#include "Huffman.h"


//cria o nó que será inserido na heap
noHeap *criaNo(int frequencia, char simbolo)
{
	noHeap *novo = (noHeap*) calloc(1, sizeof(noHeap));

	if(novo == NULL)
    {
    	printf("ERRO: nao foi possivel alocar no\n");
    	return 0;
    }

    novo->simbolo = simbolo;
    novo->frequencia = frequencia;
    novo->dir = NULL;
    novo->esq = NULL;

    return novo;
}

//cria a heap
heapMin *criaHeapMin(int tamanhoMax)
{
	heapMin *novo = (heapMin*) calloc(1, sizeof(heapMin));

	if(novo == NULL)
    {
    	printf("ERRO: nao foi possivel alocar no\n");
    	return 0;
    }

    novo->tamanhoMax = tamanhoMax;
    novo->heap = (noHeap**) calloc(tamanhoMax, sizeof(noHeap));

	return novo;
}

//cria a estrutura que irá armazenar a tabela de huffman
tabelaHuffman *criaTabelaHuffman(int tamanhoMax)
{
	tabelaHuffman *novo = (tabelaHuffman*) calloc(1, sizeof(tabelaHuffman));

	if(novo == NULL)
    {
    	printf("ERRO: nao foi possivel alocar no\n");
    	return 0;
    }

    novo->tamanho = 0;
    novo->caractere = (char*) calloc(tamanhoMax, sizeof(char));
    novo->bit = (int*) calloc(tamanhoMax, sizeof(int));
    novo->frequencia = (int*) calloc(tamanhoMax, sizeof(int));

	return novo;
}

//Mantem a propriedade do heap minimo
//Nesse caso o pai tem que ser menor do que seus filhos
//A motivação de usar o heap minimo vai ser explicitada na função de retirar o menor elemento
void minHeapify(heapMin *A, int i)
{

 	int menor;
 	//seta valor para indice à esquerda
 	int l = 2 * i + 1;
 	//seta valor para indice à direita
 	int r = 2 * i + 2;

 	if (l < A->tamanho && A->heap[l]->frequencia < A->heap[i]->frequencia)menor = l;
 	else menor = i;

  	if (r < A->tamanho && A->heap[r]->frequencia < A->heap[menor]->frequencia)menor = r;

  	if (menor != i)
  	{

    	//Performa a troca
    	noHeap *aux = A->heap[menor];
		A->heap[menor] = A->heap[i];
		A->heap[i] = aux;
		//chama recursivamente passa menor
    	minHeapify(A, menor);
  	}
}

//função que insere um nó na heap
void insereHeap(heapMin *A, noHeap *no)
{
	//incrementa o tamanho
	A->tamanho++;

	//Inicializa i com a ultima posição do heap
	int i = A->tamanho - 1;

	A->heap[i] = no;
	minHeapify(A, 0);

}

//Função que extrai mínimo, e retorna para ser inserido na árvore de Huffman
noHeap *extraiMin(heapMin *A)
{
	//auxiliar que irá ser retornada recebe primeira posição da heap
	noHeap *aux = A->heap[0];
	//i receberá a posição do ultimo elemento da heap
	int i = A->tamanho - 1;
	//troca primeiro com ultimo
	A->heap[0] = A->heap[i];
	//decrementa o tamanho
	A->tamanho--;

	//corrige a troca feita acima
	minHeapify(A, 0);

	return aux;
}

//Função que dado um vetor, assegura as propriedades do heap
void ConstruirHeapMin(heapMin *A)
{
 	int tamanho = A->tamanho - 1;
 	int i;

 	for (i = (tamanho - 1) / 2; i >= 0; --i)minHeapify(A, i);
}

//função que preenche o vetor heap e retorna o novo heap já passando pela função de construir
heapMin *preencheHeap(char *simbolo, int *frequencia, int tamanho)
{
	int i = 0;
	heapMin *novo = criaHeapMin(tamanho);

	while(i < tamanho)
	{
		novo->heap[i] = criaNo(frequencia[i], simbolo[i]);
		i++;
	}

	novo->tamanho = tamanho;
	ConstruirHeapMin(novo);

	return novo;
}

//imprime tabela de frequencia
void imprimeTabelaFreq(char *simbolo, int *frequencia, int tamanho)
{
	int i = 0;
    printf("caractere|ocorrencias\n");
	while(i < tamanho)
	{
		putchar(simbolo[i]);
		printf("|%i",frequencia[i]);
		printf("\n");
		i++;
	}
}

//constroi a árvore de Huffman
noHeap *Huffman(heapMin *A)
{
	noHeap *esq, *dir, *aux;
	int freqAux;

    //enquanto o tamanho da heap for maior que um
	while(A->tamanho > 1)
	{
        //retira o menor valor da heap e armazena no nó que será inserido à esquerda do novo nó
		esq = extraiMin(A);
        //retira o segundo menor valor da heap e armazena no nó que será inserido à direita do novo nó
		dir = extraiMin(A);
        //a frequencia do novo nó é a soma do seu nó à esquerda e o da direita
		freqAux = esq->frequencia + dir->frequencia;
        //cria o novo nó e insere os nós à esquerda e a direita
		aux = criaNo(freqAux, NULL);
		aux->esq = esq;
		aux->dir = dir;

        //insere o nó criado na heap
		insereHeap(A, aux);

	}
    //retorna o único nó que é a raiz da árvore
	return extraiMin(A);
}


//Constroi a tabela de Huffman
tabelaHuffman *codigoHuffman(noHeap *raiz, int i, char codigo[], tabelaHuffman *t, int tamanho, char *simbolo, int *frequencia)
{
    //quando é executado a recursão à esquerda, o código recebe 0
	if(raiz->esq != NULL)
	{
		codigo[i] = '0';
		t = codigoHuffman(raiz->esq, i + 1, codigo, t, tamanho, simbolo, frequencia);
	}

    //quando é executado a recursão à direita, o código recebe 1
	if(raiz->dir != NULL)
	{
		codigo[i] = '1';
        t = codigoHuffman(raiz->dir, i + 1, codigo, t, tamanho, simbolo, frequencia);
	}

	//Se os filhos são NULL, o nó está na folha, onde o caractere está armazenado
	if(raiz->dir == NULL && raiz->esq == NULL)
	{
        //final da string código recebe \0
		codigo[i] = '\0';
        //caractere recebe o simbolo que estava na árvore
        t->caractere[t->tamanho] = raiz->simbolo;
        //copia a string código para o array de strings
        strcpy(t->codigo[t->tamanho], codigo);
        //frequencia recebe a frequencia do caracter
        t->frequencia[t->tamanho] = getFrequencia(t, tamanho, simbolo, frequencia);
        //recebe quantos bits serão necessários para aquele caractere especifico
        t->bit[t->tamanho] = strlen(t->codigo[t->tamanho]) * t->frequencia[t->tamanho];
        //incrementa o tamanho
        t->tamanho++;
	}

	else return t;
}

//Função que retorna a frequencia do caractere para armazenar na tabela de huffman
int getFrequencia(tabelaHuffman *t, int tamanho, char *simbolo, int *frequencia)
{
    int i = 0;

    while(i < tamanho)
    {
        if(simbolo[i] == t->caractere[t->tamanho])
        {
            return frequencia[i];
        }
        i++;
    }
}

//Imprime a tabela de Huffman
void imprimeTabelaHuffman(tabelaHuffman *t)
{
    int i = 0;
    printf("caractere|codigo|frequencia|bits\n");
    while(i < t->tamanho)
    {
        printf("%c|", t->caractere[i]);
        printf("%s|", t->codigo[i]);
        printf("%i|", t->frequencia[i]);
        printf("%i", t->bit[i]);
        printf("\n");
        i++;
    }
}

//Comprime o arquivo
void comprimirArquivo(tabelaHuffman *t, char *nomeArquivo)
{
	FILE *arquivo;
	char c;
	unsigned char aux;
	int i = 0;
	int j;
    int tamanhoSaida = 0;
    int tamanhoVetAux = 0;

    int posicao=0;
    int posbyte, posbit, desloc;

    //faz a somatória dos bits necessários para cada caractere
    while(i<t->tamanho)
    {
        tamanhoSaida+=t->bit[i];
        i++;
    }

    //como um vetor é declarado em bytes, divide por 8
    int aux2 = tamanhoSaida;
    tamanhoSaida/=8;
    aux2%=8;
    tamanhoSaida += aux2;
    //Vetor de saída será inicializado com o tamanho APROXIMADO de bits
    unsigned char saida[tamanhoSaida];
    memset(saida,0,tamanhoSaida);


    //abre o arquivo que será comprimido
	arquivo = fopen(nomeArquivo, "r");

    //caso o arquivo nao exista
	if(arquivo == NULL)
	{
		printf("Erro ao abrir o arquivo selecionado\n");
		return 0;
	}

    //lê os caracteres do arquivo enquanto não chegar no fim do arquivo
	while((c = fgetc(arquivo))!=EOF)
	{
		i = 0;
        //procuro o caractere na tabela de huffman
		while(c != t->caractere[i])i++;

        //lê o tamanho do código
		tamanhoVetAux = strlen(t->codigo[i]);
		//declara um vetor de inteiros para converter de char para inteiro
        int vetAux[tamanhoVetAux];
    	j = 0;

        //converte de char para inteiro
    	while(t->codigo[i][j] != '\0')
    	{
        	if(t->codigo[i][j] == '0')vetAux[j] = 0;
        	else vetAux[j] = 1;
        	j++;
    	}

        //preenche o vetor saida com o bit 1 ou 0
    	for (i=0; i < tamanhoVetAux; i++)
    	{
       		posbyte = posicao/8;
        	posbit = posicao%8;

        	aux = vetAux[i];
        	aux = aux << 8 - posbit - 1;
            saida[posbyte] = saida[posbyte] | aux;
        	posicao++;
    	}
	}

    //fecha o arquivo
	fclose(arquivo);

    //cria o arquivo comprimido
	FILE *arquivoComprimido;
	char nome[200];
	char enter;
	//armazena o nome do arquivo de saída
    printf("Digite o nome do arquivo de saida: ");
	scanf("%[^\n]", nome);
    scanf("%c",&enter);

    //abre o arquivo
	arquivoComprimido = fopen(nome,"wb");

    //escreve o buffer de saída no arquivo
	fwrite(saida,1, sizeof(saida),arquivoComprimido);

    //fecha o arquivo
    fclose(arquivoComprimido);
}

//Descomprime o arquivo
void descomprimirArquivo(noHeap *raiz, tabelaHuffman *t)
{
    int i = 0;
	char nomeArquivo[200];
	unsigned char aux;
	char nome[200];
	char enter;

    //Pede o nome do arquivo a ser descomprimido
	printf("Digite o nome do arquivo a ser descomprimido: ");
	scanf("%[^\n]", nome);
    scanf("%c",&enter);

    //armazena o nome do arquivo de saída
    printf("Digite o nome do arquivo de saida: ");
	scanf("%[^\n]", nomeArquivo);
    scanf("%c",&enter);

    //calcula o tamanho do vetor de saída
    int tamanho = 0;
    while(i<t->tamanho)
    {
        tamanho+=t->bit[i];
        i++;
    }

    //saida alocada com o tamanho exato do arquivo comprimido
    unsigned char saida[tamanho];
    memset(saida,0,tamanho);

    //abre o arquivo de saida
    FILE *arquivo;
    arquivo = fopen(nome,"rb");

	if(arquivo == NULL)
	{
		printf("Erro ao abrir o arquivo selecionado\n");
		return 0;
	}

    //lê o arquivo a ser descomprimido e armazena no vetor saida
    fread(saida,1,tamanho,arquivo);

    fclose(arquivo);

    //abre o arquivo de saída
    arquivo = fopen(nomeArquivo,"w");

	if(arquivo == NULL)
	{
		printf("Erro ao abrir o arquivo selecionado\n");
		return 0;
	}

    int posbyte, posbit, desloc;
    noHeap *ponteiroAux = raiz;

    char escolha;
    //pergunta a escolha ao usuario
    printf("Deseja imprimir o binario do arquivo ?(1/0): ");
    scanf("%d", &escolha);
    printf("\n");
    setbuf(stdin, NULL);


    for (i = 0; i < tamanho; i++)
    {
        //converte o bit 1 e 0 para int
        posbyte = i/8;
        posbit = i%8;
        aux = 1;
        aux = aux << 8 - posbit - 1;
        aux = saida[posbyte]&aux;
        aux = aux >> 8 - posbit - 1;

        //se a escolha for 1, printa o código de huffman para o arquivo
        if(escolha == 1)printf("%i",aux);
        //anda para a esquerda se o valor lido for 0
        if (aux == 0)ponteiroAux = ponteiroAux->esq;
        //anda para a direita se o valor lido for 1
        else if (aux == 1)ponteiroAux = ponteiroAux->dir;

        //se o no for folha, insere o caractere no arquivo e volta para a raiz
    	if(ponteiroAux->dir == NULL && ponteiroAux->esq == NULL)
        {
            fputc(ponteiroAux->simbolo, arquivo);
            ponteiroAux = raiz;
        }
    }

    printf("\n");
    fclose(arquivo);

}
