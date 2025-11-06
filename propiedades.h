#ifndef PROPIEDADES_H
#define PROPIEDADES_H

#include "constante.h"  // Contiene #define MAX_REGISTROS 100

// Límites de cadenas
#define MAX_ROL          20   // Ej: "12345-67"
#define MAX_RUT          13   // Formato: "12.345.678-9"

// Estructura Propiedad
typedef struct {
    char rol[MAX_ROL];               
    int metrosConstruidos;           
    int anio;                        
    char torre;                      
    int numeroDepartamento;          
    int numeroPiezas;                
    int numeroBanios;                
    char rutAsociado[MAX_RUT];       
} Propiedad;

// Variables globales del módulo
extern Propiedad propiedades[MAX_REGISTROS];
extern int totalPropiedades;

// Prototipos de funciones
void menuPropiedades(void);
void agregarPropiedad(void);
void listarPropiedadesPorRut(const char* rut);
void editarPropiedad(void);
void eliminarPropiedad(void);
void eliminarPropiedadesPorRut(const char* rut); // para eliminación en cascada

#endif // PROPIEDADES_H
