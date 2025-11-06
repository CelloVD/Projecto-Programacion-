#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "vehiculo.h"
#include "validaciones.h"
#include "constante.h"

void menuVehiculos(){
int opcion, c;
  
    do{
        printf("\n------Vehículos------\n");
        printf("1. Agregar vehículo\n");
        printf("2. Editar vehículo\n");
        printf("3. Eliminar vehículo\n");
        printf("4. Listar vehículos por RUT\n");
        printf("0. Volver al menú principal\n");
        printf("----------------------------\n");
        printf("Seleccione una opción: ");

        if (scanf("%d", &opcion) != 1) { //Si no es número
            limpiar_buffer();
            opcion = -1;

        }else {
            c = getchar(); //Lee siguiente caracter

            if (c != '\n' && c != EOF) { //Si hay caracter(es) sobrantes
                limpiar_buffer();
                opcion = -1;

            } else if (opcion < 0 || opcion > 4) { //Si está fuera del rango
                opcion = -1;
            }
        }

        //Discriminar op

        switch (opcion){

            case 1:
                agregarVehiculo();
                break;

            case 2:
                editarVehiculo();
                break;

            case 3:
                eliminarVehiculo();
                break;

            case 4: 
                listarVehiculosPorRut();
                break;

            case 0:
                break;

            default:
                printf("Opción inválida. Intente nuevamente.\n");
                break;

        }

    } while (opcion!=0);

}
