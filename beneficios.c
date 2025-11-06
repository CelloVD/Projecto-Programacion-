#include <stdio.h>
#include <string.h>
#include "beneficios.h"



void Fecha(bficio *f) {
    int anio, mes, dia;

    // Año. Validado, impidiendo que existan valores de ]-inf,0[ y ]2025, +inf[
    do {
        printf("Ingrese año vencimiento: ");
        scanf("%d", &anio);
        if (anio < 0 || anio > 2030)
            printf("Ingrese un año valido.\n");
    } while (anio < 0 || anio > 2030);

    // Mes. Validado, impidiendo que existan valores de ]-inf,0[ y ]12, +inf[
    do {
        printf("Ingrese mes (1-12): ");
        scanf("%d", &mes);
        if (mes < 1 || mes > 12)
            printf("Ingrese un mes valido.\n");
    } while (mes < 1 || mes > 12);

    // Día. Aca nos preocupamos de validar correctamente la cantidad de dias que tiene cada mes, contando incluso el caso de un año bisiesto
    int diasMax;
    switch (mes) {
        //Enero, Marzo, Mayo, Julio, Agosto, Octubre y Diciembre
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            diasMax = 31; 
            break;
        //Abril, Junio, Septiembre, Noviembre
        case 4: case 6: case 9: case 11:
            diasMax = 30; 
            break;
        case 2:
            if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0))
                diasMax = 29;  // Febrero bisiesto
            else
                diasMax = 28; // Febrero normal
            break;
    }

    do {
        printf("Ingrese dia (1-%d): ", diasMax);
        scanf("%d", &dia);
        if (dia < 1 || dia > diasMax)
            printf("Ingrese un dia valido.\n");
    } while (dia < 1 || dia > diasMax);

    // Guardar la fecha en formato AAAAMMDD en el struct
    (*f).vigencia = anio * 10000 + mes * 100 + dia;
}

int beneficios() {
    bficio datos;
    //Ingreso de Datos
    printf("Ingrese ID: ");
    fgets(datos.id, sizeof(datos.id), stdin);
    datos.id[strcspn(datos.id, "\n")] = '\0';
    getchar();
    printf("Ingrese nombre de Caja de Compensacion: ");
    fgets(datos.cajaComp, sizeof(datos.cajaComp), stdin);
    datos.cajaComp[strcspn(datos.cajaComp, "\n")] = '\0';
    printf("Ingrese nombre detalle: ");
    fgets(datos.detalle, sizeof(datos.detalle), stdin);
    datos.detalle[strcspn(datos.detalle, "\n")] = '\0';
    printf("Ingrese dcto: ");
    scanf("%d", &datos.dcto);
    printf("Ingrese condicion: ");
    fgets(datos.cond, sizeof(datos.cond), stdin);
    datos.cond[strcspn(datos.cond, "\n")] = '\0';
    printf("Ingrese saldo: ");
    scanf("%d", &datos.cargaF);
    printf("Ingrese RUT: ");
    Fecha(&datos);

    // Mostrar datos
    printf("\n--- Datos ingresados ---\n");
    printf("Cuenta: %d\n", datos.id);
    printf("cajaComp: %s\n", datos.cajaComp);
    printf("Fecha: %d\n", datos.vigencia);
    printf("dcto: %d\n", datos.dcto);
    printf("Egresos: %d\n", datos.cond);
    printf("Saldo: %d\n", datos.cargaF);
    printf("RUT: %d\n", datos.vigencia);
    
    return 0;
}