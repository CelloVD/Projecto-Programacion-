#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "finanzas.h"
#include "miembro.h"         // para verificar que el RUT exista
#include "validaciones.h"    // para validar RUT y fecha
#include "bancos.h"          // para seleccionar banco válido

// Definición de variables globales
Finanzas finanzas[MAX_REGISTROS];
int totalFinanzas = 0; //Contador de registros reales 

// Tasa de conversión: 1 USD = 900 CLP
#define TASA_USD 900.0

// Elimina en cascada todas las finanzas asociadas a un RUT
void eliminarFinanzasPorRut(const char* rut) {

    if (!rut) return;
    for (int i = 0; i < totalFinanzas; ) {
        if (strcmp(finanzas[i].rutAsociado, rut) == 0) {
            // Desplazar todos los elementos siguientes una posición atrás
            for (int j = i; j < totalFinanzas - 1; j++) {
                finanzas[j] = finanzas[j + 1];
            }
            totalFinanzas--;
            // No incrementar 'i' aquí, porque el nuevo elemento en [i] debe ser revisado
        } else {
            i++;
        }
    }
}

//Menú interactivo del módulo finanzas 
int menuFinanzas() {
    int opcion;
    do {
        printf("\n-------- MÓDULO FINANZAS --------\n");
        printf("1. Agregar finanzas\n");
        printf("2. Listar finanzas por RUT\n");
        printf("3. Editar finanzas\n");
        printf("4. Eliminar finanzas\n");
        printf("5. Volver al menú principal\n");
        printf("Opción: ");
        scanf("%d", &opcion);
        printf("\n---------------------------------\n");
        limpiar_buffer(); //Evita problemas con fgets tras scanf 

        switch (opcion) {
            case 1:    
                agregarFinanzas(); 
                break;
            case 2: {
                char rut[13];
                printf("Ingrese RUT del miembro (ej: 12.345.678-9): ");
                fgets(rut, sizeof(rut), stdin);
                rut[strcspn(rut, "\n")] = 0; //Elimina salto de línea 

                //Validación obligatoria
                if (!validarRut(rut)) {
                    printf("RUT inválido.\n");
                } else if (!existeMiembro(rut)) {
                    printf("No existe un miembro con ese RUT.\n");
                } else {
                    listarFinanzasPorRut(rut);
                }
                break;
            }
            case 3: 
                editarFinanzas(); 
                break;
            case 4: 
                eliminarFinanzas(); 
                break;
            case 5: 
                //Vuelve al menú principal 
                break;
            default: 
                printf("Opción no válida.\n");
        }
    } while (opcion != 5);
}

//Crea un nuevo registro financiero vinculado a un rut existente 
void agregarFinanzas(void) {
    if (totalFinanzas > MAX_REGISTROS) {
        printf("No se pueden registrar más finanzas (máx. %d).\n", MAX_REGISTROS);
        return;
    }

    char rut[13];
    printf("Ingrese RUT del miembro (ej: 12.345.678-9): ");
    fgets(rut, sizeof(rut), stdin);
    rut[strcspn(rut, "\n")] = 0;

    //Valida el Rut 
    if (!validarRut(rut)) {
        printf("RUT inválido.\n");
        return;
    }

    //El rut debe pertenecer a un miembro ya registrado 
    if (!existeMiembro(rut)) {
        printf("El RUT no pertenece a ningún miembro registrado.\n");
        return;
    }

    Finanzas f;
    //Guarda Rut limpio
    strncpy(f.rutAsociado, rut, sizeof(f.rutAsociado) - 1);
    f.rutAsociado[sizeof(f.rutAsociado) - 1] = '\0';

    printf("Número de cuenta: ");
    fgets(f.numeroCuenta, sizeof(f.numeroCuenta), stdin);
    f.numeroCuenta[strcspn(f.numeroCuenta, "\n")] = 0;

    //Selecciona el banco autorizado 
    seleccionarBanco(f.banco, 50);

    printf("Fecha de transacción (dd/mm/aaaa): ");
    fgets(f.fechaTransaccion, sizeof(f.fechaTransaccion), stdin);
    f.fechaTransaccion[strcspn(f.fechaTransaccion, "\n")] = 0;

    //Validación de formato y lógica de fecha (dd/mm/aaaa)
    if (!validarFecha(f.fechaTransaccion)) {
        printf("Fecha inválida.\n");
        return;
    }

    //Ingreso en CLP 
    printf("Ingresos (CLP): ");
    if (scanf("%lf", &f.ingresos) != 1) {
        printf("Entrada inválida.\n");
        limpiar_buffer();
        return;
    }
    limpiar_buffer();

    //Egresos en CLP
    printf("Egresos (CLP): ");
    if (scanf("%lf", &f.egresos) != 1) {
        printf("Entrada inválida.\n");
        limpiar_buffer();
        return;
    }
    limpiar_buffer();
    
    //Calculo automático del saldo 
    f.saldoActual = f.ingresos - f.egresos;

    //Guarda el nuevo registro
    finanzas[totalFinanzas] = f;
    totalFinanzas++;
    printf("Finanzas registradas correctamente.\n");
}

