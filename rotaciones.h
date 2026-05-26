#ifndef ROTACIONES_H_INCLUDED
#define ROTACIONES_H_INCLUDED

#include "utilidades.h"

#define DERECHA 0
#define IZQUIERDA 1

bool rotar (const char * origen, const char * dest, t_header * header, int metodo);
bool rotar_derecha (const char * origen, const char * dest, t_header * header);
bool rotar_izquierda (const char * origen, const char * dest, t_header * header);

#endif // ROTACIONES_H_INCLUDED
