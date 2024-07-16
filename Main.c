#include <stdio.h>
#include <string.h>
#include "Lecturas.h"
#include "Operaciones.h"


int main() {
    int opcion;
    cargarDatos();

    char nombre[MAX_NOMBRE_PRODUCTO];
    int cantidad;
    float precio;
    

    do {
        printf("\nBienvenido a InventEdu\n");
        printf("Menu Principal:\n");
        printf("1. Productos\n");
        printf("2. Clientes\n");
        printf("3. Facturar\n");
        printf("0. Salir\n");
        opcion = leerEnteroEntre("Ingrese una opcion: ", 0, 3);

        switch (opcion) {
            case 1: {
                int subopcion;
                do {
                    printf("\nMenu Productos:\n");
                    printf("1. Ingresar Producto\n");
                    printf("2. Modificar Producto\n");
                    printf("3. Eliminar Producto\n");
                    printf("4. Listar Productos\n");
                    printf("0. Regresar al Menu Principal\n");
                    subopcion = leerEnteroEntre("Ingrese una opcion: ", 0, 4);

                    switch (subopcion) {
                        case 1:
                            ingresarProducto(nombre, &cantidad, &precio);
                            break;
                        case 2:
                            modificarProducto(nombre, &cantidad, &precio);
                            break;
                        case 3:
                            eliminarProducto(nombre, &contador_productos, nombres_productos, cantidades_productos, precios_productos);
                            break;
                        case 4:
                            listarProductos(&contador_productos, nombres_productos, cantidades_productos, precios_productos);
                            break;
                        case 0:
                            printf("Regresando al Menu Principal...\n");
                            break;
                        default:
                            printf("Opcion no valida.\n");
                    }
                } while (subopcion != 0);
                break;
            }
            case 2: {
                int subopcion;
                do {
                    printf("\nMenu Clientes:\n");
                    printf("1. Ingresar Cliente\n");
                    printf("2. Modificar Cliente\n");
                    printf("3. Listar Clientes\n");
                    printf("0. Regresar al Menu Principal\n");
                    subopcion = leerEnteroEntre("Ingrese una opcion: ", 0, 3);

                    switch (subopcion) {
                        case 1:
                            ingresarCliente(&contador_clientes, cedulas_clientes, nombres_clientes);
                            break;
                        case 2:
                            modificarCliente(&contador_clientes, cedulas_clientes, nombres_clientes);
                            break;
                        case 3:
                            listarClientes(&contador_clientes, cedulas_clientes, nombres_clientes);
                            break;
                        case 0:
                            printf("Regresando al Menu Principal...\n");
                            break;
                        default:
                            printf("Opcion no valida.\n");
                    }
                } while (subopcion != 0);
                break;
            }
            case 3: {
                int subopcion;
                do {
                    printf("\nMenu Facturacion:\n");
                    printf("1. Facturar\n");
                    printf("2. Listar Facturas\n");
                    printf("0. Regresar al Menu Principal\n");
                    subopcion = leerEnteroEntre("Ingrese una opcion: ", 0, 2);

                    switch (subopcion) {
                        case 1:
                            facturar();
                            break;
                        case 2:
                            listarFacturas();
                            break;
                        case 0:
                            printf("Regresando al Menu Principal...\n");
                            break;
                        default:
                            printf("Opcion no valida.\n");
                    }
                } while (subopcion != 0);
                break;
            }
            case 0:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while (opcion != 0);

    return 0;
}




























































char nombres_productos[MAX_PRODUCTOS][MAX_NOMBRE_PRODUCTO];
int cantidades_productos[MAX_PRODUCTOS];
float precios_productos[MAX_PRODUCTOS];
int contador_productos = 0;

char cedulas_clientes[MAX_CLIENTES][11];
char nombres_clientes[MAX_CLIENTES][50];
int contador_clientes = 0;

char fechas_facturas[MAX_FACTURAS][11];
char cedulas_facturas[MAX_FACTURAS][11];
char nombres_facturas[MAX_FACTURAS][50];
int cantidades_factura[MAX_FACTURAS][MAX_PRODUCTOS];
float precios_factura[MAX_FACTURAS][MAX_PRODUCTOS];
int cantidad_detalles_factura[MAX_FACTURAS];
float valor_total_factura[MAX_FACTURAS];
int contador_facturas = 0;





































