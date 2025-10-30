#include <stdio.h> //Entrada/Salida estándar
#include <string.h> //Manipulación de cadena (strcpy, strcmp, etc....)
#include <ctype.h> //Funciones para caracteres (toupper, etc.....)
#include "miembro.h" //incluimos la cabecera para acceder a la struct y prototipos
#include "validaciones.h"


int crearMiembro(Miembro miembro[], int *total) {
    // Verificar límite de 100 miembros
    if (*total >= MAX_REGISTROS) {
        printf("Límite de 100 miembros alcanzado.\n");
        return 0;
    }

    Miembro nuevo;
    char buffer[100]; // Buffer general para lectura segura

    do {
        printf("Nombre (máx. 19 caracteres): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        if (strlen(buffer) == 0) {
            printf("El nombre no puede estar vacío.\n");
        } else if (strlen(buffer) >= sizeof(nuevo.nombre)) {
            printf("Nombre demasiado largo.\n");
        } else {
            strcpy(nuevo.nombre, buffer);
            break;
        }
    } while (1);

    do {
        printf("Apellido (máx. 19 caracteres): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        if (strlen(buffer) == 0) {
            printf("El apellido no puede estar vacío.\n");
        } else if (strlen(buffer) >= sizeof(nuevo.apellido)) {
            printf("Apellido demasiado largo.\n");
        } else {
            strcpy(nuevo.apellido, buffer);
            break;
        }
    } while (1);

    do {
        printf("RUT (ej: 12345678-9): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        if (strlen(buffer) == 0) {
            printf("El RUT no puede estar vacío.\n");
        } else if (!validarRut(buffer)) {
            printf("RUT inválido (dígito verificador incorrecto).\n");
        } else {
            strcpy(nuevo.rut, buffer);
            break;
        }
    } while (1);

    do {
        printf("Dirección (máx. 59 caracteres): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        if (strlen(buffer) == 0) {
            printf("La dirección no puede estar vacía.\n");
        } else if (strlen(buffer) >= sizeof(nuevo.direccion)) {
            printf("Dirección demasiado larga.\n");
        } else {
            strcpy(nuevo.direccion, buffer);
            break;
        }
    } while (1);

    do {
        printf("Edad (1-120): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        int edad;
        if (sscanf(buffer, "%d", &edad) == 1 && edad >= 1 && edad <= 120) { //sscanf convierte de texto a un numero u otro tipo de dato
            nuevo.edad = edad;
            break;
        }
        printf("Ingrese una edad válida entre 1 y 120.\n");
    } while (1);
    
    do {
        printf("Fecha de nacimiento (dd/mm/aaaa): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        if (strlen(buffer) == 0) {
            printf("La fecha no puede estar vacía.\n");
        } else if (!validarFecha(buffer)) {
            printf("Fecha inválida.\n");
        } else {
            strcpy(nuevo.fechaNacimiento, buffer);
            break;
        }
    } while (1);

    do {
        printf("Sexo (M/F): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        if (strlen(buffer) == 1) {
            char s = toupper(buffer[0]);
            if (s == 'M' || s == 'F') {
                nuevo.sexo = s;
                break;
            }
        }
        printf("Ingrese solo M o F.\n");
    } while (1);

    do {
        printf("¿Casado? (1=Sí / 0=No): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        int casado;
        if (sscanf(buffer, "%d", &casado) == 1 && (casado == 0 || casado == 1)) {
            nuevo.casado = casado;
            break;
        }
        printf("Ingrese 1 para Sí o 0 para No.\n");
    } while (1);

    do {
        printf("Email (máx. 39 caracteres): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        if (strlen(buffer) == 0) {
            printf("El email no puede estar vacío.\n");
        } else if (strlen(buffer) >= sizeof(nuevo.email)) {
            printf("Email demasiado largo.\n");
        } else if (!validarEmail(buffer)) {
            printf("Email inválido (debe contener '@' y un dominio con '.').\n");
        } else {
            strcpy(nuevo.email, buffer);
            break;
        }
    } while (1);

    // === GUARDAR MIEMBRO ===
    miembro[(*total)++] = nuevo;
    printf("Miembro registrado con éxito.\n");
    return 1;
}

int menuMiembro(Miembro miembro[], int *total){
    int opcion, c;
    do{
        printf("\n------ Módulo Miembros -----\n");
        printf("1. Crear Clientes\n");
        printf("2. Editar Clientes\n");
        printf("3. Eliminar Clientes\n");
        printf("4. Listar Clientes\n");
        printf("5. Volver al menú principal\n");
        printf("------------------------------\n");
        printf("Seleccione una opcion: ");
        //Valida opción
        if (scanf("%d", &opcion) != 1) {    //Si no es número
            limpiar_buffer();
            opcion = -1;

        } else {
            c = getchar(); //Lee siguiente caracter

            if (c != '\n' && c != EOF) {    //Si hay caracter(es) sobrantes
                limpiar_buffer();
                opcion = -1;

            } else if (opcion < 0 || opcion > 8) { //Si está fuera del rango
                opcion = -1;
            }
        }

        //Discriminar op
        switch (opcion){
        case 1:
            crearMiembro(miembro, total);
            break;
        case 2:
            /* code */
            break;
        case 3:
            /* code */
            break;
        case 4:
            /* code */
            break;
        case 5:
            return 0;
            break;
        
        default:
            printf("Opción inválida. \n");
            break;
        }
    }while (opcion != 5);
    return 0;
}
