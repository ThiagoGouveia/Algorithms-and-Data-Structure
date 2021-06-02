//inclusão do cabeçalho conjunto
#include "conjunto.h"

//cria no
no *criaNo (int valor)
{	//declaração do tipo no que será retornado para ser inserido na lista de elementos
	no *novo;
	novo = (no*) malloc(sizeof(no));
	//se ele for null, a alocação não foi realizada com sucesso
	if(novo == NULL)
	{
		printf ( "ERRO: problemas com a alocacao de memoria . \n " );
		exit(1);
	}

	//apontamentos recebem o valor e o numero.
	novo->valor = valor;
	novo->prox = NULL;
	return novo;
}

//cria noLista
listaConjunto *criaNoListaConjunto (char *nome[])
{
	//declaração do tipo noLista que será retornado para ser inserido na lista de conjuntos
	listaConjunto *novo;
	novo = (listaConjunto*) malloc(sizeof(listaConjunto));

	//se ele for null, a alocação não foi realizada com sucesso
	if(novo == NULL)
	{
		printf ( "ERRO: problemas com a alocacao de memoria . \n " );
		exit(1);
	}

	//a a função strcpy da string.h para copiar a string recebida como parâmentro para o ponteiro da lista
	strcpy(novo->nome, nome);
	novo->prox = NULL;
	novo->lista = NULL;
	return novo;
}

//insereFinal
listaConjunto *insereFinalListaConjunto(listaConjunto *L, char *nome[])
{
	//cria o no que será inserido no conjunto
	listaConjunto *novo = criaNoListaConjunto(nome);
	listaConjunto *aux = L;

	//se a lista for vazia, insere no incício
	if(L == NULL)L = novo;
	else
	{//senao, percorro até null ou até quando encontrar o conjunto com o mesmo nome
		//para isso, uso uma função da string.h que compara as strings e retorna um booleano
		while(aux->prox !=NULL && strcmp (aux->nome, nome) != 0)
		{
			aux = aux->prox;
		}

		//se as strings forem iguais, o conjunto já existe
		if(strcmp (aux->nome, nome) == 0)
		{
			printf("Conjunto ja existe\n");
		}
		//senão aloco o conjunto no final
		else aux->prox = novo;
	}
	return L;
}

//insere elemento num conjunto específico
listaConjunto *insereElementoConjunto(listaConjunto *L, int valor, char *nome[])
{
	// crio um novo do tipo no
	no *novo = criaNo(valor);
	listaConjunto *aux = L;
	no *auxLista = NULL, *predLista = NULL;

	//se L for igual a null, nao existe nenhum conjunto, logo nao tem nenhum lugar para adicionar o nó
	if(L == NULL)
	{
		printf("Nenhum conjunto adicionado\n");
		return L;
	}

	else//senao
	{	//percorre até null ou até quando encontrar o conjunto com o mesmo nome
		while(aux != NULL && strcmp (aux->nome, nome) != 0)
		{
			aux = aux->prox;
		}
		//se aux chegar a null, o conjunto informado nao existe
		if(aux == NULL)
		{
			printf("Conjunto nao encontrado\n");
			return L;

		}
		//senao, uma auxiliar vai receber a lista de elementos do conjunto determinado
		else auxLista = aux->lista;

		//enquanto a lista não estiver no final, ou o elemento for maior ou igual eu percorro a lista
		while(auxLista != NULL && valor >= auxLista->valor)
		{	//se o elemento for igual, eu não faço nada, pois conjuntos não podem receber valores iguais
			if(auxLista->valor == valor)
			{
				printf("Valor ja inserido\n");
				return L;
			}
			predLista = auxLista;
			auxLista = auxLista->prox;
		}

		//inserção no inicio
		if(predLista == NULL)
		{
			novo->prox = auxLista;
			aux->lista = novo;
		}

		else
		{	//inserção no meio/final
			novo->prox = auxLista;
			predLista->prox = novo;
		}
	}

	return L;
}

