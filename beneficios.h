#ifndef BENEFICIOS_H
#define BENEFICIOS_H



//Struct para Beneficios
typedef struct{
    char id[13];
    char cajaComp[35];
    char detalle[40];
    int dcto;
    char cond[50];
    int cargaF;
    int vigencia;
}bficio;

extern bficio beneficios[MAX_REGISTROS];



#endif