#include <stdio.h>
#include "Lecturas.h"


// Función para leer un entero
int leerEntero(char* mensaje) {
    int valor;
    printf("%s", mensaje);
    scanf("%d", &valor);
    return valor;
}

// Función para leer un entero positivo
int leerEnteroPositivo(char* mensaje) {
    int valor;
    do {
        valor = leerEntero(mensaje);
    } while (valor < 0); // Permitir 0 
    return valor;
}

// Función para leer un entero entre 
int leerEnteroEntre(char*mensaje, int a , int b){
    int valor;
    do{
        printf("%s", mensaje);
        scanf("%d", &valor);
    }while(valor<a || valor>b );
    return valor;
}

// Función para leer un flotante
float leerFlotantePositivo(char*mensaje){
    float valor;
    do{
        printf("%s", mensaje);
        scanf("%f",&valor);
    }while(valor <= 0);
    return valor;
}

// Función para leer un flotante entre
float leerFlotanteEntre(char *mensaje, float a, float b) {
    float valor;
    do {
        printf("%s (entre %.2f y %.2f): ", mensaje, a, b);
        scanf("%f", &valor);
    } while (valor < a || valor > b);
    return valor;
}


// Función para leer un caracter
char leerCaracter(const char*mensaje){
    char valor;

        printf("%s", mensaje);
        scanf("%c", &valor);
            
    return valor;
}
        
    