//imprime conjunto
void imprimeConjunto(no *L, char *nome[])
{
	listaConjunto *aux = L;
	no *auxLista = NULL;

	//se lista de conjuntos nao tiver nada pra imprimir eu volto pra main sem fazer nada
	if(L == NULL)
	{
		printf("Nenhum conjunto adicionado\n");
		return L;
	}

	// verifica se o conjunto selecionado só contem vazio, se for o caso printa "vazio"
	else if(conjuntoVazio(L, nome))
	{
		printf(" vazio\n");
		return L;
	}

	else//senao
	{	//percorre até null ou até quando encontrar o conjunto com o mesmo nome
		while(aux != NULL && strcmp (aux->nome, nome) != 0)
		{
			aux = aux->prox;
		}

		//se chegar ao final, e quer dizer que o conjunto nao existe
		if(aux == NULL)
		{
			printf("Conjunto nao encontrado\n");
			return 0;

		}

		//senao, uma auxiliar vai receber a lista de elementos do conjunto determinado
		else auxLista = aux->lista;
		//percorre a lista até o final imprimindo os elementos da lista
   
		while(auxLista != NULL)
		{
			printf(" %d ", auxLista->valor);
			auxLista = auxLista->prox;
		}
		printf("\n\n");
	}
}

//esvazia um conjunto
listaConjunto *esvaziaConjunto(listaConjunto *L, char *nome[])
{
	listaConjunto *aux = L;
	no *auxLista = NULL;

	//se lista de conjuntos nao tiver nada pra imprimir eu volto pra main sem fazer nada
	if(L == NULL)
	{
		printf("Nenhum conjunto adicionado\n");
		return L;
	}

	// verifica se o conjunto selecionado só contem vazio, se for o caso printa "vazio"
	else if(conjuntoVazio(L, nome))
	{
		printf("conjunto vazio\n");
		return L;
	}

	else//senao
	{	//percorre até null ou até quando encontrar o conjunto com o mesmo nome
		while(aux != NULL && strcmp (aux->nome, nome) != 0)
		{
			aux = aux->prox;
		}
		//se chegar ao final, quer dizer que o conjunto nao existe
		if(aux == NULL)
		{
			printf("Conjunto nao encontrado\n");
			return L;
		}

		else//senao
		{	//enquanto o ponteiro lista de elementos não for igual a null, auxiliar recebe o primeiro elemento, o ponteiro lista de elementos vai receber o prox
			//e libera a memorio da aux
			while(aux->lista != NULL)
			{
				auxLista = aux->lista;
				aux->lista = aux->lista->prox;
				free(auxLista);
			}
		}
	}

	return L;
}

//verifica se o conjunto eh vazio
bool conjuntoVazio(listaConjunto *L,char *nome[])
{
	listaConjunto *aux = L;
	no *auxLista = NULL;

	//se lista de conjuntos nao tiver nada pra imprimir eu volto pra main sem fazer nada
	if(L == NULL)
	{
		printf("Nenhum conjunto adicionado\n");
		return true;
	}

	else//senao
	{	//percorre até null ou até quando encontrar o conjunto com o mesmo nome
		while(aux != NULL && strcmp (aux->nome, nome) != 0)
		{
			aux = aux->prox;
		}
		//se chegar ao final, quer dizer que o conjunto nao existe
		if(aux == NULL)
		{
			printf("Conjunto nao encontrado\n");
			return true;
		}

		//se o ponteiro que recebe a lista nao tiver nada retorna verdadeiro
		else if(aux->lista == NULL)return true;
		//senao falso
		else return false;

	}
}


