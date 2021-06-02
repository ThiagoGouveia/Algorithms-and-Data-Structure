//Thiago Rodrigues Gouveia da Silva
//Victor Cezari Nascimento


#include "Huffman.h"

int main(int argc, char const *argv[])
{
	int *frequencia;
	char *simbolo;
	char aux;
	int tamanho = 0;
	int i = 0;
	char *nomeArquivo = (char*) calloc(100, sizeof(char));;
	char enter;

	frequencia = (int*)calloc(1, sizeof(int));
	simbolo = (char*)calloc(1, sizeof(char));

	FILE *arquivo;

	printf("Digite o nome do arquivo a ser comprimido: ");
	scanf("%[^\n]", nomeArquivo);
    scanf("%c",&enter);
	arquivo = fopen(nomeArquivo, "r");


	if(arquivo == NULL)
	{
		printf("Erro ao abrir o arquivo selecionado\n");
		return 0;
	}

	while((aux = fgetc(arquivo))!=EOF)
	{
		//printf("tamanho: %i\n",tamanho );
		//percorre o vetor até i ser igual ao tamanho, ou achar o simbolo
		i = 0;
		while(i < tamanho){

			//Se simbolo estiver na tabela, só incrementa frequencia e retorna pra main
			if(aux == simbolo[i])
			{
				++frequencia[i];
				break;
			}
			i++;
		}

		//Se chegar ao final do vetor e não encontrar a chave, realoca espaço
		if(i == tamanho)
		{	//se aux for igual a simbolo sai do loop
			if(aux == simbolo[i])break;

			//realoca a memória da frequencia e simbolo
			int *tempfrequencia =  realloc(frequencia, (tamanho + 1)*sizeof(int));
			char *tempSimbolo =  realloc(simbolo, (tamanho + 1)*sizeof(char));

			//se a realocação for bem sucedida
			if(tempfrequencia != NULL && tempSimbolo != NULL)
			{
				//copia o conteudo de temp para variavel original
				frequencia = tempfrequencia;
				simbolo = tempSimbolo;

				//adiciona 1 ao final do array
				frequencia[tamanho] = 1;
				//copia o novo caractere para o final do array simbolo
				simbolo[tamanho] = aux;
			}
			tamanho++;
		}
	}


	fclose(arquivo);


	//imprime a tabela de frequencia
	//imprimeTabelaFreq(simbolo, frequencia, tamanho);

	//cria o heap com a tabela de frequencia de caracteres
	heapMin *novoHeap = preencheHeap(simbolo, frequencia, tamanho);

	//constroi a árvore de Huffman através do heap criado anteriormente
	noHeap *arvoreHuffman = Huffman(novoHeap);

	//cria a tabela de huffman
    tabelaHuffman *t = criaTabelaHuffman(tamanho);

    char codigo[8];
    i = 0;


    //preenche a tabela de huffman
    t = codigoHuffman(arvoreHuffman, i, codigo, t, tamanho, simbolo, frequencia);

    //comprime arquivo
    comprimirArquivo(t, nomeArquivo);

 	int escolha = 0;
 	do//enquanto
    {
    	//imprime menu
        printf("\n0 - Sair\n1 - Imprime tabela de ocorrencias\n2 - Imprime o codigo de Huffman\n3 - Descomprime arquivo\n");

        //pergunta a escolha ao usuario
        printf("Sua escolha: ");
        scanf("%d", &escolha);
        printf("\n");
        setbuf(stdin, NULL);
    	switch(escolha)
        {
        	case 1://imprime tabela de ocorrencias
            	imprimeTabelaFreq(simbolo, frequencia, tamanho);
            	break;
            case 2://tabela com os codigos de huffman
            	imprimeTabelaHuffman(t);
            	break;
            case 3://descomprime arquivo
				descomprimirArquivo(arvoreHuffman, t);
				break;
			case 0:
				free(novoHeap);
				free(t);
				free(arvoreHuffman);
        }

    }while(escolha != 0);

	return 0;
}
