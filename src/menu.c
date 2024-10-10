#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>  // Para a função Sleep() no Windows
#else
#include <unistd.h>  // Para a função usleep() no Unix/Linux
#endif

// Estrutura para armazenar os itens do inventário
typedef struct {
    int id;
    char nome[50];
    char descricao[100];
    float preco;
    int quantidade;
    char data_criacao[11];  // Formato "dd/mm/aaaa"
} Item;

// Protótipos das funções
void adicionarItem(Item **inventario, int *numItens);
void listarItens(Item *inventario, int numItens);
Item* buscarItem(Item *inventario, int numItens, int id);
void editarItem(Item *item);
void deletarItem(Item **inventario, int *numItens);

// Função para a animação da caixa
void animacaoCaixa() {
    printf("Abrindo a caixa...\n");
    for (int i = 0; i < 5; i++) {
        printf("|\n");  // Simula a "altura" da caixa
#ifdef _WIN32
        Sleep(300);  // Espera 300 milissegundos no Windows
#else
        usleep(300000);  // Espera 300 milissegundos no Unix/Linux
#endif
    }
    printf("A caixa esta aberta!\n\n");
    Sleep(1000);  // Espera 1 segundo antes de mostrar o menu
}

// Implementação da função para adicionar um item
void adicionarItem(Item **inventario, int *numItens) {
    *inventario = realloc(*inventario, (*numItens + 1) * sizeof(Item));
    if (*inventario == NULL) {
        printf("Erro ao adicionar item\n");
        return;
    }

    Item *novoItem = &(*inventario)[*numItens];  // Apontar para o novo item
    printf("Digite o ID do item: ");
    scanf("%d", &novoItem->id);
    printf("Digite o nome do item: ");
    scanf(" %[^\n]", novoItem->nome);
    printf("Digite a descricao do item: ");
    scanf(" %[^\n]", novoItem->descricao);
    printf("Digite o preco do item: ");
    scanf("%f", &novoItem->preco);
    printf("Digite a quantidade do item: ");
    scanf("%d", &novoItem->quantidade);
    printf("Digite a data de criacao (dd/mm/aaaa): ");
    scanf(" %[^\n]", novoItem->data_criacao);
    
    (*numItens)++;  // Incrementa o número de itens
    printf("Item adicionado com sucesso!\n");
}

// Implementação da função para listar itens
void listarItens(Item *inventario, int numItens) {
    if (numItens == 0) {
        printf("Nenhum item cadastrado!\n");
        return;
    }
    for (int i = 0; i < numItens; i++) {
        Item *item = &inventario[i];
        printf("ID: %d\n", item->id);
        printf("Nome: %s\n", item->nome);
        printf("Descricao: %s\n", item->descricao);
        printf("Preco: %.2f\n", item->preco);
        printf("Quantidade: %d\n", item->quantidade);
        printf("Data de criacao: %s\n", item->data_criacao);
        printf("-----------------------------------\n");
    }
}

// Implementação da função para buscar um item
Item* buscarItem(Item *inventario, int numItens, int id) {
    for (int i = 0; i < numItens; i++) {
        if (inventario[i].id == id) {
            return &inventario[i];  // Retorna o item encontrado
        }
    }
    return NULL;  // Retorna NULL se não encontrado
}

// Implementação da função para editar um item
void editarItem(Item *item) {
    printf("Editando item: %s\n", item->nome);
    printf("Digite o novo nome do item: ");
    scanf(" %[^\n]", item->nome);
    printf("Digite a nova descricao do item: ");
    scanf(" %[^\n]", item->descricao);
    printf("Digite o novo preco do item: ");
    scanf("%f", &item->preco);
    printf("Digite a nova quantidade do item: ");
    scanf("%d", &item->quantidade);
    printf("Item editado com sucesso!\n");
}

// Implementação da função para deletar um item
void deletarItem(Item **inventario, int *numItens) {
    int id;
    printf("Digite o ID do item a ser deletado: ");
    scanf("%d", &id);
    
    for (int i = 0; i < *numItens; i++) {
        if ((*inventario)[i].id == id) {
            // Desloca os itens para preencher a lacuna
            for (int j = i; j < *numItens - 1; j++) {
                (*inventario)[j] = (*inventario)[j + 1];
            }
            (*numItens)--;  // Decrementa o número de itens
            *inventario = realloc(*inventario, (*numItens) * sizeof(Item));
            printf("Item deletado com sucesso!\n");
            return;
        }
    }
    printf("Item nao encontrado.\n");
}

int main() {
    Item *inventario = NULL;  // Ponteiro para o inventário
    int numItens = 0;         // Contador de itens
    int opcao;

    animacaoCaixa();  // Chama a animação da caixa

    do {
        // Exibe o menu de opções
        printf("----- Sistema de Gerenciamento de Inventario -----\n");
        printf("1. Adicionar item\n");
        printf("2. Listar itens\n");
        printf("3. Buscar item por ID\n");
        printf("4. Editar item\n");
        printf("5. Deletar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        // Lida com a escolha do usuário
        switch(opcao) {
            case 1:
                adicionarItem(&inventario, &numItens);
                break;
            case 2:
                listarItens(inventario, numItens);
                break;
            case 3: {
                int id;
                printf("Digite o ID do item a ser buscado: ");
                scanf("%d", &id);
                Item *item = buscarItem(inventario, numItens, id);
                if (item) {
                    printf("Item encontrado: %s\n", item->nome);
                } else {
                    printf("Item não encontrado.\n");
                }
                break;
            }
            case 4: {
                int id;
                printf("Digite o ID do item a ser editado: ");
                scanf("%d", &id);
                Item *item = buscarItem(inventario, numItens, id);
                if (item) {
                    editarItem(item);
                } else {
                    printf("Item não encontrado.\n");
                }
                break;
            }
            case 5: {
                deletarItem(&inventario, &numItens);
                break;
            }
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while(opcao != 0);

    free(inventario); // Libera a memória alocada
    return 0;
}
