#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#ifdef _WIN32
#include <windows.h>  // Para a função Sleep() no Windows
#else
#include <unistd.h>  // Para a função usleep() e sleep() no Unix/Linux
#endif

// Estrutura para armazenar os itens do inventário
typedef struct {
    int id;
    char nome[50];
    char descricao[100];
    float preco;
    int quantidade;
    char data_criacao[20];      // Formato "dd/mm/aaaa hh:mm"
    char data_atualizacao[20];   // Formato "dd/mm/aaaa hh:mm"
} Item;

// Variável global para o próximo ID único
int proximoId = 1;

// Protótipos das funções
void limparConsole();
void obterDataHoraAtual(char *dataHora);
void solicitarPrecoItem(Item *item);
void solicitarQuantidadeItem(Item *item);
void adicionarNovoItem(Item **inventario, int *numItens);
void exibirListaItens(Item *inventario, int numItens);
Item* procurarItemPorID(Item *inventario, int numItens, int id);
void editarDadosItem(Item *item);
void removerItemPorID(Item **inventario, int *numItens);
void exibirItemPorID(Item *inventario, int numItens);
int exibirMenu();
void iniciarSistemaInventario();

// Função para limpar o console
void limparConsole() {
    #ifdef _WIN32
        system("cls");  // Comando para Windows
    #else
        system("clear");  // Comando para Unix/Linux/macOS
    #endif
}

// Função para obter a data e hora atual no formato dd/mm/aaaa hh:mm
void obterDataHoraAtual(char *dataHora) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(dataHora, "%02d/%02d/%04d %02d:%02d", 
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);
}

// Funções para entrada de dados com validação
void solicitarPrecoItem(Item *item) {
    int validInput;
    do {
        printf("Digite o preço do item (em R$, use ponto para decimais, ex: R$ 3.50): R$ ");
        validInput = scanf("%f", &item->preco);
        if (validInput != 1 || item->preco < 0) {
            printf("Erro: Preço inválido. Insira um valor numérico não negativo, usando ponto para decimais.\n");
            while (getchar() != '\n');  // Limpa o buffer de entrada
        }
    } while (validInput != 1 || item->preco < 0);
}

void solicitarQuantidadeItem(Item *item) {
    int validInput;
    do {
        printf("Digite a quantidade do item (não negativa): ");
        validInput = scanf("%d", &item->quantidade);
        if (validInput != 1 || item->quantidade < 0) {
            printf("Erro: Quantidade inválida. Insira um número inteiro não negativo.\n");
            while (getchar() != '\n');  // Limpa o buffer de entrada
        }
    } while (validInput != 1 || item->quantidade < 0);
}

// Função para adicionar um novo item ao inventário
void adicionarNovoItem(Item **inventario, int *numItens) {
    limparConsole();
    *inventario = realloc(*inventario, (*numItens + 1) * sizeof(Item));
    if (*inventario == NULL) {
        printf("Erro ao adicionar item\n");
        return;
    }

    Item *novoItem = &(*inventario)[*numItens];
    novoItem->id = proximoId++;  // Atribui o próximo ID único e incrementa

    printf("Digite o nome do item: ");
    scanf(" %[^\n]", novoItem->nome);
    printf("Digite a descrição do item: ");
    scanf(" %[^\n]", novoItem->descricao);
    solicitarPrecoItem(novoItem);
    solicitarQuantidadeItem(novoItem);
    
    obterDataHoraAtual(novoItem->data_criacao);
    strcpy(novoItem->data_atualizacao, novoItem->data_criacao);

    (*numItens)++;
    limparConsole();
    printf("Item adicionado com sucesso!\n");
    printf("ID: %d\nNome: %s\nDescrição: %s\n", novoItem->id, novoItem->nome, novoItem->descricao);
    printf("Preço: R$ %.2f\nQuantidade: %d\n", novoItem->preco, novoItem->quantidade);
    printf("Data de criação: %s\n\n", novoItem->data_criacao);
}

// Função para exibir a lista de itens no inventário
void exibirListaItens(Item *inventario, int numItens) {
    limparConsole();
    if (numItens == 0) {
        printf("Nenhum item cadastrado!\n\n");
        return;
    }

    printf("========== Lista de Itens no Inventário ==========\n\n");
    for (int i = 0; i < numItens; i++) {
        Item *item = &inventario[i];
        printf("ID: %d\nNome: %s\nDescrição: %s\n", item->id, item->nome, item->descricao);
        printf("Preço: R$ %.2f\nQuantidade: %d unidades\n", item->preco, item->quantidade);
        printf("Data de Criação: %s\nData de Última Atualização: %s\n", item->data_criacao, item->data_atualizacao);
        printf("-------------------------------------------\n");
    }
    printf("=========== Fim da Lista de Itens ==========\n\n");
}

