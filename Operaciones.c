#include <stdio.h>
#include <string.h>
#include "Lecturas.h"
#include "Operaciones.h"



void cargarDatos() {
    FILE *archivo; //Declara un puntero a una estructura FILE, que se utilizará para manejar archivos.
    char nombre_producto[MAX_NOMBRE_PRODUCTO];
    int cantidad;
    float precio;

    
    archivo = fopen("productos.txt", "r"); //Abre el archivo productos.txt en modo de lectura "r"
    if (archivo != NULL) { //Comprueba si el archivo se abrió correctamente
        while (fscanf(archivo, "%s %d %f", nombre_producto, &cantidad, &precio) == 3) { 

            //Lee datos del archivo productos.txt en el formato nombre_producto cantidad precio y 
            //los almacena en las variables nombre_producto, cantidad y precio. El bucle continúa 
            //mientras se puedan leer tres valores correctamente.

            strcpy(nombres_productos[contador_productos], nombre_producto);
            cantidades_productos[contador_productos] = cantidad;
            precios_productos[contador_productos] = precio;
            contador_productos++;

            //Copia el nombre_producto al arreglo nombres_productos, asigna cantidad y precio a los arreglos 
            //cantidades_productos y precios_productos, respectivamente, 
            //en la posición indicada por contador_productos. Luego, incrementa contador_productos para la siguiente iteración.
        }
        fclose(archivo); //Cierra el archivo productos.txt
    }

    
    archivo = fopen("clientes.txt", "r");
    if (archivo != NULL) {
        while (fscanf(archivo, "%s %s", cedulas_clientes[contador_clientes], nombres_clientes[contador_clientes]) == 2) {
            contador_clientes++;

            //Lee datos del archivo clientes.txt en el formato cedula nombre y los almacena en los arreglos 
            //cedulas_clientes y nombres_clientes,
            // respectivamente. El bucle continúa mientras se puedan leer dos valores correctamente.
        }
        fclose(archivo); // Cierra el archivo productos.txt
    }

    
    archivo = fopen("facturas.txt", "r");
    if (archivo != NULL) {
        while (fscanf(archivo, "%s %s %s", fechas_facturas[contador_facturas], cedulas_facturas[contador_facturas], nombres_facturas[contador_facturas]) == 3) {
            int cantidad_detalles;
            fscanf(archivo, "%d", &cantidad_detalles);
            cantidad_detalles_factura[contador_facturas] = cantidad_detalles;
            for (int i = 0; i < cantidad_detalles; i++) {
                fscanf(archivo, "%d %f", &cantidades_factura[contador_facturas][i], &precios_factura[contador_facturas][i]);
            }
            fscanf(archivo, "%f", &valor_total_factura[contador_facturas]);
            contador_facturas++;
        }
        fclose(archivo);
    }
}

void actualizarArchivo(const char* archivoNombre, const char* modo, void (*escribirDatos)()) {
    FILE *archivo = fopen(archivoNombre, modo);
    if (archivo != NULL) {
        escribirDatos(archivo);
        fclose(archivo);
    } else {
        printf("No se pudo abrir el archivo %s\n", archivoNombre);
    }
}

void escribirProductos(FILE* archivo) {
    for (int i = 0; i < contador_productos; i++) {
        fprintf(archivo, "%s %d %.2f\n", nombres_productos[i], cantidades_productos[i], precios_productos[i]);
    }
}

//Este bucle recorrerá todos los productos almacenados

void escribirClientes(FILE* archivo) {
    for (int i = 0; i < contador_clientes; i++) {
        fprintf(archivo, "%s %s\n", cedulas_clientes[i], nombres_clientes[i]);
    }
}

//Dentro del bucle, fprintf escribe los datos de cada producto en el archivo apuntado por archivo

