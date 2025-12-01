#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ----------------------------
//      ESTRUTURAS
// ----------------------------
typedef struct {
    char tipo;   // Tipo da peça (T, L, S, Z, O, I, J)
    int id;      // Identificador sequencial
} Peca;


// ----------------------------
//   CONSTANTES DO DESAFIO
// ----------------------------
#define TAM_FILA 5


// ----------------------------
//  VARIÁVEIS GLOBAIS
// ----------------------------
int frente = 0, tras = 0, quantidade = 0;
int geradorID = 1;
Peca fila[TAM_FILA];


// ----------------------------
//      FUNÇÕES DA FILA
// ----------------------------

// Inicia a fila
void inicializarFila() {
    frente = 0;
    tras = 0;
    quantidade = 0;
}

// Verifica se está vazia
int filaVazia() {
    return quantidade == 0;
}

// Verifica se está cheia
int filaCheia() {
    return quantidade == TAM_FILA;
}

// Gera uma peça automática
Peca gerarPeca() {
    Peca p;
    char tipos[7] = {'T','L','S','Z','O','I','J'};
    p.tipo = tipos[rand() % 7];
    p.id = geradorID++;
    return p;
}

// Insere peça no final
void enqueue(Peca p) {
    if (filaCheia()) {
        printf("\nFila cheia! Não é possível inserir.\n");
        return;
    }
    fila[tras] = p;
    tras = (tras + 1) % TAM_FILA;
    quantidade++;
}

// Remove peça da frente
Peca dequeue() {
    Peca removida = {'-', -1};
    if (filaVazia()) {
        printf("\nFila vazia! Nada a remover.\n");
        return removida;
    }

    removida = fila[frente];
    frente = (frente + 1) % TAM_FILA;
    quantidade--;

    return removida;
}

// Exibe toda a fila
void mostrarFila() {
    printf("\n=== FILA DE PEÇAS (FIFO) ===\n");
    if (filaVazia()) {
        printf("Fila vazia!\n");
        return;
    }

    int i = frente;
    for (int c = 0; c < quantidade; c++) {
        printf("[ID %d | %c] ", fila[i].id, fila[i].tipo);
        i = (i + 1) % TAM_FILA;
    }
    printf("\n============================\n");
}


// ----------------------------
//      FUNÇÃO PRINCIPAL
// ----------------------------
int main() {

    // Inicializa aleatório e fila
    srand(time(NULL));
    inicializarFila();

    // Preenche a fila automaticamente com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(gerarPeca());
    }

    int opcao;

    do {
        mostrarFila();

        printf("\nMENU - NIVEL NOVATO\n");
        printf("1 - Jogar peça (remover da frente)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            // Remover a peça
            Peca jogada = dequeue();

            if (jogada.id != -1) {
                printf("\nPeça jogada: ID %d | %c\n", jogada.id, jogada.tipo);

                // Repor nova peça automaticamente
                enqueue(gerarPeca());
            }
        }

    } while (opcao != 0);

    printf("\nEncerrando...\n");
    return 0;
}
