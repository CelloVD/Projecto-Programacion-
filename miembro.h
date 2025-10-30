#ifndef MIEMBRO_H
#define MIEMBRO_H
#include "constante.h"


typedef struct {
    char nombre[20];
    char apellido[20];
    char rut[20];               // "12.345.678-9"
    char direccion[60];         
    int edad;
    char fechaNacimiento[11];   // "dd/mm/aaaa"
    char sexo;                  
    int casado;                 
    char email[40];
} Miembro;

int crearMiembro(Miembro miembro[], int *total);
int menuMiembro(Miembro miembro[], int *total);

#endif