void escribirFacturas(FILE* archivo) {
    for (int i = 0; i < contador_facturas; i++) {
        fprintf(archivo, "%s %s %s\n", fechas_facturas[i], cedulas_facturas[i], nombres_facturas[i]);
        fprintf(archivo, "%d\n", cantidad_detalles_factura[i]);
        for (int j = 0; j < cantidad_detalles_factura[i]; j++) {
            fprintf(archivo, "%d %.2f\n", cantidades_factura[i][j], precios_factura[i][j]);
        }
        fprintf(archivo, "%.2f\n", valor_total_factura[i]);
    }
}

// Funciones para manejar productos
void ingresarProducto(char *nombre, int *cantidad, float *precio) {
    if (contador_productos >= MAX_PRODUCTOS) {
        printf("No se pueden agregar más productos.\n");
        return;
    }

    printf("Ingrese el nombre del producto: ");
    scanf("%s", nombre);

    // Verificar que no exista otro producto con el mismo nombre
    for (int i = 0; i < contador_productos; i++) {
        if (strcmp(nombres_productos[i], nombre) == 0) {
            printf("El producto ya existe.\n");
            return;
        }
    }

    strcpy(nombres_productos[contador_productos], nombre);
    *cantidad = leerEnteroPositivo("Ingrese la cantidad del producto: ");
    *precio = leerFlotantePositivo("Ingrese el precio del producto: ");
    
    cantidades_productos[contador_productos] = *cantidad;
    precios_productos[contador_productos] = *precio;

    contador_productos++;
    printf("Producto agregado exitosamente.\n");
    actualizarArchivo("productos.txt", "w", escribirProductos);
}


void modificarProducto(char *nombre, int *cantidad, float *precio) {
    if (contador_productos == 0) {
        printf("No hay productos para modificar.\n");
        return;
    }

    printf("Ingrese el nombre del producto a modificar: ");
    scanf("%s", nombre);

    for (int i = 0; i < contador_productos; i++) {
        if (strcmp(nombres_productos[i], nombre) == 0) {
            *cantidad = leerEnteroPositivo("Ingrese la nueva cantidad del producto: ");
            *precio = leerFlotantePositivo("Ingrese el nuevo precio del producto: ");

            cantidades_productos[i] = *cantidad;
            precios_productos[i] = *precio;

            printf("Producto modificado exitosamente.\n");
            actualizarArchivo("productos.txt", "w", escribirProductos);
            return;
        }
    }
    printf("Producto no encontrado.\n");
}


void eliminarProducto(char *nombre, int *contador_productos, char nombres_productos[][MAX_NOMBRE_PRODUCTO], int *cantidades_productos, float *precios_productos) {
    if (*contador_productos == 0) {
        printf("No hay productos para eliminar.\n");
        return;
    }

    printf("Ingrese el nombre del producto a eliminar: ");
    scanf("%s", nombre);

    for (int i = 0; i < *contador_productos; i++) {
        if (strcmp(nombres_productos[i], nombre) == 0) {
            for (int j = i; j < *contador_productos - 1; j++) {
                strcpy(nombres_productos[j], nombres_productos[j + 1]);
                cantidades_productos[j] = cantidades_productos[j + 1];
                precios_productos[j] = precios_productos[j + 1];
            }
            (*contador_productos)--;
            printf("Producto eliminado exitosamente.\n");
            actualizarArchivo("productos.txt", "w", escribirProductos);
            return;
        }
    }
    printf("Producto no encontrado.\n");
}


void listarProductos(int *contador_productos, char (*nombres_productos)[MAX_NOMBRE_PRODUCTO], int *cantidades_productos, float *precios_productos) {
    if (*contador_productos == 0) {
        printf("No hay productos para mostrar.\n");
        return;
    }

    for (int i = 0; i < *contador_productos; i++) {
        printf("Nombre: %s, Cantidad: %d, Precio: %.2f\n", nombres_productos[i], cantidades_productos[i], precios_productos[i]);
    }
}