//uniao de conjuntos
listaConjunto *uniaoConjuntos(listaConjunto *L, char *nome[], char *nome2[])
{

	listaConjunto *aux = L;
	no *auxLista = NULL;
	listaConjunto *aux2 = L;
	no *auxLista2 = NULL;
	char nomeConjunto[10] = "uniao";


	//se lista de conjuntos nao tiver nada pra imprimir eu volto pra main sem fazer nada
	if(L == NULL)
	{
		printf("Nenhum conjunto adicionado\n");
		return L;
	}

	//se os dois conjuntos forem vazios, retorna somente o conjunto vazio
	else if(conjuntoVazio(L, nome) && conjuntoVazio(L, nome2))
	{
		printf("conjunto vazio\n");
		return L;
	}

	else//senao
	{	//insere um novo conjunto chamado uniao, na lista
		insereFinalListaConjunto(L, nomeConjunto);

		//percorre até null ou até quando encontrar o conjunto com o mesmo nome
		while(aux != NULL && strcmp (aux->nome, nome) != 0)
		{
			aux = aux->prox;
		}
		//se chegar ao final, quer dizer que o conjunto nao existe
		if(aux == NULL)
		{
			printf("Conjunto nao encontrado\n");
			return L;

		}

		else//senao
		{	//um auxiliar recebe a lista de elementos do conjunto
			auxLista = aux->lista;
			//percorre ate o final da lista, inserindo no conjunto uniao
			while(auxLista != NULL)
			{
				L =	insereElementoConjunto(L, auxLista->valor, nomeConjunto);
				auxLista = auxLista->prox;
			}
		}

		//repete a mesma logica para o segundo conjunto
		//vale notar que se encontrar elementos repetidos, na função de inserir, isso já está tratado
		//entaom mesmo se o conjunto for o mesmo, a uniao dos dois será ele mesmo
		while(aux2 != NULL && strcmp (aux2->nome, nome2) != 0)
		{
			aux2 = aux2->prox;
		}
		if(aux2 == NULL)
		{
			printf("Conjunto nao encontrado\n");
			return L;

		}

		else
		{
			auxLista2 = aux2->lista;
			while(auxLista2 != NULL)
			{
				L =	insereElementoConjunto(L, auxLista2->valor, nomeConjunto);
				auxLista2 = auxLista2->prox;
			}
		}
	}

	//printa o conjunto com a função de imprimir conjunto
	printf("conjunto %s %s %s:",nome ,nomeConjunto, nome2);
	imprimeConjunto(L, nomeConjunto);
	//esvazia o conjunto
	esvaziaConjunto(L, nomeConjunto);
	//e exclui o conjunto
	L = excluiConjunto(L, nomeConjunto);


	return L;
}

//intersecao de conjuntos
listaConjunto *intersecaoConjuntos(listaConjunto *L, char *nome[], char *nome2[])
{

	listaConjunto *aux = L;
	no *auxLista = NULL;
	listaConjunto *aux2 = L;
	no *auxLista2 = NULL;
	char nomeConjunto[20] = "intersecao";


	//se lista de conjuntos nao tiver nada pra imprimir eu volto pra main sem fazer nada
	if(L == NULL)
	{
		printf("Nenhum conjunto adicionado\n");
		return L;
	}

	//se os dois conjuntos forem vazios, a intersecao sera vazia
	else if(conjuntoVazio(L, nome) && conjuntoVazio(L, nome2))
	{
		printf("conjunto vazio\n");
		return L;
	}

	else//senao
	{	//insere um novo conjunto chamado intersecao, na lista
		insereFinalListaConjunto(L, nomeConjunto);
		//percorre até null ou até quando encontrar o conjunto com o mesmo nome
		while(aux != NULL && strcmp (aux->nome, nome) != 0)
		{
			aux = aux->prox;
		}
		//se chegar ao final, quer dizer que o conjunto nao existe
		if(aux == NULL)
		{
			printf("Conjunto nao encontrado\n");
			return L;

		}

		else//senao
		{	//auxiliar recebe a lista de elementos
			auxLista = aux->lista;
			//enquanto auxiliar nao chegar no final
			while(auxLista != NULL)
			{
				//verifica se o elemento de conjunto A está contido no conjunto b
				//se for true, insere na intersecao
				if(verificaElementoConjunto(L, nome2, auxLista->valor))
					L = insereElementoConjunto(L, auxLista->valor, nomeConjunto);

				auxLista = auxLista->prox;

			}
		}
	}

	//printa o conjunto intersecao
	printf("conjunto %s %s %s:",nome ,nomeConjunto, nome2);
	imprimeConjunto(L, nomeConjunto);
	//esvazia o conjunto
	esvaziaConjunto(L, nomeConjunto);
	//retira o conjunto da lista
	L = excluiConjunto(L, nomeConjunto);

	return L;
}

