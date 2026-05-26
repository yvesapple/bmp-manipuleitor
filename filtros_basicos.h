#ifndef FILTROS_BASICOS_H_INCLUDED
#define FILTROS_BASICOS_H_INCLUDED

#include "utilidades.h"

/**
 * @brief Invierte los colores de la imagen dada.
 * 
 * @param origen Ruta al archivo de la imagen.
 * @param dest Ruta donde se va a escribir el resultado.
 * @param header Estructura con la informacion de cabecera de la imagen.
 * 
 * @return true Si se completo el filtro.
 * @return false Si no tiene permisos de lectura y escritura.
 */
bool negativo (const char * origen, const char * dest, t_header * header);

/**
 * @brief Convierte una imagen a escala de grises promediando RGB
 * @param origen Ruta al archivo de la imagen.
 * @param dest Ruta donde se va a escribir el resultado.
 * @param header Estructura con la informacion de cabecera de la imagen.
 * 
 * @return true Si se completo el filtro.
 * @return false Si no tiene permisos de lectura y escritura.
 */
bool escala_de_grises (const char * origen, const char * dest, t_header * header);

/**
 * @brief Voltea una imagen dada horizontalmente
 * @param origen Ruta al archivo de la imagen.
 * @param dest Ruta donde se va a escribir el resultado.
 * @param header Estructura con la informacion de cabecera de la imagen.
 * 
 * @return true Si se completo el filtro.
 * @return false Si no tiene permisos de lectura y escritura.
 */
bool espejar_horizontal (const char * origen, const char * dest, t_header * header);

/**
 * @brief Voltea una imagen dada verticalmente
 * @param origen Ruta al archivo de la imagen.
 * @param dest Ruta donde se va a escribir el resultado.
 * @param header Estructura con la informacion de cabecera de la imagen.
 * 
 * @return true Si se completo el filtro.
 * @return false Si no tiene permisos de lectura y escritura.
 */
bool espejar_vertical (const char * origen, const char * dest, t_header * header);

#endif // FILTROS_BASICOS_H_INCLUDED
