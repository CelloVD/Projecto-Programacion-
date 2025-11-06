#include "bloomer.h"

//Funcion para entrar a nuestro menu principal del la empresa Bloomer.
void menuPrincipal(){

    int opcion, c;
    
    do{
        printf("\n------Sistema Bloomer------\n");
        printf("1. Miembros\n");
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
            menuMiembro();
            printf("Miembros y menu principal:");
            break;

        case 2:
            menuFinanzas();
            printf("Finanzas \n");
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

int main(){
    menuPrincipal();
    return 0;
}
