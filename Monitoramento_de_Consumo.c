#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RESIDENCES 100
#define MONTHS 12
#define SAFE_AVERAGE 15.0

typedef struct {
    int id;
    char resident[50];
    int num_residents;
    float consumption[MONTHS];
} Residence;

Residence residences[MAX_RESIDENCES];
int residence_count = 0;

// Function prototypes
void registerResidence();
void updateMonthlyConsumption();
void displayAboveAverage();
void displayBelowAverage();
float calculateCommunityAverage();

int main() {
    int choice;
    
    do {
        printf("\nMenu:\n");
        printf("1 - Cadastrar casa\n");
        printf("2 - Registrar consumo mensal\n");
        printf("3 - Exibir casas acima da média\n");
        printf("4 - Exibir casas abaixo da média\n");
        printf("5 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerResidence();
                break;
            case 2:
                updateMonthlyConsumption();
                break;
            case 3:
                displayAboveAverage();
                break;
            case 4:
                displayBelowAverage();
                break;
            case 5:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (choice != 5);

    return 0;
}

void registerResidence() {
    if (residence_count >= MAX_RESIDENCES) {
        printf("Limite de residências atingido.\n");
        return;
    }

    Residence r;
    printf("\nID da residência: ");
    scanf("%d", &r.id);
    printf("Nome do morador principal: ");
    scanf(" %49[^\n]", r.resident); // Corrigido o delimitador para aceitar espaços
    printf("Número de moradores: ");
    scanf("%d", &r.num_residents);

    for (int i = 0; i < MONTHS; i++) {
        r.consumption[i] = 0.0;
    }

    residences[residence_count++] = r;
    printf("Residência cadastrada com sucesso!\n");
}

void updateMonthlyConsumption() {
    int id, month;
    float consumption;

    printf("\nID da residência: ");
    scanf("%d", &id);

    int index = -1;
    for (int i = 0; i < residence_count; i++) {
        if (residences[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Residência não encontrada.\n");
        return;
    }

    printf("Mês (1-12): ");
    scanf("%d", &month);
    if (month < 1 || month > 12) {
        printf("Mês inválido.\n");
        return;
    }

    printf("Consumo em m3: ");
    scanf("%f", &consumption);

    residences[index].consumption[month - 1] = consumption;
    printf("Consumo atualizado com sucesso!\n");
}

void displayAboveAverage() {
    float community_avg = calculateCommunityAverage();
    printf("\nMédia segura: %.2f m3\n", SAFE_AVERAGE);
    printf("Média comunitária: %.2f m3\n", community_avg);

    printf("Residências acima da média:\n");
    for (int i = 0; i < residence_count; i++) {
        float total = 0.0;
        for (int j = 0; j < MONTHS; j++) {
            total += residences[i].consumption[j];
        }
        float avg = total / MONTHS;
        if (avg > SAFE_AVERAGE) {
            printf("ID: %d, Morador: %s, Consumo médio: %.2f m3\n", residences[i].id, residences[i].resident, avg);
        }
    }
}

void displayBelowAverage() {
    float community_avg = calculateCommunityAverage();
    printf("\nMédia segura: %.2f m3\n", SAFE_AVERAGE);
    printf("Média comunitária: %.2f m3\n", community_avg);

    printf("Residências abaixo da média:\n");
    for (int i = 0; i < residence_count; i++) {
        float total = 0.0;
        for (int j = 0; j < MONTHS; j++) {
            total += residences[i].consumption[j];
        }
        float avg = total / MONTHS;
        if (avg <= SAFE_AVERAGE) {
            printf("ID: %d, Morador: %s, Consumo médio: %.2f m3\n", residences[i].id, residences[i].resident, avg);
        }
    }
}

float calculateCommunityAverage() {
    float total = 0.0;
    int count = 0;

    for (int i = 0; i < residence_count; i++) {
        for (int j = 0; j < MONTHS; j++) {
            total += residences[i].consumption[j];
            count++;
        }
    }

    return (count > 0) ? (total / count) : 0.0;
}
