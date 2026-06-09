#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEITURAS 100

#define VERMELHO "\033[1;31m"
#define VERDE "\033[1;32m"
#define AMARELO "\033[1;33m"
#define AZUL "\033[1;34m"
#define RESET "\033[0m"

typedef struct {
    float temperatura;
    int energia;
    int comunicacao;
    char statusOperacional[30];
} LeituraMissao;

LeituraMissao historico[MAX_LEITURAS];
int totalLeituras = 0;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
}

void cabecalho() {
    printf("==================================================\n");
    printf(AZUL "              MISSION CONTROL AI\n" RESET);
    printf("==================================================\n");
}

void inserirDados() {
    limparTela();
    cabecalho();

    if (totalLeituras >= MAX_LEITURAS) {
        printf(VERMELHO "Limite de leituras atingido!\n" RESET);
        pausar();
        return;
    }

    printf("INSERIR DADOS DA MISSAO\n\n");

    printf("Temperatura da nave em Celsius: ");
    while (scanf("%f", &historico[totalLeituras].temperatura) != 1) {
        printf(VERMELHO "Entrada invalida. Digite um numero: " RESET);
        limparBuffer();
    }

    do {
        printf("Porcentagem de energia (0 a 100): ");
        while (scanf("%d", &historico[totalLeituras].energia) != 1) {
            printf(VERMELHO "Entrada invalida. Digite um numero inteiro: " RESET);
            limparBuffer();
        }

        if (historico[totalLeituras].energia < 0 || historico[totalLeituras].energia > 100) {
            printf(VERMELHO "A energia deve estar entre 0 e 100.\n" RESET);
        }

    } while (historico[totalLeituras].energia < 0 || historico[totalLeituras].energia > 100);

    do {
        printf("Comunicacao ativa? 1 - ONLINE | 0 - OFFLINE: ");
        while (scanf("%d", &historico[totalLeituras].comunicacao) != 1) {
            printf(VERMELHO "Entrada invalida. Digite 1 ou 0: " RESET);
            limparBuffer();
        }

        if (historico[totalLeituras].comunicacao != 0 && historico[totalLeituras].comunicacao != 1) {
            printf(VERMELHO "A comunicacao deve ser 1 para ONLINE ou 0 para OFFLINE.\n" RESET);
        }

    } while (historico[totalLeituras].comunicacao != 0 && historico[totalLeituras].comunicacao != 1);

    limparBuffer();

    printf("Status operacional da missao: ");
    scanf(" %29[^\n]", historico[totalLeituras].statusOperacional);
    limparBuffer();

    totalLeituras++;

    printf(VERDE "\nDados inseridos com sucesso!\n" RESET);
    pausar();
}

int verificarRiscoOperacional(char status[]) {
    char statusMinusculo[30];

    for (int i = 0; status[i] != '\0' && i < 29; i++) {
        statusMinusculo[i] = tolower(status[i]);
        statusMinusculo[i + 1] = '\0';
    }

    if (
        strcmp(statusMinusculo, "falha") == 0 ||
        strcmp(statusMinusculo, "critico") == 0 ||
        strcmp(statusMinusculo, "crítico") == 0 ||
        strcmp(statusMinusculo, "risco") == 0
    ) {
        return 1;
    }

    return 0;
}

void analisarSistema(LeituraMissao leitura) {
    int existeAlerta = 0;

    printf("\n" AMARELO "ALERTAS:\n" RESET);

    if (leitura.temperatura > 80) {
        printf(VERMELHO "- ALERTA DE SUPERAQUECIMENTO\n" RESET);
        existeAlerta = 1;
    }

    if (leitura.energia < 20) {
        printf(AMARELO "- MODO DE ECONOMIA DE ENERGIA\n" RESET);
        existeAlerta = 1;
    }

    if (leitura.comunicacao == 0) {
        printf(VERMELHO "- FALHA DE COMUNICACAO\n" RESET);
        existeAlerta = 1;
    }

    if (verificarRiscoOperacional(leitura.statusOperacional)) {
        printf(VERMELHO "- RISCO OPERACIONAL\n" RESET);
        existeAlerta = 1;
    }

    if (existeAlerta == 0) {
        printf(VERDE "- Nenhum alerta identificado. Missao estavel.\n" RESET);
    }
}

