#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ---------------------------------------------------------
//                     STRUCT PEÇA
// ---------------------------------------------------------
typedef struct {
    char tipo;
    int id;
} Peca;


// ---------------------------------------------------------
//                     CONSTANTES
// ---------------------------------------------------------
#define TAM_FILA 5
#define TAM_PILHA 3


// ---------------------------------------------------------
//                VARIÁVEIS GLOBAIS
// ---------------------------------------------------------
Peca fila[TAM_FILA];
Peca pilha[TAM_PILHA];

int frente = 0, tras = 0, qtdFila = 0;
int topo = -1;
int geradorID = 0;


// ---------------------------------------------------------
//                     FUNÇÕES FILA
// ---------------------------------------------------------
void inicializarFila() {
    frente = tras = qtdFila = 0;
}

int filaVazia() { return qtdFila == 0; }
int filaCheia() { return qtdFila == TAM_FILA; }

Peca gerarPeca() {
    char tipos[4] = {'I','O','T','L'};
    Peca p = {tipos[rand() % 4], geradorID++};
    return p;
}

void enqueue(Peca p) {
    if (filaCheia()) return;
    fila[tras] = p;
    tras = (tras + 1) % TAM_FILA;
    qtdFila++;
}

Peca dequeue() {
    Peca erro = {'-', -1};
    if (filaVazia()) return erro;

    Peca x = fila[frente];
    frente = (frente + 1) % TAM_FILA;
    qtdFila--;
    return x;
}


// ---------------------------------------------------------
//                     FUNÇÕES PILHA
// ---------------------------------------------------------
void inicializarPilha() {
    topo = -1;
}

int pilhaVazia() { return topo == -1; }
int pilhaCheia() { return topo == TAM_PILHA - 1; }

void push(Peca p) {
    if (!pilhaCheia())
        pilha[++topo] = p;
}

Peca pop() {
    Peca erro = {'-', -1};
    if (pilhaVazia()) return erro;

    return pilha[topo--];
}


// ---------------------------------------------------------
//          FUNÇÕES DE EXIBIÇÃO DA ESTRUTURA
// ---------------------------------------------------------
void mostrarFila() {
    printf("Fila de peças: ");
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
    printf("Pilha de reserva (Topo -> Base): ");
    if (pilhaVazia()) {
        printf("(vazia)\n");
        return;
    }

    for (int i = topo; i >= 0; i--)
        printf("[%c %d] ", pilha[i].tipo, pilha[i].id);

    printf("\n");
}

void mostrarEstado() {
    printf("\n============================================\n");
    printf("              ESTADO ATUAL\n");
    printf("============================================\n");
    mostrarFila();
    mostrarPilha();
    printf("============================================\n");
}


// ---------------------------------------------------------
//             FUNÇÕES DE TROCA (NÍVEL MESTRE)
// ---------------------------------------------------------

// Troca 1: frente da fila ↔ topo da pilha
void trocarIndividual() {
    if (filaVazia()) {
        printf("\nNão é possível trocar: a fila está vazia.\n");
        return;
    }
    if (pilhaVazia()) {
        printf("\nNão é possível trocar: a pilha está vazia.\n");
        return;
    }

    int indiceFila = frente;
    int indicePilha = topo;

    Peca temp = fila[indiceFila];
    fila[indiceFila] = pilha[indicePilha];
    pilha[indicePilha] = temp;

    printf("\nTroca entre frente da fila e topo da pilha realizada com sucesso.\n");
}


// Troca 2: troca os 3 primeiros da fila com as 3 peças da pilha
void trocarTres() {
    if (qtdFila < 3) {
        printf("\nA fila não possui 3 peças para trocar.\n");
        return;
    }
    if (topo < 2) {
        printf("\nA pilha não possui 3 peças para trocar.\n");
        return;
    }

    for (int i = 0; i < 3; i++) {
        int idxFila = (frente + i) % TAM_FILA;  // circular
        int idxPilha = topo - i;                // linear inverso

        Peca tmp = fila[idxFila];
        fila[idxFila] = pilha[idxPilha];
        pilha[idxPilha] = tmp;
    }

    printf("\nTroca múltipla entre as 3 primeiras peças da fila e as 3 da pilha realizada com sucesso!\n");
}


// ---------------------------------------------------------
//                  FUNÇÃO PRINCIPAL
// ---------------------------------------------------------
int main() {
    srand(time(NULL));

    inicializarFila();
    inicializarPilha();

    // Preenche a fila inicial
    for (int i = 0; i < TAM_FILA; i++)
        enqueue(gerarPeca());

    int opcao;

    do {
        mostrarEstado();

        printf("\nOPÇÕES:\n");
        printf("1 - Jogar peça da frente da fila\n");
        printf("2 - Enviar peça da fila para a pilha de reserva\n");
        printf("3 - Usar peça da pilha de reserva\n");
        printf("4 - Trocar peça da frente da fila com topo da pilha\n");
        printf("5 - Trocar as 3 primeiras da fila com as 3 da pilha\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1: {
                Peca jogada = dequeue();
                if (jogada.id != -1)
                    printf("\nPeça jogada: [%c %d]\n", jogada.tipo, jogada.id);

                enqueue(gerarPeca());
                break;
            }

            case 2: {
                if (pilhaCheia()) {
                    printf("\nA pilha está cheia! Não é possível reservar.\n");
                    break;
                }

                Peca p = dequeue();
                if (p.id != -1) {
                    push(p);
                    printf("\nPeça [%c %d] movida para a reserva.\n", p.tipo, p.id);
                    enqueue(gerarPeca());
                }
                break;
            }

            case 3: {
                Peca usada = pop();
                if (usada.id != -1)
                    printf("\nPeça reservada usada: [%c %d]\n", usada.tipo, usada.id);

                enqueue(gerarPeca());
                break;
            }

            case 4:
                trocarIndividual();
                break;

            case 5:
                trocarTres();
                break;

            case 0:
                printf("\nEncerrando...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