//Muestra todas las finanzas de un miembro por su Rut
void listarFinanzasPorRut(const char* rut) {
    int encontrado = 0;
    printf("\n=== FINANZAS DEL RUT: %s ===\n", rut);
    for (int i = 0; i < totalFinanzas; i++) {
        if (strcmp(finanzas[i].rutAsociado, rut) == 0) {
            encontrado = 1;
            printf("\n[ID: %d]\n", i + 1);
            printf("Cuenta: %s\n", finanzas[i].numeroCuenta);
            printf("Banco: %s\n", finanzas[i].banco);
            printf("Fecha: %s\n", finanzas[i].fechaTransaccion);
            printf("Ingresos: ");
            mostrarMontoEnCLPyUSD(finanzas[i].ingresos);
            printf("Egresos: ");
            mostrarMontoEnCLPyUSD(finanzas[i].egresos);
            printf("Saldo actual: ");
            mostrarMontoEnCLPyUSD(finanzas[i].saldoActual);
            printf("------------------------\n");
        }
    }
    if (!encontrado) {
        printf("No hay registros financieros para este RUT.\n");
    }
}

//Modifica un registro financiero existente 
void editarFinanzas(void) {
    if (totalFinanzas == 0) {
        printf("No hay registros para editar.\n");
        return;
    }

    int id;
    printf("Ingrese ID de la finanza a editar (1 a %d): ", totalFinanzas);
    if (scanf("%d", &id) != 1 || id < 1 || id > totalFinanzas) {
        printf("ID inválido.\n");
        limpiar_buffer();
        return;
    }
    limpiar_buffer();
    id--; //Convierte a índice base 0

    printf("Editando finanza para RUT: %s\n", finanzas[id].rutAsociado);

    //Editar número de cuenta 
    printf("Nuevo número de cuenta (actual: %s): ", finanzas[id].numeroCuenta);
    char temp[50];
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = 0;
    if (strlen(temp) > 0) {
        strncpy(finanzas[id].numeroCuenta, temp, sizeof(finanzas[id].numeroCuenta) - 1);
        finanzas[id].numeroCuenta[sizeof(finanzas[id].numeroCuenta) - 1] = '\0';
        finanzas[id].numeroCuenta[20 - 1] = '\0';
    }

    //Editar banco (solo si el usuario lo confirma)
    printf("¿Cambiar banco? (s/n): ");
    char resp = getchar();
    limpiar_buffer();
    if (resp == 's' || resp == 'S') {
        seleccionarBanco(finanzas[id].banco, 50);
    }

    //Editar fecha con validación
    printf("Nueva fecha (actual: %s): ", finanzas[id].fechaTransaccion);
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = 0;
    if (strlen(temp) > 0 && validarFecha(temp)) {
        strncpy(finanzas[id].fechaTransaccion, temp, 10);
        finanzas[id].fechaTransaccion[10] = '\0';
    } else if (strlen(temp) > 0) {
        printf("Fecha inválida. No se actualizó.\n");
    }

    //Editar ingresos 
    printf("Nuevos ingresos (actual: %.0f): ", finanzas[id].ingresos);
    double nuevo;
    if (scanf("%lf", &nuevo) == 1) finanzas[id].ingresos = nuevo;
    limpiar_buffer();

    //Editar egresos 
    printf("Nuevos egresos (actual: %.0f): ", finanzas[id].egresos);
    if (scanf("%lf", &nuevo) == 1) finanzas[id].egresos = nuevo;
    limpiar_buffer();

    //Recalcular saldo 
    finanzas[id].saldoActual = finanzas[id].ingresos - finanzas[id].egresos;
    printf("Finanza actualizada.\n");
}

//Elimina un registro financiero por ID
void eliminarFinanzas(void) {
    if (totalFinanzas == 0) {
        printf("No hay registros para eliminar.\n");
        return;
    }

    int id;
    printf("ID a eliminar (1 a %d): ", totalFinanzas);
    if (scanf("%d", &id) != 1 || id < 1 || id > totalFinanzas) {
        printf("ID inválido.\n");
        limpiar_buffer();
        return;
    }
    limpiar_buffer();

    printf("¿Está seguro? (s/n): ");
    char confirm = getchar();
    limpiar_buffer();

    if (confirm == 's' || confirm == 'S') {
        for (int i = id - 1; i < totalFinanzas - 1; i++) {
            finanzas[i] = finanzas[i + 1];
        }
        totalFinanzas--;
        printf("Registro eliminado.\n");
    } else {
        printf("Operación cancelada.\n");
    }
}

//Muestra un monto en ambos formatos: pesos chilenos y dólares
void mostrarMontoEnCLPyUSD(double monto) {
    printf("$%.0f CLP | $%.2f USD\n", monto, monto / TASA_USD);
}
