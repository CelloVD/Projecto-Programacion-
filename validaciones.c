#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "validaciones.h"

void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int sumaRecursiva(int rut, int multiplicador) {
    if (rut == 0){
        return 0;
    }
    int digito = rut % 10;
    int nuevo_mult = (multiplicador == 7) ? 2 : multiplicador + 1; //operador ternario 
    return digito * multiplicador + sumaRecursiva(rut / 10, nuevo_mult);
}

int calcularDV(int rut) {
    int suma = sumaRecursiva(rut, 2); //ejemplo 12.345.678-9 (8*2)+(7*3)+(6*4)+(5*5)+(4*6)+(3*7)+(2*2)+(1*3)
    int resto = suma % 11; //Resto de dividir la suma entre 11
    int resultado = 11 - resto; //Calcula el valor base  

    if (resultado == 11)
        return 0; //El rut termina en 0
    else if (resultado == 10)
        return -1; //El rut termina en k
    else
        return resultado;
}

//Validar un RUT (ejemplo: "12.345.678-9" o "12345678-9")
int validarRut(const char* rutCompleto) {
    int rut;
    char dvIngresado; //digito verificador 
    char limpio[20]; //Almacena el rut sin puntos ni espacio
    int j = 0;

    //Quitar puntos y espacios
    for (int i = 0; rutCompleto[i] != '\0'; i++) {
        if (rutCompleto[i] != '.' && rutCompleto[i] != ' ')
            limpio[j++] = rutCompleto[i];
    }
    limpio[j] = '\0';

    //Separar número y dígito verificador
    if (sscanf(limpio, "%d-%c", &rut, &dvIngresado) != 2)
        return 0; // formato inválido

    dvIngresado = toupper(dvIngresado); //convierte el digito verificar en mayuscula por si es "k"

    int dvCalculado = calcularDV(rut);
    char dvCorrecto = (dvCalculado == -1) ? 'K' : dvCalculado + '0';

    return dvIngresado == dvCorrecto;
}

int validarFecha(const char *fecha) {
    if (!fecha || strlen(fecha) != 10) // Formato dd/mm/aaaa
        return 0;

    int dia, mes, anio;

    // Escanea la fecha, debe tener formato exacto con /
    if (sscanf(fecha, "%2d/%2d/%4d", &dia, &mes, &anio) != 3)
        return 0;

    if (anio < 0 || anio > 2025) // Rango de año
        return 0;

    if (mes < 1 || mes > 12) // Rango de mes
        return 0;

    // Determinar la cantidad máxima de días en el mes
    int diasMax;
    switch (mes) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            diasMax = 31; break;
        case 4: case 6: case 9: case 11:
            diasMax = 30; break;
        case 2:
            // Año bisiesto
            if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0))
                diasMax = 29;
            else
                diasMax = 28;
            break;
        default:
            return 0;
    }

    if (dia < 1 || dia > diasMax)
        return 0;

    return 1; // Fecha válida
}

int validarEmail(const char *email) {
    if (!email || strlen(email) == 0){
        return 0;
    }
    // No permitir espacios
    for (int i = 0; email[i]; i++) {
        if (isspace(email[i])){
            return 0;
        }
    }
    // Debe haber exactamente un '@'
    const char *arroba = strchr(email, '@');
    if (!arroba){
        return 0;
    }
    if (strchr(arroba + 1, '@')){// más de un '@'
        return 0;
    } 
    // Debe haber al menos un '.' después del '@' y al menos 2 caracteres al final
    const char *punto = strchr(arroba, '.');
    if (!punto || strlen(punto) < 3){
        return 0;
    }
    return 1; // email válido
}
