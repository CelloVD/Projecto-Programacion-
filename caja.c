#include <stdio.h>
#include <string.h>
#include "caja.h"

const char* CAJA_VALIDOS[NUM_CAJA] = {
    "Los Andes",
    "La Araucana",
    "Los Héroes",
    "Caja 18"

};

int esCajaValido(const char* caja) {
    if (!caja) return 0;
    for (int i = 0; i < NUM_CAJA; i++) {
        if (strcmp(caja, CAJA_VALIDOS[i]) == 0)
            return 1;
    }
    return 0;
}

void seleccionarCaja(char destino[], int tam) {
    printf("\nSeleccione un Caja:\n");
    for (int i = 0; i < NUM_CAJA; i++) {
        printf("%2d. %s\n", i + 1, CAJA_VALIDOS[i]);
    }
    printf("Opción (1-%d): ", NUM_CAJA);

    int op;
    scanf("%d", &op);
    getchar(); // limpiar \n

    if (op >= 1 && op <= NUM_CAJA) {
        strncpy(destino, CAJA_VALIDOS[op - 1], tam - 1);
        destino[tam - 1] = '\0';
    } else {
        strncpy(destino, "Caja de compensacion no válido", tam - 1);
        destino[tam - 1] = '\0';
    }
}
