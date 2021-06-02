//inclusão do cabeçalho ABB genérica
#include "ABBGen.h"

//estrutura que recebe os dados do clinte
typedef struct usuario
{
    int id;
    int idade;
    float altura, peso;
}usuario;

//função que faz a comparação de duas chaves da arvore, por seu valor de id
int compara(void *info, void *info2)
{

    usuario *aux = (usuario *)info;
    usuario *aux2 = (usuario *)info2;

    if(aux->id > aux2->id) return 1;

    if(aux->id == aux2->id)return 0;

    if(aux->id < aux2->id) return -1;


}

//imprime id(chave) via percurso pre/em/pos ordem

void imprimeChave (void *info)
{
    usuario *user = (usuario *)info;
    printf("%d\t", user->id);
}

//imprime os dados do cliente usando o callback
void imprimeUsuario(void *info)
{
    usuario *user = (usuario *)info;

    printf("Sua idade: %i\n", user->idade);
    printf("Sua altura: %f\n", user->altura);
    printf("Seu peso: %f\n", user->peso);

}

//Função que busca um determinado ID na árvore, e printa todos os seus dados
void buscaID(noABB* raiz, int id)
{
    usuario *info = (usuario *)calloc(1, sizeof(usuario));

    if(!info)
    {
        printf("Erro.\n");
        exit(1);
    }

    info->id = id;


    buscaABB(raiz, info, compara, imprimeUsuario);

}

//insere os dados do cliente na arvore na tad
noABB* insereUser(noABB* raiz, int id, int idade, float peso, float altura)
{
    usuario *user = (usuario *)malloc(sizeof(usuario));

    if(!user)
    {
        printf("Erro.\n");
        exit(1);
    }

    user->id = id;
    user->idade = idade;
    user->altura = altura;
    user->peso = peso;

    return insereABB(raiz, user, compara);
}


noABB* deletaUser(noABB* raiz)
{
    int id;
    printf("digite a ID a ser deletada: ");
    scanf("%d", &id);
    printf("\n");

    usuario *info = (usuario *)calloc(1, sizeof(usuario));



    if(!info)
    {
        printf("Erro.\n");
        exit(1);
    }

    info->id = id;

    return deletaNoABB(raiz, info, compara);
}



//main
int main(int argc, char const *argv[])
{
	noABB *raiz;
    raiz = NULL;
    float altura, peso;
    int idade, id = 0;
    int escolha = 0;
    do
    {
        printf("0 - Sair\n1 - Insere elemento\n2 - Procura elemento\n3 - Deleta elemento\n4 - Imprime Arvore(pre ordem)\n5 - Imprime Arvore(em ordem)\n6 - Imprime Arvore(pos ordem)\n");
        printf("Sua escolha: ");
        scanf("%i", &escolha);
        printf("\n");

        switch(escolha)
        {
            case 1:
                printf("digite sua ID: ");
                scanf("%d", &id);
                printf("\n");

                printf("Digite sua idade(anos): ");
                scanf("%i", &idade);

                printf("Digite sua altura(cm): ");
                scanf("%f", &altura);
                printf("\n");

                printf("Digite o seu peso(kg): ");
                scanf("%f", &peso);
                printf("\n");

                raiz = insereUser(raiz, id, idade, peso, altura);
                break;

            case 2:

                printf("digite a ID a ser procurada: ");
                scanf("%d", &id);
                printf("\n");
                buscaID(raiz, id);
                break;

            case 3:
                deletaUser(raiz);
                break;

            case 4:
                preOrdem(raiz, 0, imprimeChave);
                break;

            case 5:
                emOrdem(raiz, 0, imprimeChave);
                break;

            case 6:
                posOrdem(raiz, 0, imprimeChave);
                break;

            case 0:
                deletaABB(raiz);
                break;
        }

    }while(escolha != 0);



	return 0;
}
