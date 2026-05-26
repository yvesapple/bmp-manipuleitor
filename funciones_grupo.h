#ifndef FUNCIONES_GRUPO_H_INCLUDED
#define FUNCIONES_GRUPO_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "utilidades.h"
#include "filtros_basicos.h"

#define TAM_MAX_NOMBRE 256

extern bool verbose;

typedef enum {
    EXITO = 0,
    ERROR_ARGUMENTOS = 1,
    ERROR_ARCHIVO = 2,
    ERROR_MEMORIA = 3,
    BMP_INVALIDO = 4

} codigoRetorno;

typedef struct {
    unsigned char b;
    unsigned char g;
    unsigned char r;
} t_pixel;

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
 * @param header Estructura con la informacion del archivo.
 *
 * @return true Si cumple las 4 condiciones
 * @return false Si no se puede abrir o no cumple alguna condicion.
 */
bool validar_bmp (t_header * header);

t_pixel** crearMatriz (int alto, int ancho);

void liberarMatriz (t_pixel** mat, int filas);

void guardarMatrizArchivo (t_pixel ** matriz, int filas, int col, int padding, FILE * pf);

void copiar_bytes (FILE * origen, FILE * dest, int offsetDatos);

void generarNombreArchivo (const char * prefijo, const char * nombreArch, char * resultado);
#endif // FUNCIONES_GRUPO_H_INCLUDED
