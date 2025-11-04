#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5

typedef struct {
    char nome;
    int id;
} Peca;

typedef struct {
    Peca pecas[MAX];
    int inicio;
    int fim;
    int quantidade;
} FilaCircular;

// Função para inicializar a fila
void inicializarFila(FilaCircular *fila) {
    fila->inicio = 0;
    fila->fim = -1;
    fila->quantidade = 0;
}

// Função para gerar uma peça aleatória
Peca gerarPeca(int id) {
    Peca novaPeca;
    char tipos[] = {'I', 'O', 'T', 'L', 'J', 'S', 'Z'};
    
    novaPeca.nome = tipos[rand() % 7];
    novaPeca.id = id;
    
    return novaPeca;
}

// Função para verificar se a fila está vazia
int filaVazia(FilaCircular *fila) {
    return fila->quantidade == 0;
}

// Função para verificar se a fila está cheia
int filaCheia(FilaCircular *fila) {
    return fila->quantidade == MAX;
}

// Função para enfileirar uma peça
void enfileirar(FilaCircular *fila, Peca peca) {
    if (filaCheia(fila)) {
        printf("⚠️ Erro: Fila cheia!\n");
        return;
    }
    
    fila->fim = (fila->fim + 1) % MAX;
    fila->pecas[fila->fim] = peca;
    fila->quantidade++;
}

// Função para desenfileirar uma peça
Peca desenfileirar(FilaCircular *fila) {
    Peca pecaVazia = {' ', -1};
    
    if (filaVazia(fila)) {
        printf("⚠️ Erro: Fila vazia!\n");
        return pecaVazia;
    }
    
    Peca pecaRemovida = fila->pecas[fila->inicio];
    fila->inicio = (fila->inicio + 1) % MAX;
    fila->quantidade--;
    
    return pecaRemovida;
}

// Função para visualizar a fila
void visualizarFila(FilaCircular *fila) {
    printf("\n🎮 === FILA DE PEÇAS FUTURAS ===\n");
    
    if (filaVazia(fila)) {
        printf("Fila vazia!\n");
        return;
    }
    
    int posicao = fila->inicio;
    for (int i = 0; i < fila->quantidade; i++) {
        printf("Posição %d: [%c] (ID: %d)\n", 
               i + 1, 
               fila->pecas[posicao].nome, 
               fila->pecas[posicao].id);
        posicao = (posicao + 1) % MAX;
    }
    printf("Total de peças na fila: %d\n", fila->quantidade);
}

// Função para mostrar o menu
void mostrarMenu() {
    printf("\n🧱 === TETRIS STACK - NÍVEL NOVATO ===\n");
    printf("1. Visualizar fila atual\n");
    printf("2. Jogar peça da frente\n");
    printf("3. Inserir nova peça\n");
    printf("4. Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    
    FilaCircular fila;
    inicializarFila(&fila);
    int proximoId = 1;
    
    // Inicializa a fila com 5 peças
    printf("Inicializando fila com 5 peças...\n");
    for (int i = 0; i < MAX; i++) {
        Peca novaPeca = gerarPeca(proximoId++);
        enfileirar(&fila, novaPeca);
    }
    
    int opcao;
    do {
        mostrarMenu();

        // Usa scanf com verificação de retorno pra evitar loop infinito
        if (scanf("%d", &opcao) != 1) {
            printf("\n⚠️ Entrada inválida! Digite um número.\n");
            while (getchar() != '\n'); // limpa buffer
            continue;
        }
        
        switch (opcao) {
            case 1:
                visualizarFila(&fila);
                break;
                
            case 2:
                if (!filaVazia(&fila)) {
                    Peca pecaJogada = desenfileirar(&fila);
                    printf("\nPeça jogada: [%c] (ID: %d)\n", 
                           pecaJogada.nome, pecaJogada.id);
                    
                    // Insere automaticamente uma nova peça
                    if (!filaCheia(&fila)) {
                        Peca novaPeca = gerarPeca(proximoId++);
                        enfileirar(&fila, novaPeca);
                        printf("Nova peça inserida: [%c] (ID: %d)\n", 
                               novaPeca.nome, novaPeca.id);
                    }
                    
                    visualizarFila(&fila);
                } else {
                    printf("\nFila vazia! Não há peças para jogar.\n");
                }
                break;
                
            case 3:
                if (!filaCheia(&fila)) {
                    Peca novaPeca = gerarPeca(proximoId++);
                    enfileirar(&fila, novaPeca);
                    printf("\nNova peça inserida: [%c] (ID: %d)\n", 
                           novaPeca.nome, novaPeca.id);
                    visualizarFila(&fila);
                } else {
                    printf("\nFila cheia! Jogue uma peça primeiro.\n");
                }
                break;
                
            case 4:
                printf("\n👋 Obrigado por jogar Tetris Stack!\n");
                break;
                
            default:
                printf("\n❌ Opção inválida! Tente novamente.\n");
                break;
        }
        
    } while (opcao != 4);
    
    return 0;
}
