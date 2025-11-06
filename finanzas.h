#ifndef FINANZAS_H
#define FINANZAS_H

#include "constante.h"

typedef struct {
    char numeroCuenta[20];
    char banco[50];
    char fechaTransaccion[11];
    double ingresos;
    double egresos;
    double saldoActual;
    char rutAsociado[13];
} Finanzas;

extern Finanzas finanzas[MAX_REGISTROS];
extern int totalFinanzas;

void eliminarFinanzasPorRut(const char* rut);
void menuFinanzas(void);
void agregarFinanzas(void);
void listarFinanzasPorRut(const char* rut);
void editarFinanzas(void);
void eliminarFinanzas(void);
void mostrarMontoEnCLPyUSD(double monto); // Muestra en peso chileno y dólar

#endif