int validarCedula(const char* cedula) {
    int longitud = strlen(cedula);

    if (longitud != 10) {
        return 0;
    }

    int provincia = (cedula[0] - '0') * 10 + (cedula[1] - '0');
    if (provincia < 0 || provincia > 24) {
        return 0;
    }

    int tercer_digito = cedula[2] - '0';
    if (tercer_digito < 0 || tercer_digito > 5) {
        return 0;
    }

    int suma_impares = 0;
    int suma_pares = 0;

    for (int i = 0; i < 9; i++) {
        int digito = cedula[i] - '0';
        
        if (i % 2 == 0) {
            int producto = digito * 2;
            if (producto > 9) {
                producto -= 9;
            }
            suma_impares += producto;
        } else {
            suma_pares += digito;
        }
    }

    int suma_total = suma_impares + suma_pares;
    int digito_verificador = cedula[9] - '0';
    int modulo_10 = suma_total % 10;
    
    int digito_calculado;
    if (modulo_10 == 0) {
        digito_calculado = 0;
    } else {
        digito_calculado = 10 - modulo_10;
    }

    return digito_verificador == digito_calculado;
}


void ingresarCliente(int *contador_clientes, char (*cedulas_clientes)[11], char (*nombres_clientes)[MAX_NOMBRE_CLIENTE]) {
    if (*contador_clientes >= MAX_FACTURAS) {
        printf("No se pueden agregar más clientes.\n");
        return;
    }

    char cedula[11];
    printf("Ingrese la cédula del cliente: ");
    scanf("%s", cedula);

    if (!validarCedula(cedula)) {
        printf("La cédula %s es inválida.\n", cedula);
        return;
    }

    for (int i = 0; i < *contador_clientes; i++) {
        if (strcmp(cedulas_clientes[i], cedula) == 0) {
            printf("El cliente ya existe.\n");
            return;
        }
    }

    strcpy(cedulas_clientes[*contador_clientes], cedula);
    printf("Ingrese el nombre del cliente: ");
    scanf("%s", nombres_clientes[*contador_clientes]);

    (*contador_clientes)++;
    printf("Cliente agregado exitosamente.\n");
    actualizarArchivo("clientes.txt", "w", escribirClientes);
}



void modificarCliente(int *contador_clientes, char (*cedulas_clientes)[11], char (*nombres_clientes)[MAX_NOMBRE_CLIENTE]) {
    if (*contador_clientes == 0) {
        printf("No hay clientes para modificar.\n");
        return;
    }

    char cedula[11];
    printf("Ingrese la cedula del cliente a modificar: ");
    scanf("%s", cedula);

    for (int i = 0; i < *contador_clientes; i++) {
        if (strcmp(cedulas_clientes[i], cedula) == 0) {
            printf("Ingrese el nuevo nombre del cliente: ");
            scanf("%s", nombres_clientes[i]);
            printf("Cliente modificado exitosamente.\n");
            actualizarArchivo("clientes.txt", "w", escribirClientes);
            return;
        }
    }
    printf("Cliente no encontrado.\n");
}

void listarClientes(int *contador_clientes, char (*cedulas_clientes)[11], char (*nombres_clientes)[MAX_NOMBRE_CLIENTE]) {
    if (*contador_clientes == 0) {
        printf("No hay clientes para mostrar.\n");
        return;
    }

    for (int i = 0; i < *contador_clientes; i++) {
        printf("Cedula: %s, Nombre: %s\n", cedulas_clientes[i], nombres_clientes[i]);
    }
}

