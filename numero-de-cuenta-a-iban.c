#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define IBAN_PREFIX "ES"
#define IBAN_LENGTH 24 // IBAN completo, incluyendo prefijo y checksum
#define ACCOUNT_LENGTH 20 // Número de cuenta sin prefijo ni checksum

// Función para convertir un IBAN a un número de cuenta
void iban_to_account(const char *iban, char *account) {
    if (strlen(iban) != IBAN_LENGTH || strncmp(iban, IBAN_PREFIX, 2) != 0) {
        fprintf(stderr, "Formato de IBAN no válido.\n");
        exit(EXIT_FAILURE);
    }

    strncpy(account, iban + 4, ACCOUNT_LENGTH); // Saltar prefijo y checksum
    account[ACCOUNT_LENGTH] = '\0';
}

// Función para convertir un número de cuenta a un IBAN
void account_to_iban(const char *account, char *iban) {
    if (strlen(account) != ACCOUNT_LENGTH) {
        fprintf(stderr, "Formato de número de cuenta no válido.\n");
        exit(EXIT_FAILURE);
    }

    snprintf(iban, IBAN_LENGTH + 1, "%s00%s", IBAN_PREFIX, account); // Placeholder para checksum

    // Cálculo de checksum (implementación simplificada)
    char temp[IBAN_LENGTH * 2];
    snprintf(temp, sizeof(temp), "%s%s%s00", account, "142800", IBAN_PREFIX + 2); // Código país a números

    unsigned long checksum = 0;
    for (size_t i = 0; i < strlen(temp); ++i) {
        checksum = (checksum * 10 + (temp[i] - '0')) % 97;
    }

    checksum = 98 - checksum;
    snprintf(iban, IBAN_LENGTH + 1, "%s%02lu%s", IBAN_PREFIX, checksum, account);
}

int main() {
    char iban[IBAN_LENGTH + 1];
    char account[ACCOUNT_LENGTH + 1];
    int option;

    printf("Seleccione una opción:\n");
    printf("1. Convertir IBAN a número de cuenta\n");
    printf("2. Convertir número de cuenta a IBAN\n");
    printf("Opción: ");
    scanf("%d", &option);

    switch (option) {
        case 1:
            printf("Introduce el IBAN: ");
            scanf("%s", iban);
            iban_to_account(iban, account);
            printf("Número de cuenta: %s\n", account);
            break;

        case 2:
            printf("Introduce el número de cuenta: ");
            scanf("%s", account);
            account_to_iban(account, iban);
            printf("IBAN: %s\n", iban);
            break;

        default:
            printf("Opción no válida.\n");
    }

    return 0;
}
