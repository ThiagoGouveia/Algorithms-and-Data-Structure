#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Declaração da estrutura que alocará os usuários
//Detalhe que eu estou declarando dentro da estrutura um ponteiro filho que apontará para a lista de amigos
//Estou usando o conceito Flatten Nested Linked List
typedef struct no
{
	int id;
	char nome[100];
	int idade;
	char email[100];

	struct no *prox, *ant;
	struct listaAmigos *listaAmigos;


}no;

typedef struct listaAmigo
{
    struct no *prox, *ant;
}listaAmigos;

//Função cria no, e preenche com os dados passados por referencias.
//Pra armazenar as strings eu estou copiando elas pra dentro do ponteiro usando a função strcpy da biblioteca string.h
no *criaNo (int id, char *nome[], int idade, char *email[])
{
	no *novo;
	novo = (no*) malloc(sizeof(no));
	if(novo == NULL)
	{
		printf ( "ERRO: problemas com a alocacao de memoria . \n " );
		exit(1);
	}

    novo->id = id;
    strcpy(novo->nome, nome);
    novo->idade = idade;
    strcpy(novo->email, email);
    novo->listaAmigos = NULL;
    novo->prox = NULL;
    novo->ant = NULL;

	return novo;
}

//Mesma função da anterior, porém ela só recebe a id do amigo
no *criaAmigo (int id)
{
	no *novo;
	novo = (no*) calloc(1,sizeof(no));
	if(novo == NULL)
	{
		printf ( "ERRO: problemas com a alocacao de memoria . \n " );
		exit(1);
	}

    novo->listaAmigos = NULL;
    novo->idade = NULL;
    novo->prox = NULL;
    novo->ant = NULL;
    novo->id = id;

	return novo;
}

//Função que insere no final
no *insereFinal(no *L, int id, char *nome[], int idade, char *email[])
{
	no *novo = criaNo(id, nome, idade, email);
	no *aux = L;
	//Se o ponteiro que apontara pra função for null ela somente recebera novo
	if(L == NULL)L = novo;

	else
	{	//A lista será percorrida até o final quando chegar ao final os devidos apontamentos serão feitos
		//Lembrando que o usuário nunca vai ser duplicada, porque cada usuário cadastrado receberá um ID único
		while(aux->prox !=NULL)aux = aux->prox;

		aux->prox = novo;
		novo->ant = aux;
	}
	return L;
}

//Função que insere na lista de amigos
no *insereAmigo(no *L, int id, int idAmigo)
{
    no *aux = L;
    no *aux2 = L;
    no *auxAmigos = NULL;

    no *novo = criaAmigo(idAmigo);

    //Se o id for igual ao id do amigo, sai da função sem fazer nada
    if(id == idAmigo)
    {
        printf("Usuario igual\n");
        return L;
    }

    //Se L for igual a null ou seja não existir nenhum usuário cadastrado, não faz nada
    if(L == NULL)
    {
        printf("Usuario nao encontrado\n");
        return L;
    }

    //senão
    else
    {	//percorre a lista até o final ou até encontrar o usuário que receberá o amigo
        while(aux != NULL && aux->id != id)
        {
            aux = aux->prox;
        }

        //percorre a lista até o final ou até encontrar o usuário que será cadastrado como amigo
        while(aux2 != NULL && aux2->id != idAmigo)
        {
            aux2 = aux2->prox;
        }

        //Se chegar no final da lista, ou seja, o id não for encontrado printa uma mensagem e sai da função
        if(aux == NULL || aux2 == NULL)
        {
            printf("Usuario nao encontrado\n");
            return L;
        }

        //Uma auxiliar receberá o ponteiro filho, se ele for null somente insere novo
        auxAmigos = aux->listaAmigos;
        if(auxAmigos == NULL)
        {
            aux->listaAmigos = novo;

        }

        //senão
        else
        {
        	//percorre a lista de amigo até o final ou encontrar o amigo que está sendo solicitado o cadastro
            while(auxAmigos->prox != NULL && auxAmigos->id != idAmigo)
            {
                auxAmigos = auxAmigos->prox;
            }
            //Se o amigo ja estiver o cadastro printa uma mensagem e sai da funcao
            if(auxAmigos->id == idAmigo)
                {
                    printf("Amigo ja cadastrado\n");
                    return L;
                }

            //Senao insere o amigo no final
            auxAmigos->prox = novo;
            novo->ant = auxAmigos;

        }

        return L;
    }
}