void mostrarStatus() {
    limparTela();
    cabecalho();

    if (totalLeituras == 0) {
        printf(VERMELHO "Nenhuma leitura cadastrada ainda.\n" RESET);
        pausar();
        return;
    }

    LeituraMissao atual = historico[totalLeituras - 1];

    printf("STATUS ATUAL DA MISSAO\n\n");
    printf("Temperatura: %.2f C\n", atual.temperatura);
    printf("Energia: %d%%\n", atual.energia);
    printf("Comunicacao: %s\n", atual.comunicacao == 1 ? "ONLINE" : "OFFLINE");
    printf("Status Operacional: %s\n", atual.statusOperacional);

    analisarSistema(atual);

    pausar();
}

void executarAnaliseAutomatica() {
    limparTela();
    cabecalho();

    if (totalLeituras == 0) {
        printf(VERMELHO "Nenhuma leitura cadastrada para analise.\n" RESET);
        pausar();
        return;
    }

    printf("ANALISE AUTOMATICA DA ULTIMA LEITURA\n");

    LeituraMissao atual = historico[totalLeituras - 1];

    printf("\nTemperatura: %.2f C", atual.temperatura);
    printf("\nEnergia: %d%%", atual.energia);
    printf("\nComunicacao: %s", atual.comunicacao == 1 ? "ONLINE" : "OFFLINE");
    printf("\nStatus Operacional: %s\n", atual.statusOperacional);

    analisarSistema(atual);

    pausar();
}

void mostrarHistorico() {
    limparTela();
    cabecalho();

    if (totalLeituras == 0) {
        printf(VERMELHO "Nenhum historico disponivel.\n" RESET);
        pausar();
        return;
    }

    printf("HISTORICO DE LEITURAS\n\n");

    for (int i = 0; i < totalLeituras; i++) {
        printf("--------------------------------------------------\n");
        printf("Leitura %d\n", i + 1);
        printf("Temperatura: %.2f C\n", historico[i].temperatura);
        printf("Energia: %d%%\n", historico[i].energia);
        printf("Comunicacao: %s\n", historico[i].comunicacao == 1 ? "ONLINE" : "OFFLINE");
        printf("Status Operacional: %s\n", historico[i].statusOperacional);
        analisarSistema(historico[i]);
        printf("--------------------------------------------------\n\n");
    }

    pausar();
}

void menu() {
    int opcao;

    do {
        limparTela();
        cabecalho();

        printf("1 - Inserir dados da missao\n");
        printf("2 - Visualizar status atual\n");
        printf("3 - Executar analise automatica\n");
        printf("4 - Exibir historico das leituras\n");
        printf("5 - Encerrar sistema\n");
        printf("==================================================\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf(VERMELHO "\nEntrada invalida! Digite um numero.\n" RESET);
            limparBuffer();
            pausar();
            opcao = 0;
            continue;
        }

        limparBuffer();

        switch (opcao) {
            case 1:
                inserirDados();
                break;
            case 2:
                mostrarStatus();
                break;
            case 3:
                executarAnaliseAutomatica();
                break;
            case 4:
                mostrarHistorico();
                break;
            case 5:
                limparTela();
                cabecalho();
                printf(VERDE "Sistema encerrado com sucesso.\n" RESET);
                break;
            default:
                printf(VERMELHO "\nOpcao invalida! Tente novamente.\n" RESET);
                pausar();
                break;
        }

    } while (opcao != 5);
}

int main() {
    menu();
    return 0;
}