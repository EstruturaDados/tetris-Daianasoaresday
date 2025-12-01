#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ----------------------------------------------
//                  STRUCT PEÇA
// ----------------------------------------------
typedef struct {
    char tipo;   // Tipo da peça (I, O, T, L, etc.)
    int id;      // Identificador único
} Peca;


// ----------------------------------------------
//           CONSTANTES DO SISTEMA
// ----------------------------------------------
#define TAM_FILA 5
#define TAM_PILHA 3


// ----------------------------------------------
//           VARIÁVEIS GLOBAIS
// ----------------------------------------------
Peca fila[TAM_FILA];
Peca pilha[TAM_PILHA];

int frente = 0, tras = 0, qtdFila = 0;
int topo = -1;
int geradorID = 0;


// ----------------------------------------------
//              FUNÇÕES DA FILA
// ----------------------------------------------
void inicializarFila() {
    frente = 0;
    tras = 0;
    qtdFila = 0;
}

int filaVazia() {
    return qtdFila == 0;
}

int filaCheia() {
    return qtdFila == TAM_FILA;
}

// Gera peça automaticamente
Peca gerarPeca() {
    Peca p;
    char tipos[4] = {'I', 'O', 'T', 'L'};
    p.tipo = tipos[rand() % 4];
    p.id = geradorID++;
    return p;
}

void enqueue(Peca p) {
    if (filaCheia()) return;
    fila[tras] = p;
    tras = (tras + 1) % TAM_FILA;
    qtdFila++;
}

Peca dequeue() {
    Peca vazia = {'-', -1};

    if (filaVazia()) {
        printf("\nA fila está vazia! Nada a remover.\n");
        return vazia;
    }

    Peca removida = fila[frente];
    frente = (frente + 1) % TAM_FILA;
    qtdFila--;
    return removida;
}


// ----------------------------------------------
//              FUNÇÕES DA PILHA
// ----------------------------------------------
void inicializarPilha() {
    topo = -1;
}

int pilhaVazia() {
    return topo == -1;
}

int pilhaCheia() {
    return topo == TAM_PILHA - 1;
}

void push(Peca p) {
    if (pilhaCheia()) {
        printf("\nA pilha está cheia! Não é possível reservar.\n");
        return;
    }
    pilha[++topo] = p;
}

Peca pop() {
    Peca vazia = {'-', -1};
    if (pilhaVazia()) {
        printf("\nA pilha está vazia! Nenhuma peça reservada.\n");
        return vazia;
    }
    return pilha[topo--];
}


// ----------------------------------------------
//     FUNÇÕES PARA EXIBIR FILA E PILHA
// ----------------------------------------------
void mostrarFila() {
    printf("\nFila de Peças: ");
    if (filaVazia()) {
        printf("(vazia)\n");
        return;
    }

    int i = frente;
    for (int c = 0; c < qtdFila; c++) {
        printf("[%c %d] ", fila[i].tipo, fila[i].id);
        i = (i + 1) % TAM_FILA;
    }
    printf("\n");
}

void mostrarPilha() {
    printf("Pilha de Reserva (Topo -> Base): ");

    if (pilhaVazia()) {
        printf("(vazia)\n");
        return;
    }

    for (int i = topo; i >= 0; i--) {
        printf("[%c %d] ", pilha[i].tipo, pilha[i].id);
    }
    printf("\n");
}

void mostrarEstado() {
    printf("\n========================================");
    printf("\n         ESTADO ATUAL DO SISTEMA");
    printf("\n========================================\n");
    mostrarFila();
    mostrarPilha();
    printf("========================================\n");
}


// ----------------------------------------------
//                FUNÇÃO PRINCIPAL
// ----------------------------------------------
int main() {
    srand(time(NULL));

    inicializarFila();
    inicializarPilha();

    // Preenche fila inicial
    for (int i = 0; i < TAM_FILA; i++)
        enqueue(gerarPeca());

    int opcao;

    do {
        mostrarEstado();

        printf("\nOPÇÕES:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça (fila -> pilha)\n");
        printf("3 - Usar peça reservada (pilha -> fora)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1: {
                // Jogar peça
                Peca jogada = dequeue();
                if (jogada.id != -1)
                    printf("\nPeça jogada: [%c %d]\n", jogada.tipo, jogada.id);

                enqueue(gerarPeca());
                break;
            }

            case 2: {
                // Reservar peça
                if (pilhaCheia()) {
                    printf("\nA pilha está cheia! Não é possível reservar.\n");
                    break;
                }

                if (!filaVazia()) {
                    Peca p = dequeue();
                    push(p);
                    printf("\nPeça [%c %d] movida para a reserva.\n", p.tipo, p.id);
                    enqueue(gerarPeca());
                }
                break;
            }

            case 3: {
                // Usar peça reservada
                if (!pilhaVazia()) {
                    Peca usada = pop();
                    printf("\nPeça reservada usada: [%c %d]\n", usada.tipo, usada.id);
                    enqueue(gerarPeca());
                }
                break;
            }

            case 0:
                printf("\nEncerrando...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