//Função que busca os usuários
void buscaUsuario(no *L, int id)
{
	no *aux = L;
    no *auxAmigos = NULL;

    //Com o auxilio de um auxiliar percorre até achar o usuário ou NULL
	while (aux != NULL && aux->id != id)
	{
		aux = aux->prox;
	}

	//Se achar o usuário, printa os dados e entra no loop com auxilio de outra auxiliar
	//e printa todos os amigos da lista de amigos
	if(aux!=NULL && aux->id == id)
    {
        printf("Seu nome: %s\n", aux->nome);
		printf("Sua idade: %d \n", aux->idade);
		printf("Seu email: %s\n", aux->email);
		printf("Seu id: %d\n", aux->id);


        printf("Amigos: \n");
        auxAmigos = aux->listaAmigos;
        while(auxAmigos != NULL)
        {
            printf("%d\n",auxAmigos->id);
            auxAmigos = auxAmigos->prox;
        }
    }
    //Senao printa usuario nao encontrado
    else printf("Usuario nao encontrado\n");
}

//Função que exclui amizades
no *excluiAmizade(no *L, int id, int idAmigo)
{
    no *aux = L;
    no *aux2 = L;
    no *auxAmigos = NULL;
    //Se nenhum usuario estiver cadastrado, sai da função
    if(L == NULL)
    {
        printf("Nenhum usuario cadastrado\n");
        return L;
    }
    //senao
    else
    {
    	//entra no loop e percorre ate achar o usuario
        while(aux != NULL && aux->id != id)
        {
            aux = aux->prox;
        }

        //entra no loop e percorre até achar o id do amigo que esta sendo excluido
        while(aux2 != NULL && aux2->id != idAmigo)
        {
            aux2 = aux2->prox;
        }

        //Se não forem achados um dos ID's sai da função
        if(aux == NULL || aux2 == NULL)
        {
            printf("Usuario nao encontrado\n");
            return L;
        }

        //senao
        else
        {	//auxiliar recebe o topo da lista de amigos e percorre até achar o amigo
            auxAmigos = aux->listaAmigos;
            while(auxAmigos->prox != NULL && auxAmigos->id != idAmigo)
            {
                auxAmigos = auxAmigos->prox;
            }

            //Se amigo nao for encontrado, sai da função
            if(auxAmigos == NULL)
            {
                printf("Amizade nao encontrada\n");
                return L;
            }
            //senao
            else{//se amigo foi encontrado faz os apontamentos necessario para retirar o amigo da lista.
                if(auxAmigos != NULL &&auxAmigos->id == idAmigo)
                {
                    if(auxAmigos->ant != NULL)auxAmigos->ant->prox = auxAmigos->prox;
                    else aux->listaAmigos = auxAmigos->prox;

                    if(auxAmigos->prox !=NULL)auxAmigos->prox->ant = auxAmigos->ant;
                    else aux->listaAmigos = auxAmigos->ant;
                }
            }
        }
    }
    return L;
}

//função que exclui um usuário
no* excluiUsuario(no *L, int id)
{
	no *aux = L;
    no *auxAmigos = NULL;

    //percorre a lista até achar o usuario
	while (aux != NULL && aux->id != id)
	{
		aux = aux->prox;
	}

	//se achar o usuario um auxiliar recebe o topo das listas e percorre a lista de amigos chamando a função de remover amigos
	//Isso retira o usuario que está excluindo a conta da lista de cada um dos seus amigos.
	if(aux!=NULL && aux->id == id)
    {
        auxAmigos = aux->listaAmigos;
        while(auxAmigos != NULL)
        {
            excluiAmizade(L,auxAmigos->id,id);
            auxAmigos = auxAmigos->prox;
        }
        aux->listaAmigos = NULL;//aponta a lista de amigos pra NULL
        free(auxAmigos);//libera o ponteiro que estava apontando para a lista de amigos

        //faz os devidos apontamentos para excluir o usuario da lista de usuarios.
        if(aux->ant == NULL)L = aux->prox;
        else aux->ant->prox = aux->prox;
        if(aux->prox != NULL)aux->prox->ant = aux->ant;
        free(aux);

    }
    //senao, printa uma mensagem e retorna a lista se modificá-la
    else printf("Usuario nao encontrado\n");

    return L;
}

