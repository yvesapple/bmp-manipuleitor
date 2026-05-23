#ifndef FUNCIONES_GRUPO_H_INCLUDED
#define FUNCIONES_GRUPO_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_BMP 2
#define BYTES_X_PIXEL 3

extern bool verbose;

typedef enum {
    EXITO = 0,
    ERROR_ARGUMENTOS = 1,
    ERROR_ARCHIVO = 2,
    ERROR_MEMORIA = 3,
    BMP_INVALIDO = 4

} codigoRetorno;

typedef struct {
    unsigned int tamArchivo;
    unsigned int offsetDatos;
    unsigned int ancho;
    unsigned int alto;
    unsigned int compresion;
    unsigned int tamImagen;
    unsigned int padding;
    unsigned short bits;
    char firma[2];
} t_header;

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

/**
 * @brief Comprueba e imprime si el archivo es valido para procesar.
 *
 * @details Abre el archivo binario y verifica:
 * - Firma "BM"
 * - Profundidad de 24 bits
 * - Sin compresion
 *
 * @param header Estructura con la informacion del archivo.
 *
 * @return true Si cumple las 3 condiciones
 * @return false Si no se puede abrir o no cumple alguna condicion.
 */
bool comando_validar (t_header * header);

/**
 * @brief Carga la informacion de la imagen en una estructura.
 * 
 * @param nombreArch Ruta del archivo.
 * @param header Estructura a cargar.
 * 
 * @return true Si pudo cargar la informacion.
 * @return false Si no pudo abrir el archivo.
 */
bool cargar_header (const char * nombreArch, t_header * header);
void mostrar_info (t_header * header);
void mostrar_comandos ();
#endif // FUNCIONES_GRUPO_H_INCLUDED