// Função para procurar item por ID
Item* procurarItemPorID(Item *inventario, int numItens, int id) {
    for (int i = 0; i < numItens; i++) {
        if (inventario[i].id == id) {
            return &inventario[i];
        }
    }
    return NULL;
}

// Função para editar os dados de um item
void editarDadosItem(Item *item) {
    limparConsole();
    printf("Editando item: %s\n", item->nome);
    printf("Digite o novo nome do item: ");
    scanf(" %[^\n]", item->nome);
    printf("Digite a nova descrição do item: ");
    scanf(" %[^\n]", item->descricao);
    solicitarPrecoItem(item);
    solicitarQuantidadeItem(item);
    
    obterDataHoraAtual(item->data_atualizacao);
    limparConsole();
    printf("Item editado com sucesso!\nID: %d\nNome: %s\nDescrição: %s\n", item->id, item->nome, item->descricao);
    printf("Preço: R$ %.2f\nQuantidade: %d\n", item->preco, item->quantidade);
    printf("Data de atualização: %s\n\n", item->data_atualizacao);
}

// Função para remover um item por ID
void removerItemPorID(Item **inventario, int *numItens) {
    limparConsole();
    int id;
    printf("Digite o ID do item a ser deletado: ");
    scanf("%d", &id);
    
    for (int i = 0; i < *numItens; i++) {
        if ((*inventario)[i].id == id) {
            for (int j = i; j < *numItens - 1; j++) {
                (*inventario)[j] = (*inventario)[j + 1];
            }
            (*numItens)--;
            *inventario = realloc(*inventario, (*numItens) * sizeof(Item));
            limparConsole();
            printf("Item deletado com sucesso!\n\n");
            return;
        }
    }
    printf("Item não encontrado.\n\n");
}

// Função para exibir o item por ID
void exibirItemPorID(Item *inventario, int numItens) {
    limparConsole();
    int id;
    printf("Digite o ID do item a ser buscado: ");
    scanf("%d", &id);
    Item *item = procurarItemPorID(inventario, numItens, id);
    if (item) {
        limparConsole();
        printf("Item encontrado:\n");
        printf("ID: %d\nNome: %s\nDescrição: %s\n", item->id, item->nome, item->descricao);
        printf("Preço: R$ %.2f\nQuantidade: %d unidades\n", item->preco, item->quantidade);
        printf("Data de Criação: %s\nData de Última Atualização: %s\n\n", item->data_criacao, item->data_atualizacao);
    } else {
        printf("Item não encontrado.\n\n");
    }
}

// Função para exibir o menu
int exibirMenu() {
    printf("----- Sistema de Gerenciamento de Inventário -----\n");
    printf("1. Adicionar item\n");
    printf("2. Exibir lista de itens\n");
    printf("3. Exibir item por ID\n");
    printf("4. Editar item\n");
    printf("5. Remover item\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
    int opcao;
    scanf("%d", &opcao);
    return opcao;
}

// Função principal do sistema de inventário
void iniciarSistemaInventario() {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);  // Define UTF-8 no console do Windows
    #endif
    setlocale(LC_ALL, "pt_BR.UTF-8"); 

    
    Item *inventario = NULL;
    int numItens = 0;
    int opcao;

    do {
        limparConsole();
        opcao = exibirMenu();
        
        switch(opcao) {
            case 1:
                adicionarNovoItem(&inventario, &numItens);
                break;
            case 2:
                exibirListaItens(inventario, numItens);
                break;
            case 3:
                exibirItemPorID(inventario, numItens);
                break;
            case 4: {
                int id;
                printf("Digite o ID do item a ser editado: ");
                scanf("%d", &id);
                Item *item = procurarItemPorID(inventario, numItens, id);
                if (item) editarDadosItem(item);
                else printf("Item não encontrado.\n\n");
                break;
            }
            case 5:
                removerItemPorID(&inventario, &numItens);
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n\n");
        }

        if (opcao != 0) {
            printf("Pressione Enter para voltar ao menu principal...");
            while (getchar() != '\n'); // Limpa o buffer de entrada
            getchar(); // Aguarda o Enter do usuário
        }
    } while(opcao != 0);

    free(inventario);
}

// Função principal
int main() {
    iniciarSistemaInventario();
    return 0;
}