//funcao que compara amizades
void comparaAmizades(no *L, int id, int idAmigo)
{
    no *aux = L;
    no *aux2 = L;
    no *auxAmigos = NULL;
    no *auxAmigos2 = NULL;

    //percorre a lista pra achar o primeiro usuario
    while (aux != NULL && aux->id != id)
	{
		aux = aux->prox;
	}

	//percorre a lista para achar o segundo usuario
    while (aux2 != NULL && aux2->id != idAmigo)
	{
		aux2 = aux2->prox;
	}

	//se um dos dois usuarios nao existirem, sai da funcao
	if(aux == NULL || aux2 == NULL)
        {
            printf("Usuario nao encontrado\n");
            return 0;
        }

    //se os dois usuarios forem encontrados uma auxiliar recebe a lista de amigos do primeiro usuario
    //entra no loop e ao iniciar o primeiro loop uma segunda auxiliar recebe a lista de amigos do segundo usuario
   	//assim, entre num segundo loop que percorrerá a lista de amigos do segundo usuario e compara com o primeiro usuario
    //se forem iguais, printa os amigos em comum
	if(aux!=NULL && aux->id == id && aux2!=NULL && aux2->id == idAmigo)
    {

        printf("Amigos em comum: \n");
        auxAmigos = aux->listaAmigos;
        while(auxAmigos != NULL)
        {
            auxAmigos2 = aux2->listaAmigos;
            while(auxAmigos2 != NULL)
            {
                if(auxAmigos->id == auxAmigos2->id)printf("%d\n",auxAmigos->id);
                auxAmigos2 = auxAmigos2->prox;
            }
            auxAmigos = auxAmigos->prox;
        }
    }
    //senao, printa usuario nao encontrado
    else printf("Usuario nao encontrado\n");

}


int main(int argc, char const *argv[])
{
	no *L;
	L = NULL;


	int id = 1, idade, escolha = 0, idBusca, idBuscaAmigo;
	char nome[100], email[100], enter;

	//enquanto o usuario do programa nao digitar um sete o programa continua em funcionamento
    while(escolha != 7)
    {
    	//printa o menu e escolhe uma das opções
    	printf("\n");
        printf("1 - Busca usuario \n2 - Cria novo usuario \n3 - Exclui usuario \n4 - Cadastra amizade \n5 - Lista amigos em comum \n6 - Exclui amizade \n7 - Sair\n");
        printf("Digite sua escolha: ");
        scanf("%d", &escolha);
        printf("\n");
        setbuf(stdin, NULL);

        //entra num switch, e dentro dele dependendo da escolha pede os parâmetros, e chama a função que o usuário escolheu
        switch (escolha)
        {
            case 1:
                printf("Escolha o usuario a ser buscado: \n");
                scanf("%d", &idBusca);
                buscaUsuario(L, idBusca);
                break;

            case 2:
                printf("Seu nome: ");
                scanf("%[^\n]",nome);
                scanf("%c",&enter);

                printf("Sua idade : ");
                scanf("%d", &idade);
                scanf("%c",&enter);

                printf("Seu email: ");
                scanf("%[^\n]",email);
                scanf("%c",&enter);
                L = insereFinal(L, id, nome, idade, email);
                printf("Seu ID: %d (lembre-se dele)\n",id);
                id++;
                break;


            case 3:
                printf("Escolha o usuario a ser excluido: \n");
                scanf("%d", &idBusca);
                excluiUsuario(L, idBusca);
                break;


            case 4:
                printf("Escolha o usuario a ser buscado: \n");
                scanf("%d", &idBusca);
                printf("Escolha o amigo a ser cadastrado: \n");
                scanf("%d", &idBuscaAmigo);
                L = insereAmigo(L, idBusca, idBuscaAmigo);//importante salientar, que em funções que necessitam de reciprocidade eu chamo a função duas vezes com parametros invertidos
                L = insereAmigo(L, idBuscaAmigo, idBusca);
                break;

            case 5:
                printf("Escolha o usuario a ser buscado: \n");
                scanf("%d", &idBusca);
                printf("Escolha o amigo a ser buscado: \n");
                scanf("%d", &idBuscaAmigo);
                comparaAmizades(L,idBusca,idBuscaAmigo);
                break;

            case 6:
                printf("Escolha o usuario a ser buscado: \n");
                scanf("%d", &idBusca);
                printf("Escolha o amigo a ser buscado: \n");
                scanf("%d", &idBuscaAmigo);
                L = excluiAmizade(L, idBusca, idBuscaAmigo);
                L = excluiAmizade(L, idBuscaAmigo, idBusca);
                break;

        }

    }

	return 0;
}
