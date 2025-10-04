// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.

#include <stdbool.h>
#include <stdio.h>    // Para entrada/saída (printf, scanf)
#include <stdlib.h>   // Para funções de propósito geral (system)
#include <string.h>   // Para manipulação de strings (strcpy, strcmp, strcspn)

// --- Definição da Struct Item ---
typedef struct {
    char nome[30];      // Nome do item (ex: Faca, Bala .45)
    char tipo[20];      // Tipo do item (ex: arma, municao, cura, ferramenta)
    int quantidade;     // Quantidade em estoque
} Item;

// --- Constantes e Protótipos ---
#define MAX_ITENS 10 

void inserirItem(Item mochila[], int *qtd);
void removerItem(Item mochila[], int *qtd);
void listarItensTabular(const Item mochila[], int qtd); // Renomeada/Corrigida
int buscarItem(const Item mochila[], int qtd, const char nomeBusca[]);
void exibir_menu(int qtd_atual); 

// ====================================================================
// FUNÇÃO PRINCIPAL
// ====================================================================
int main() {
    Item inventario[MAX_ITENS];
    int quantidadeAtual = 0; 
    int opcao;

    // A MENSAGEM DE INTRODUCAO É EXIBIDA AQUI
    printf("============================================\n");
    printf("   MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
    printf("============================================\n");

    // Laço principal do menu
    do {
        // O MENU AGORA É EXIBIDO AQUI
        exibir_menu(quantidadeAtual);
        
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) { 
            printf("\nERRO: Entrada invalida. Tente novamente.\n");
            while (getchar() != '\n'); 
            opcao = -1;
            continue;
        }

        // --- LÓGICA DE EXECUÇÃO ---
        switch (opcao) {
            case 1:
                inserirItem(inventario, &quantidadeAtual);
                break;
            case 2:
                removerItem(inventario, &quantidadeAtual);
                break;
            case 3:
                // CHAMA A FUNÇÃO DE LISTAGEM TABULAR
                listarItensTabular(inventario, quantidadeAtual); 
                break;
            case 4:
                // Busca de Item 
                { 
                    char nomeBusca[30];
                    printf("\n--- BUSCA DE ITEM ---\n");
                    printf("Nome do item para busca: ");
                    while (getchar() != '\n'); 
                    fgets(nomeBusca, 30, stdin);
                    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

                    int indice = buscarItem(inventario, quantidadeAtual, nomeBusca);
                    
                    if (indice != -1) {
                        printf("\n[SUCESSO] Item encontrado na posicao %d:\n", indice + 1);
                        printf("  > Nome: %s\n", inventario[indice].nome);
                        printf("  > Tipo: %s\n", inventario[indice].tipo);
                        printf("  > Quantidade: %d\n", inventario[indice].quantidade);
                    } else {
                        printf("\n[ALERTA] O item '%s' nao foi encontrado na mochila.\n", nomeBusca);
                    }
                }
                break;
            case 0:
                printf("\nEncerrando o sistema de inventario. Boa sorte no jogo!\n");
                break;
            default:
                printf("\n[ALERTA] Opcao invalida! Escolha de 0 a 3.\n");
                break;
        }
        
        // Listagem após operacoes de adicao ou remocao
        if (opcao == 1 || opcao == 2) {
            listarItensTabular(inventario, quantidadeAtual);
        }

        // --- PAUSA E LIMPEZA DE TELA ---
        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            while (getchar() != '\n'); // Limpa o buffer
            getchar(); // Espera a tecla Enter
            
            #ifdef _WIN32
                system("cls"); // Comando mais comum para Windows
            #else
                system("clear"); // Comando para Linux/macOS
            #endif
        }
        
    } while (opcao != 0);

    return 0;
}

// ====================================================================
// FUNÇÕES DE UTILIDADE E OBRIGATÓRIAS
// ====================================================================

/**
 * Exibe o menu de opcoes do inventario no formato solicitado.
 */
void exibir_menu(int qtd_atual) {
    printf("Itens na Mochila: %d/%d\n\n", qtd_atual, MAX_ITENS);
    printf("1. Adicionar Item (Loot)\n");
    printf("2. Remover Item\n");
    printf("3. Listar Itens na Mochila\n");
    printf("0. Sair\n");
    printf("--------------------------------------------\n");
}


void inserirItem(Item mochila[], int *qtd) {
    printf("\n--- Adicionar Novo Item ---\n");
    
    if (*qtd >= MAX_ITENS) {
        printf("[ALERTA] Mochila cheia! Capacidade maxima (%d) atingida.\n", MAX_ITENS);
        return;
    }

    printf("Nome do item: ");
    while (getchar() != '\n'); 
    fgets(mochila[*qtd].nome, 30, stdin);
    mochila[*qtd].nome[strcspn(mochila[*qtd].nome, "\n")] = 0;

    printf("Tipo do item (arma, municao, cura, etc.): ");
    fgets(mochila[*qtd].tipo, 20, stdin);
    mochila[*qtd].tipo[strcspn(mochila[*qtd].tipo, "\n")] = 0;

    printf("Quantidade: ");
    while (scanf("%d", &mochila[*qtd].quantidade) != 1 || mochila[*qtd].quantidade <= 0) {
        printf("ERRO: Quantidade invalida. Digite um numero inteiro positivo: ");
        while (getchar() != '\n');
    }
    
    (*qtd)++; 
    printf("\nItem '%s' adicionado com sucesso!\n", mochila[*qtd - 1].nome);
}


void removerItem(Item mochila[], int *qtd) {
    if (*qtd == 0) {
        printf("\n[ALERTA] A mochila esta vazia. Nada para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("\n--- REMOCAO DE ITEM ---\n");
    printf("Nome do item para remover: ");
    while (getchar() != '\n');
    fgets(nomeRemover, 30, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = 0;

    int indice = buscarItem(mochila, *qtd, nomeRemover);

    if (indice == -1) {
        printf("\n[ALERTA] O item '%s' nao foi encontrado para remocao.\n", nomeRemover);
        return;
    }

    // Deslocamento dos elementos
    for (int i = indice; i < *qtd - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    (*qtd)--;

    printf("\n[SUCESSO] O item '%s' foi removido com sucesso da mochila.\n", nomeRemover);
}


/**
 * Implementa a listagem tabular, corrigindo a formatação e o especificador.
 */
void listarItensTabular(const Item mochila[], int qtd) {
    printf("\n--- ITENS NA MOCHILA (%d/%d) ---\n", qtd, MAX_ITENS);
    
    if (qtd == 0) {
        printf("[VAZIA] A mochila nao contem nenhum item no momento.\n");
        return;
    }
    
    // Cabeçalho da tabela com espaçamento ajustado
    printf("%-30s | %-12s | %-12s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("------------------------------|--------------|--------------\n");

    // Impressão dos itens em formato tabular
    for (int i = 0; i < qtd; i++) {
        // Usa largura fixa para as colunas: Nome (-30s), Tipo (-12s), Quantidade (-12d)
        printf("%-30s | %-12s | %-12d\n", 
            mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("----------------------------------------------------------------\n");
}

/**
 * Realiza a busca sequencial por um item na mochila com base no nome.
 */
int buscarItem(const Item mochila[], int qtd, const char nomeBusca[]) {
    for (int i = 0; i < qtd; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            return i; // Item encontrado, retorna o índice
        }
    }
    return -1; // Item não encontrado
}