//complemento relativo
listaConjunto *complementoRelativoConjuntos(listaConjunto *L, char *nome[], char *nome2[])
{

	listaConjunto *aux = L;
	no *auxLista = NULL;
	listaConjunto *aux2 = L;
	no *auxLista2 = NULL;
	char nomeConjunto[30] = "complemento relativo";


	//se lista de conjuntos nao tiver nada pra imprimir eu volto pra main sem fazer nada
	if(L == NULL)
	{
		printf("Nenhum conjunto adicionado\n");
		return L;
	}

	//se os dois conjuntos forem vazios, a intersecao sera vazia
	else if(conjuntoVazio(L, nome) && conjuntoVazio(L, nome2))
	{
		printf("conjunto vazio\n");
		return L;
	}

	else//senao
	{	//insere o conjunto complemento relativo
		insereFinalListaConjunto(L, nomeConjunto);
		//percorre a lista até o final ou até achar o primeiro conjunto
		while(aux != NULL && strcmp (aux->nome, nome) != 0)
		{
			aux = aux->prox;
		}

		//se chegar ao final, o conjunto nao existe
		if(aux == NULL)
		{
			printf("Conjunto nao encontrado\n");
			return L;

		}

		else//senao
		{	//auxiliar recebe os elementos do conjunto
			auxLista = aux->lista;
			while(auxLista != NULL)
			{	//verifica se o elemento de A NÃO está contido em B
				//insere o elemento na lista complemento relativo
				if(verificaElementoConjunto(L, nome2, auxLista->valor) == false)
					L = insereElementoConjunto(L, auxLista->valor, nomeConjunto);

				auxLista = auxLista->prox;

			}
		}
	}

	//imprime a operação
	printf("conjunto %s %s %s:",nome ,nomeConjunto, nome2);
	imprimeConjunto(L, nomeConjunto);
	//esvazia o conjunto
	esvaziaConjunto(L, nomeConjunto);
	//retira o conjunto da lista
	L = excluiConjunto(L, nomeConjunto);

	return L;
}


//exclui conjunto
listaConjunto *excluiConjunto(listaConjunto *L, char *nome[])
{
	listaConjunto *aux = L;
	listaConjunto *pred = NULL;

	//se lista de conjuntos for vazia, retorna a lista vazia
	if(L == NULL)
	{
		printf("Nenhum conjunto encontrado\n");
		return L;
	}

	else//senao
	{	//percorre a lista até o final ou até achar o primeiro conjunto
		while(aux != NULL && strcmp (aux->nome, nome) != 0)
		{
			pred = aux;
			aux = aux->prox;
		}


		//remove o elemento do inicio
		if(pred == NULL) L = aux->prox;
		//remove o elemento do meio/fim
		else pred->prox = aux->prox;

		//libera a auxiliar
		free(aux);


	}

	return L;
}

//conjuntos iguais
bool conjuntosIguais(listaConjunto *L, char *nome[], char *nome2[])
{
	listaConjunto *aux = L;

	no *auxLista = NULL;
	listaConjunto *aux2 = L;
	no *auxLista2 = NULL;

	//se lista de conjuntos for vazia, retorna a lista vazia
	if(L == NULL)
	{
		printf("Nenhum conjunto adicionado\n");
		return false;
	}

	//se os dois conjuntos forem vazios, retorno verdadeiro
	else if(conjuntoVazio(L, nome) && conjuntoVazio(L, nome2))
	{
		return true;
	}

	//se só um dos conjunto for vazio, retorno falso
	else if(conjuntoVazio(L, nome) || conjuntoVazio(L, nome2))
	{
		return false;
	}

	else//senao
	{	//percorre a lista até o final ou até achar o primeiro conjunto
		while(aux != NULL && strcmp (aux->nome, nome) != 0)
		{
			aux = aux->prox;
		}
		//se chegar ao final, o conjunto nao existe
		if(aux == NULL)
		{
			printf("Conjunto nao encontrado\n");
			return false;

		}

		else//senao
		{	//auxiliar recebe a lista de elemento
			auxLista = aux->lista;
		}

		//percorre a lista até o final ou até achar o segundo conjunto
		while(aux2 != NULL && strcmp (aux2->nome, nome2) != 0)
		{
			aux2 = aux2->prox;
		}
		//se chegar ao final, o conjunto nao existe
		if(aux2 == NULL)
		{
			printf("Conjunto nao encontrado\n");
			return false;

		}

		else//senao
		{	//auxiliar recebe a lista de elemento
			auxLista2 = aux2->lista;
		}

		//enquanto nenhum dos dois chegarem ao final
		while(auxLista != NULL && auxLista2 != NULL)
		{	//se o elemento de A for != de B retorna falso
			//lembrando que os elementos foram inseridos de forma ordenada, e pra serem identicos
			//os elementos tem que ser iguais, na posicao igual, para os dois conjuntos
			if(auxLista->valor != auxLista2->valor)return false;
			auxLista = auxLista->prox;
			auxLista2 = auxLista2->prox;
		}

	}
	//se chegar ao final das duas lista, retorna verdadeiro
	return true;
}
//elemento esta no conjunto
bool verificaElementoConjunto(listaConjunto *L, char *nome[], int valor)
{
	listaConjunto *aux = L;
	no *auxLista = NULL;
	//se lista de conjuntos for vazia, retorna a lista vazia
	if(L == NULL)
	{
		printf("Nenhum conjunto adicionado\n");
	}
	//verifica se o conjunto é vazio, se for retorna conjunto vazio e vai para o fim, retornando falso
	else if(conjuntoVazio(L, nome))
	{
		printf("conjunto vazio\n");
	}

	else//senao
	{	//percorre a lista até o final ou até achar o primeiro conjunto
		while(aux != NULL && strcmp (aux->nome, nome) != 0)
		{
			aux = aux->prox;
		}
		//se chegar ao final, o conjunto nao existe
		if(aux == NULL)
		{
			printf("Conjunto nao encontrado\n");

		}

		else//senao
		{	//auxiliar recebe a lista de elementos
			auxLista = aux->lista;
			//percorro até o final
			while(auxLista != NULL)
			{	//se o elemento estiver na lista, eu interrompo o while retornando verdadeiro
				if(auxLista->valor == valor)return true;
				auxLista = auxLista->prox;
			}
		}
	}

	return false;
}

