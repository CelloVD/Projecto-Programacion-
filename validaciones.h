#ifndef VALIDACIONES_H
#define VALIDACIONES_H

typedef struct {
    int dia;
    int mes;
    int anio;
} Fecha;

int validarRut(const char *rut);
int validarFecha(const char *fecha);
int validarEmail(const char *email);
void limpiar_buffer(void);

#endif