// Funciones para manejar facturas
void facturar() {
    if (contador_clientes == 0) {
        printf("No hay clientes para facturar.\n");
        return;
    }

    if (contador_productos == 0) {
        printf("No hay productos para facturar.\n");
        return;
    }

    char cedula_cliente[11];
    printf("Ingrese la cedula del cliente: ");
    scanf("%s", cedula_cliente);

    int cliente_encontrado = 0;
    char nombre_cliente[50];
    for (int i = 0; i < contador_clientes; i++) {
        if (strcmp(cedulas_clientes[i], cedula_cliente) == 0) {
            cliente_encontrado = 1;
            strcpy(nombre_cliente, nombres_clientes[i]);
            break;
        }
    }

    if (!cliente_encontrado) {
        printf("Cliente no encontrado.\n");
        return;
    }

    char fecha[11];
    printf("Ingrese la fecha de la factura (dd/mm/aaaa): ");
    scanf("%s", fecha);

    if (contador_facturas >= MAX_FACTURAS) {
        printf("No se pueden agregar mas facturas.\n");
        return;
    }

    strcpy(nombres_facturas[contador_facturas], nombre_cliente);
    strcpy(cedulas_facturas[contador_facturas], cedula_cliente);
    strcpy(fechas_facturas[contador_facturas], fecha);

    int cantidad_productos_factura = 0;
    while (1) {
        printf("Desea ingresar un producto a la factura? (1. Si, 2. No): ");
        int continuar = leerEnteroEntre("Opcion: ", 1, 2);

        if (continuar == 2) {
            break;
        }

        if (cantidad_productos_factura >= MAX_PRODUCTOS) {
            printf("No se pueden agregar mas productos a la factura.\n");
            break;
        }

        printf("Ingrese el nombre del producto a facturar: ");
        char nombre_producto[MAX_NOMBRE_PRODUCTO];
        scanf("%s", nombre_producto);

        int producto_encontrado = 0;
        for (int i = 0; i < contador_productos; i++) {
            if (strcmp(nombres_productos[i], nombre_producto) == 0) {
                int cantidad_producto = leerEnteroPositivo("Cantidad: ");

                if (cantidad_producto > cantidades_productos[i]) {
                    printf("La cantidad solicitada supera el stock disponible.\n");
                } else {
                    cantidades_factura[contador_facturas][cantidad_productos_factura] = cantidad_producto;
                    precios_factura[contador_facturas][cantidad_productos_factura] = precios_productos[i];
                    cantidad_detalles_factura[contador_facturas] = cantidad_productos_factura + 1;
                    valor_total_factura[contador_facturas] += cantidad_producto * precios_productos[i];
                    cantidades_productos[i] -= cantidad_producto; // <--- Actualiza el inventario aquí
                    cantidad_productos_factura++;
                    producto_encontrado = 1;
                }
                break;
            }
        }

        if (!producto_encontrado) {
            printf("Producto no encontrado.\n");
        }
    }

    if (cantidad_productos_factura == 0) {
        printf("No se ingresaron productos para la factura.\n");
        return;
    }

    contador_facturas++;
    printf("Factura agregada exitosamente.\n");

    int ver_factura;
    printf("Desea ver la factura?\n1. Si\n2. No\nIngrese una opcion: ");
    ver_factura = leerEnteroEntre("Opcion: ", 1, 2);

    if (ver_factura == 1) {
        listarFacturas();
    }

    // Guardar cambios en el archivo de productos
    actualizarArchivo("productos.txt", "w", escribirProductos); // <--- Actualiza el archivo aquí
    // Guardar cambios en el archivo de facturas
    actualizarArchivo("facturas.txt", "w", escribirFacturas);
}


void listarFacturas() {
    if (contador_facturas == 0) {
        printf("No hay facturas para mostrar.\n");
        return;
    }

    for (int i = 0; i < contador_facturas; i++) {
        printf("\nFactura %d\n", i + 1);
        printf("Fecha: %s\n", fechas_facturas[i]);
        printf("Cedula: %s\n", cedulas_facturas[i]);
        printf("Nombre: %s\n", nombres_facturas[i]);

        // Imprimir tabla de productos facturados
        printf("------------------------------------\n");
        printf("| Cantidad | Descripcion | Precio |\n");
        printf("------------------------------------\n");

        for (int j = 0; j < cantidad_detalles_factura[i]; j++) {
            printf("| %8d | %-10s | %6.2f |\n",
                   cantidades_factura[i][j],
                   nombres_productos[j],
                   precios_factura[i][j]);
        }

        printf("------------------------------------\n");
        printf("| Total           | %6.2f |\n", valor_total_factura[i]);
        printf("------------------------------------\n");
    }
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
