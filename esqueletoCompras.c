/*
 Este é um esqueleto que deve ser utilizado como base para implementação do trabalho;
     - As funções não têm os parâmetros definidos; se necessário, estes devem ser incluídos; Os tipos de retorno podem ser alterados, se necessário;
     - Devem ser respeitados os nomes atribuídos às funções e estruturas, porém, novas estruturas e funções podem ser criadas, caso julgue necessário;
     - Faça os includes necessários;
     - A organização das funções fica a critério do programador;
     - A indentação correta faz parte da nota;
     - Não são permitidas variáveis globais;
     - Caso seja detectado plágio, os grupos envolvidos receberão nota 0.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define EXIT 10 // valor fixo para a opção que finaliza a aplicação

// Struct que representa um item de uma lista de compras armazenada em uma arvore binaria de busca
struct item
{
    char produto[50];
    int quantidade;
    struct item *esquerdo;
    struct item *direito;
};
typedef struct item Item;

struct itemLista
{
    char produto[50];
    struct lista *proximo;
};
typedef struct itemLista ItemLista;

struct lista
{
    struct itemLista *primeiro;
};
typedef struct lista Lista;

// Apresenta o primeiro menu da aplicação e retorna a opção selecionada
int menu1()
{
    int op = 0;
    printf("\nMenu principal\n");
    // complete com as demais opcoes...
    printf("1-Gerenciar lista de compras A\n");
    printf("2-Gerenciar lista de compras B\n");
    printf("3-Visualizar itens duplicados\n");
    printf("%d-Sair do programa", EXIT);
    printf("\nDigite a opcao: ");
    scanf("%d", &op);
    return op;
}

// Apresenta o segundo menu da aplicação e retorna a opção selecionada
int menu2()
{
    int op = 0;
    printf("Submenu - Gerenciar lista de compras\n");
    // complete com as demais opcoes...
    printf("1-Inserir item na lista de compras\n");
    printf("2-Pesquisar produto na lista de compras\n");
    printf("3-Atualizar a quantidade de um produto na lista de compras\n");
    printf("4-Listar todos os itens da lista de compras em ordem alfabetica\n");
    printf("5-Deletar item da lista de compras\n");
    printf("%d-Retornar para o menu principal", EXIT);
    printf("\nDigite a opcao: ");
    scanf("%d", &op);
    return op;
}

// Permite o cadastro de um item (caso o produto ainda não exista) em uma lista de compras
Item *insert(Item *item, char produto[50], int quant)
{
    // printf("inserindo");
    if (item == NULL)
    {
        Item *new = malloc(sizeof(Item));
        for (int i = 0; produto[i]; i++)
        {
            produto[i] = tolower(produto[i]);
        }
        strcpy(new->produto, produto);
        new->quantidade = quant;
        new->direito = new->esquerdo = NULL;
        return new;
    }

    else
    {
        if (strcmp((item->produto), (produto)) >= 0)
            item->esquerdo = insert(item->esquerdo, produto, quant);
        else
            item->direito = insert(item->direito, produto, quant);
        return item;
    }
}

// Permite consultar se um item está em uma lista de compras
Item *query(Item *item, char produto[50])
{
    // printf("pesquisando");
    if (item)
    {
        if (strcmp(item->produto, produto) > 0)
            return query(item->esquerdo, produto);
        else if (strcmp(item->produto, produto) < 0)
            return query(item->direito, produto);
        else
        {

            return item;
        }
    }
    return NULL;
}

// Permite excluir um item de uma lista de compras
Item *delete(Item *item, char produto[50])
{
    if (query(item, produto) == NULL)
    {
        printf("\nItem nao encontrado!!!");
        return NULL;
    }
    if (item == NULL)
    {
        printf("\nItem nao encontrado!!!");
        return NULL;
    }
    else
    {
        if (strcmp(item->produto, produto) == 0)
        {
            if (item->esquerdo == NULL && item->direito == NULL)
            {
                free(item);
                return NULL;
            }
            else
            {
                if (item->esquerdo != NULL && item->direito != NULL)
                {
                    Item *aux = item->esquerdo;
                    while (aux->direito != NULL)
                        aux = aux->direito;
                    strcpy(item->produto, aux->produto);
                    item->quantidade = aux->quantidade;
                    strcpy(aux->produto, produto);
                    printf("Elemento trocado: %s !\n", produto);
                    item->esquerdo = delete (item->esquerdo, produto);
                    return item;
                }
                else
                {
                    Item *aux;
                    if (item->esquerdo != NULL)
                        aux = item->esquerdo;
                    else
                        aux = item->direito;
                    free(item);
                    printf("Item removido: %s !\n", produto);
                    return aux;
                }
            }
        }
        else
        {
            if (strcmp((item->produto), (produto)) > 0)
                item->esquerdo = delete (item->esquerdo, produto);
            else
                item->direito = delete (item->direito, produto);
            return item;
        }
    }
}

// Permite a atualização da quantidade de um produto (caso exista) na lista de compras
Item *update(Item *item, char produto[50], int quant)
{
    // printf("atualizando");
    if (item != NULL)
    {
        if (quant <= 0)
        {
            return delete (item, produto);
        }
        else
        {
            if (strcmp(item->produto, produto) > 0)
                update(item->esquerdo, produto, quant);
            else if (strcmp(item->produto, produto) < 0)
                update(item->direito, produto, quant);
            else
            {
                item->quantidade = quant;
                return item;
            }
        }
    }

    return NULL;
}

// Listar todos os itens da lista de compras em ordem alfabética;
void list(Item *item)
{
    if (item == NULL)
        return;

    list(item->esquerdo);
    printf("\n%s - (Qtd:%d)", item->produto, item->quantidade);
    list(item->direito);
}

void inicializaLista(Lista *lista)
{
    // inicializa a cabeca e cauda da lista como NULL
    lista->primeiro = NULL;
}
void intersect(Item *itemA, Item *itemB, Lista *lista)
{
    ItemLista *aux;
    aux = malloc(sizeof(ItemLista));

    if (itemA == NULL)
        return;

    intersect(itemA->esquerdo, itemB, lista);
    if (query(itemB, itemA->produto))
    {

        strcpy(aux->produto, itemA->produto);
        aux->proximo = NULL;

        if (lista->primeiro == NULL)
        { // Insercao na lista vazia
            lista->primeiro = aux;
        }
        else
        {
            aux->proximo = lista->primeiro;
            lista->primeiro = aux;
        }
    }
    intersect(itemA->direito, itemB, lista);
}

// Programa principal
int main()
{
    int opcao1;
    int opcao2;
    Item *raizA = NULL;
    Item *raizB = NULL;
    Lista *lista;
    ItemLista *auxi;
    lista = malloc(sizeof(Lista));
    lista->primeiro = NULL;

    opcao1 = 0;
    while (opcao1 != EXIT)
    {
        opcao1 = menu1();

        switch (opcao1)
        {
        case 1: // gerenciar lista de compras A
            opcao2 = 0;
            while (opcao2 != EXIT)
            {
                char produto[50];
                int quant;
                Item *aux;
                printf("\n\n** Lista de Compras A **\n\n");
                opcao2 = menu2();
                switch (opcao2)
                { // operacoes sobre a arvore A
                case 1:

                    printf("Nome do produto:");
                    scanf("%s", produto);

                    printf("Quantidade do produto:");
                    scanf("%d", &quant);
                    if (query(raizA, produto) != NULL)
                    {
                        printf("\nItem ja adicionado!");
                        break;
                    }
                    raizA = insert(raizA, produto, quant);
                    printf("(Produto = %s, Quantidade = %d) adicionado com sucesso!!!", produto, quant);
                    break;
                case 2:
                    printf("Nome do produto:");
                    scanf("%s", produto);
                    if (query(raizA, produto))
                        printf("\n%s esta na sua lista!", produto);
                    else
                        printf("Produto nao encontrado!!!");
                    break;
                case 3:
                    printf("Nome do produto:");
                    scanf("%s", produto);
                    printf("Quantidade do produto:");
                    scanf("%d", &quant);
                    aux = update(raizA, produto, quant);
                    if (aux != NULL)
                        printf("\n%s foi atualizado para quantidade = %d!", produto, quant);
                    else
                        printf("\nProduto nao encontrado!!!");
                    break;
                case 4:
                    if (raizA == NULL)
                        printf("\nLista A vazia!!!");
                    else
                        list(raizA);
                    break;
                case 5:
                    printf("Nome do produto:");
                    scanf("%s", produto);

                    if (delete (raizA, produto) != NULL)
                        printf("\n%s foi deletado de sua lista", produto);
                }
            }
            break;
        case 2: // gerenciar lista de compras B
            // idem ao caso 1, mas para a arvore B
            opcao2 = 0;
            while (opcao2 != EXIT)
            {
                char produto[50];
                int quant;
                Item *aux;
                printf("\n\n** Lista de Compras B **\n\n");
                opcao2 = menu2();
                switch (opcao2)
                { // operacoes sobre a arvore B
                case 1:
                    printf("Nome do produto:");
                    scanf("%s", produto);
                    printf("Quantidade do produto:");
                    scanf("%d", &quant);
                    if (query(raizB, produto) != NULL)
                    {
                        printf("\nItem ja adicionado!");
                        break;
                    }
                    raizB = insert(raizB, produto, quant);
                    printf("(Produto = %s, Quantidade = %d) adicionado com sucesso!!!", produto, quant);
                    break;
                case 2:
                    printf("Nome do produto:");
                    scanf("%s", produto);
                    if (query(raizB, produto))
                        printf("\n%s esta na sua lista!", produto);
                    else
                        printf("Produto nao encontrado!!!");
                    break;
                case 3:
                    printf("Nome do produto:");
                    scanf("%s", produto);
                    printf("Quantidade do produto:");
                    scanf("%d", &quant);
                    aux = update(raizB, produto, quant);
                    if (aux != NULL)
                        printf("\n%s foi atualizado para quantidade = %d!\n", aux->produto, aux->quantidade);
                    else
                        printf("\nProduto nao encontrado!!!");
                    break;
                case 4:
                    if (raizB == NULL)
                        printf("\nLista B vazia!!!");
                    else
                        list(raizB);
                    break;
                case 5:
                    printf("Nome do produto:");
                    scanf("%s", produto);

                    if (delete (raizB, produto) != NULL)
                        printf("\n%s foi deletado de sua lista", produto);
                }
            }
            break;
        case 3: // Visualizar itens duplicados

            intersect(raizA, raizB, lista);
            printf("\nItens duplicados: ");

            for (auxi = lista->primeiro; auxi != NULL; auxi = auxi->proximo)
            {
                printf("%s", auxi->produto);
                (auxi->proximo != NULL) ? printf(", ") : printf(".");
            }
            printf("\n");
            while (lista->primeiro->proximo)
            {
                auxi = lista->primeiro;
                lista->primeiro = lista->primeiro->proximo;
                free(auxi);
            }
            lista->primeiro = NULL;
        }
    }
    return 0;
}
