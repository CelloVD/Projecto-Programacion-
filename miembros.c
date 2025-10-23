#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    char nombre[20];
    char apellido[20];
    int rut;
    char direccion[20];
    int edad;
    int nacimiento;
    char sexo[12];
    bool ecivil;
    char email[40];
}member;

int miembros(){
    member m;
    do{
        printf("Ingrese Nombre");
        fgets(m.nombre, sizeof(m.nombre), stdin);
        m.nombre[strcspn(m.nombre, "\n")] = '\0';
        printf("Ingrese Apellido");
        fgets(m.apellido, sizeof(m.apellido), stdin);
        m.apellido[strcspn(m.apellido, "\n")] = '\0';
        printf("Ingrese RUT");
        scanf("%d", &m.rut);

    }
}