//conjunto contem conjunto
bool conjuntoContemConjunto(listaConjunto *L, char *nome[], char *nome2[])
{
	listaConjunto *aux = L;
	no *auxLista = NULL;
	//se lista de conjuntos for vazia, retorna a lista vazia
	if(L == NULL)
	{
		printf("Nenhum conjunto adicionado\n");
		return false;
	}
	//verifica se o conjunto é vazio, se for retorna conjunto vazio
	else if(conjuntoVazio(L, nome))
	{
		printf("conjunto vazio\n");
		return false;
	}

	else//senao
	{	//percorre a lista até o final ou até achar o primeiro conjunto
		while(aux != NULL && strcmp (aux->nome, nome) != 0)
		{
			aux = aux->prox;
		}
		//se chegar ao final, o conjunto nao existe
		if(aux == NULL)
		{
			printf("Conjunto nao encontrado\n");
			return false;
		}

		else//senao
		{	//auxiliar recebe a lista de elementos
			auxLista = aux->lista;
			//percorro até o final
			while(auxLista != NULL)
			{	//se o elemento de A está contido em B eu continuo no while
				if(verificaElementoConjunto(L, nome2, auxLista->valor ))auxLista = auxLista->prox;
				//senao, retorno falso, saindo do loop
				else return false;
			}
		}
	}
	//se chegar ao fim, quer dizer que A está contido em B
	return true;
}

//remove elemento do conjunto
listaConjunto *removeElemento(listaConjunto *L, char *nome[], int valor)
{
	listaConjunto *aux = L;
	no *auxLista = NULL;
	no *predLista = NULL;
	//se lista de conjuntos for vazia, retorna a lista vazia
	if(L == NULL)
	{
		printf("Nenhum conjunto adicionado\n");
		return L;
	}
	//verifica se o conjunto é vazio, se for retorna conjunto vazio
	else if(conjuntoVazio(L, nome))
	{
		printf("conjunto vazio\n");
		return L;
	}

	else//senao
	{	//percorre a lista até o final ou até achar o primeiro conjunto
		while(aux != NULL && strcmp (aux->nome, nome) != 0)
		{
			aux = aux->prox;
		}
		//se chegar ao final, o conjunto nao existe
		if(aux == NULL)
		{
			printf("Conjunto nao encontrado\n");
			return L;
		}

		else//senao
		{	//auxiliar recebe a lista de elementos
			auxLista = aux->lista;
			//enquanto a lista nao chegar ao fim ou o valor for encontrado percorro a lista
			while(auxLista != NULL && auxLista->valor != valor)
			{
				predLista = auxLista;
				auxLista = auxLista->prox;
			}
			//remove do inicio
			if(predLista == NULL) aux->lista = auxLista->prox;
			//remove do meio//fim
			else predLista->prox = auxLista -> prox;
			//libera auxiliar
			free(auxLista);
		}
	}

	return L;
}
