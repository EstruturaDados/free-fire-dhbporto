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

#include <stdio.h>    // Para entrada/saída (printf, scanf)
#include <stdlib.h>   // Para funções de propósito geral (system)
#include <string.h>   // Para manipulação de strings (strcpy, strcmp)
#include <stdbool.h>

// Define a estrutura para armazenar as informações de cada item do inventário.
typedef struct {
    char nome[30];      // Nome do item (ex: Faca, Bala .45)
    char tipo[20];      // Tipo do item (ex: arma, municao, cura, ferramenta)
    int quantidade;     // Quantidade em estoque
} Item;

// Definição do Tamanho Máximo da Lista
#define MAX_ITENS 10 // A mochila virtual suporta ate 10 itens distintos.

// Protótipos das Funções
void inserirItem(Item mochila[], int *qtd);
void removerItem(Item mochila[], int *qtd);
void listarItens(const Item mochila[], int qtd);
int buscarItem(const Item mochila[], int qtd, const char nomeBusca[]);
void menu();

// ====================================================================
// FUNÇÃO PRINCIPAL
// ====================================================================
int main() {
    // Vetor de Structs: Representa a lista sequencial (mochila)
    Item inventario[MAX_ITENS];
    // Variável de controle: Armazena a quantidade atual de itens na mochila
    int quantidadeAtual = 0; 
    int opcao;

    // Mensagem inicial sem acentos
    printf("--- INVENTARIO (MOCHILA INICIAL) ---\n");
    printf("Prepare-se para o jogo! Gerencie seus primeiros 10 itens.\n");

    // Laço principal do menu
    do {
        menu();
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) { 
            printf("\nERRO: Entrada invalida. Tente novamente.\n");
            while (getchar() != '\n'); 
            opcao = -1;
            continue;
        }

        switch (opcao) {
            case 1:
                inserirItem(inventario, &quantidadeAtual);
                break;
            case 2:
                removerItem(inventario, &quantidadeAtual);
                break;
            case 3:
                listarItens(inventario, quantidadeAtual);
                break;
            case 4:
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
                printf("\n[ALERTA] Opcao invalida! Escolha de 0 a 4.\n");
                break;
        }
        
        // Listagem apos cada operacao (exceto na busca e saida)
        if (opcao != 3 && opcao != 4 && opcao != 0) {
            listarItens(inventario, quantidadeAtual);
        }

        // Comando para limpar a tela e pausar (melhora a usabilidade)
        #ifdef _WIN32
            system("pause"); // Para Windows
        #else
            system("read -p 'Pressione Enter para continuar...' x"); // Para Linux/macOS
        #endif
        system("clear"); // Limpa o console
        
    } while (opcao != 0);

    return 0;
}

// ====================================================================
// FUNÇÕES OBRIGATÓRIAS
// ====================================================================

/**
 * Exibe o menu de opcoes do inventario (sem acentos).
 */
void menu() {
    printf("\n######################################\n");
    printf("  MOCHILA - DECISOES ESTRATEGICAS\n");
    printf("######################################\n");
    printf("1. Cadastrar Novo Item (Loot)\n");
    printf("2. Remover Item (Descarte/Uso)\n");
    printf("3. Listar Itens (Visualizar Mochila)\n");
    printf("4. Buscar Item por Nome (Checar Status)\n");
    printf("0. Sair do Jogo (Encerrar Inventario)\n");
    printf("--------------------------------------\n");
}

/**
 * Cadastra um novo item no inventario (Lista Sequencial) (sem acentos).
 */
void inserirItem(Item mochila[], int *qtd) {
    printf("\n--- CADASTRO DE ITEM ---\n");
    
    // Verifica se a mochila esta cheia
    if (*qtd >= MAX_ITENS) {
        printf("[ALERTA] Mochila cheia! Capacidade maxima (%d) atingida. Descarte algo antes de pegar mais loot.\n", MAX_ITENS);
        return;
    }

    // Leitura do Nome 
    printf("Nome do Item (max 29 caracteres): ");
    while (getchar() != '\n'); 
    fgets(mochila[*qtd].nome, 30, stdin);
    mochila[*qtd].nome[strcspn(mochila[*qtd].nome, "\n")] = 0;

    // Leitura do Tipo
    printf("Tipo do Item (ex: arma, municao, cura, ferramenta): ");
    fgets(mochila[*qtd].tipo, 20, stdin);
    mochila[*qtd].tipo[strcspn(mochila[*qtd].tipo, "\n")] = 0;

    // Leitura da Quantidade
    printf("Quantidade: ");
    while (scanf("%d", &mochila[*qtd].quantidade) != 1 || mochila[*qtd].quantidade <= 0) {
        printf("ERRO: Quantidade invalida. Digite um numero inteiro positivo: ");
        while (getchar() != '\n');
    }
    
    // Incrementa a quantidade de elementos validos na lista
    (*qtd)++; 
    printf("\n[SUCESSO] Item '%s' cadastrado! Posicao %d na mochila.\n", mochila[*qtd - 1].nome, *qtd);
}

/**
 * Remove um item do inventario (sem acentos).
 */
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

    // Deslocamento dos elementos: simula a remocao em uma lista sequencial
    for (int i = indice; i < *qtd - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    (*qtd)--;

    printf("\n[SUCESSO] O item '%s' foi removido com sucesso da mochila.\n", nomeRemover);
}

/**
 * Lista todos os itens atualmente no inventario (sem acentos).
 */
void listarItens(const Item mochila[], int qtd) {
    printf("\n--- VISUALIZACAO DA MOCHILA (ITENS: %d/%d) ---\n", qtd, MAX_ITENS);
    
    if (qtd == 0) {
        printf("[VAZIA] A mochila nao contem nenhum item no momento.\n");
        return;
    }

    // Percorre apenas os elementos validos
    for (int i = 0; i < qtd; i++) {
        printf(" [%d] - Nome: %s | Tipo: %s | Qtd: %d\n", 
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("---------------------------------------------------\n");
}

/**
 * Realiza a busca sequencial por um item na mochila com base no nome.
 */
int buscarItem(const Item mochila[], int qtd, const char nomeBusca[]) {
    // Laço for para percorrer a lista sequencial
    for (int i = 0; i < qtd; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            return i; // Item encontrado, retorna o índice
        }
    }
    return -1; // Item não encontrado
}