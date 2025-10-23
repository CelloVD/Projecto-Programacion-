#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "finanzas.c"

//Funcion para entrar a nuestro menu principal del la empresa Bloomer.
void menuPrincipal(){
    int opcion;
    do{
        printf("\n------Sistema Bloomer------\n");
        printf("1. Miembros y menú principal\n");
        printf("2. Finanzas\n");
        printf("3. Propiedades\n");
        printf("4. Vehículos\n");
        printf("5. Fondos mutuos\n");
        printf("6. Terrenos\n");
        printf("7. Agenda\n");
        printf("8. Beneficios\n");
        printf("0. Salir\n");
        printf("----------------------------\n");
        printf("Seleccione una opcion: ");

        if (scanf("%d", &opcion) != 1) { // Si el usuario ingresa algo que no es número, limpiamos el buffer
            while (getchar() != '\n');
            opcion = -1; // Opción inválida
        }

        switch (opcion){

        case 1:
            /* code */
            printf("Miembros y menu principal:");
            break;

        case 2:
            /* code */
            printf("Finanzas \n");
            finanzas();
            break;

        case 3:
            /* code */
            printf("Propiedades");
            break;

        case 4:
            /* code */
            printf("Vehiculos");
            break;

        case 5:
            /* code */
            printf("Fondos Mutuos");
            break;

        case 6:
            /* code */
            printf("Terreno");
            break;

        case 7:
            /* code */
            printf("Agenda");
            break;

        case 8:
            /* code */
            printf("Beneficios");
            break;

        case 0:
            printf("Saliendo del sistema. ¡Hasta pronto!\n");
            break;

        default:
            printf("Opcion invalida. Intente de nuevo.\n");
            break;
        }
    }while(opcion != 0);
}


int main() {
    menuPrincipal();
    return 0;
}

int nombre(char nombre){
    printf("Ingrese nombre:");
}