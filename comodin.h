#ifndef COMODIN_H_INCLUDED
#define COMODIN_H_INCLUDED

#include "utilidades.h"

bool comodin_efecto_VHS (FILE * pf_origen, const char * dest, t_header * header, t_pixel ** matriz);
unsigned int ondular (unsigned int pos, unsigned int fila, unsigned int columna, unsigned int bandas, unsigned int* mapa_pos_extremos);

#endif // COMODIN_H_INCLUDED
