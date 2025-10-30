#include <stdio.h>
#include <string.h>

//Struct para propiedades
typedef struct{
    int Rol;
    int m2;
    int anio;
    char torre[1];
    char dpto[30];
    int nPieza;
    int nBano;
    int rut;
}propiedad;

int propiedades() {
    propiedad datop;
    printf("Ingrese Rol: ");
    scanf("%d", &datop.Rol);
    getchar();
    printf("Ingresar metros cuadrados de terreno: ");
    scanf("%d", &datop.m2);
    printf("Ingresar año de adquisicion: ");
    scanf("%d", &datop.anio);
    printf("Ingrese Torre (A - H): ");
    fgets(datop.torre, sizeof(datop.torre), stdin);
    datop.torre[strcspn(datop.torre, "\n")] = '\0';
    printf("Ingrese Departamento: ");
    fgets(datop.dpto, sizeof(datop.dpto), stdin);
    datop.dpto[strcspn(datop.dpto, "\n")] = '\0';
    printf("Ingresar numero de piezas: ");
    scanf("%d", &datop.nPieza);
    printf("Ingresar numero de baños: ");
    scanf("%d", &datop.nBano);
    printf("Ingresar RUT: ");
    scanf("%d", &datop.rut);

    // Mostrar datop
    printf("\n--- datop ingresados ---\n");
    printf("Rol: %d\n", datop.Rol);
    printf("Metros cuadrados: %s\n", datop.m2);
    printf("Año de aquisicion: %d\n", datop.anio);
    printf("Torre: %d\n", datop.torre);
    printf("Departamento: %d\n", datop.dpto);
    printf("Numero de piezas: %d\n", datop.nPieza);
    printf("Numero de baños: %d\n", datop.nBano);
    printf("RUT: %d\n", datop.rut);

    return 0;
}
