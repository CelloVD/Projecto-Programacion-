#include <stdio.h>
#include <string.h>

//Struct para finanzas
typedef struct{
    int numCuenta;
    char banco[15];
    int fecha;
    int ingresos;
    int egresos;
    int saldo;
    int rut;
}finanza;


void Fecha(finanza *f) {
    int anio, mes, dia;

    // Año. Validado, impidiendo que existan valores de ]-inf,0[ y ]2025, +inf[
    do {
        printf("Ingrese año: ");
        scanf("%d", &anio);
        if (anio < 0 || anio > 2025)
            printf("Ingrese un año valido.\n");
    } while (anio < 0 || anio > 2025);

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
    (*f).fecha = anio * 10000 + mes * 100 + dia;
}

int finanzas() {
    finanza datos;
    //Ingreso de Datos
    printf("Ingrese numero de cuenta: ");
    scanf("%d", &datos.numCuenta);
    getchar();
    printf("Ingrese nombre del banco: ");
    fgets(datos.banco, sizeof(datos.banco), stdin);
    datos.banco[strcspn(datos.banco, "\n")] = '\0';
    Fecha(&datos);
    printf("Ingrese ingresos: ");
    scanf("%d", &datos.ingresos);
    printf("Ingrese egresos: ");
    scanf("%d", &datos.egresos);
    printf("Ingrese saldo: ");
    scanf("%d", &datos.saldo);
    printf("Ingrese RUT: ");
    scanf("%d", &datos.rut);

    // Mostrar datos
    printf("\n--- Datos ingresados ---\n");
    printf("Cuenta: %d\n", datos.numCuenta);
    printf("Banco: %s\n", datos.banco);
    printf("Fecha: %d\n", datos.fecha);
    printf("Ingresos: %d\n", datos.ingresos);
    printf("Egresos: %d\n", datos.egresos);
    printf("Saldo: %d\n", datos.saldo);
    printf("RUT: %d\n", datos.rut);

    return 0;
}