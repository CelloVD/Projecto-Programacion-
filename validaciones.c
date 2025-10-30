#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "validaciones.h"

void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}



int validarEmail(const char *email) {
    if (!email || strlen(email) == 0) return 0;
    const char *arroba = strchr(email, '@');
    if (!arroba || arroba == email) return 0;
    const char *punto = strchr(arroba, '.');
    return punto != NULL && punto != arroba + 1 && strlen(punto) > 1;
}
