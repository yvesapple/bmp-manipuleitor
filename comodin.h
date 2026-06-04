#ifndef COMODIN_H_INCLUDED
#define COMODIN_H_INCLUDED

#include "utilidades.h"

bool comodin_efecto_VHS (FILE * pf_origen, const char * dest, t_header * header, t_pixel ** matriz);
void copiarMatriz(t_pixel **origen, t_pixel **destino, int alto, int ancho);

#endif // COMODIN_H_INCLUDED
