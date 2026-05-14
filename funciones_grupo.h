#ifndef FUNCIONES_GRUPO_H_INCLUDED
#define FUNCIONES_GRUPO_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_BMP 2

typedef enum {
    EXITO = 0,
    ERROR_ARGUMENTOS = 1,
    ERROR_ARCHIVO = 2,
    ERROR_MEMORIA = 3,
    BMP_INVALIDO = 4

} codigoRetorno;


int procesar_imagen (int argc, char* argv[]);

/**
* @brief Busca en argv archivos con extension bmp y los almacena.
*
* @param argv Array de strings recibido por main.
* @param bmpEncontrados Array para guardar los argumentos con extension bmp.
*
* @return Cantidad de archivos .bmp encontrados.
*/
int encontrarImagenes (char* argv[], char * bmpEncontrados[MAX_BMP]);

/**
* @brief Comprueba si el archivo es valido para procesar.
*
* @details Abre el archivo binario y verifica:
* - Firma "BM"
* - Dimensiones minimas de 1x1
* - Profundidad de 24 bits
* - Sin compresion
*
* @param nombreArch Ruta del archivo a validar.
*
* @return true Si cumple las 3 condiciones
* @return false Si no se puede abrir o no cumple alguna condicion.
*/
bool validar_bmp (const char * nombreArch);

#endif // FUNCIONES_GRUPO_H_INCLUDED
