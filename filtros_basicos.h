#ifndef FILTROS_BASICOS_H_INCLUDED
#define FILTROS_BASICOS_H_INCLUDED

#include "utilidades.h"

bool negativo (FILE * pf_origen, const char * dest, t_header * header, t_pixel ** matrizOriginal);

bool escala_de_grises (FILE * pf_origen, const char * dest, t_header * header, t_pixel ** matrizOriginal);

bool espejar_horizontal (FILE * pf_origen, const char * dest, t_header * header, t_pixel **matrizOriginal);

bool espejar_vertical (FILE * pf_origen, const char * dest, t_header * header, t_pixel **matrizOriginal);

#endif // FILTROS_BASICOS_H_INCLUDED
