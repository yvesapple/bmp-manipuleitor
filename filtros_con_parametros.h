#ifndef FILTROS_CON_PARAMETROS_H_INCLUDED
#define FILTROS_CON_PARAMETROS_H_INCLUDED
#include "utilidades.h"

bool aumentar_contraste (const char * origen, const char * dest, t_header * header, const unsigned int porcentaje);
bool reducir_contraste(const char * origen, const char * dest, t_header * header, const unsigned int porcentaje);
bool tonalidad_azul(const char * origen, const char * dest, t_header * header, const unsigned int porcentaje);
bool tonalidad_rojo(const char * origen, const char * dest, t_header * header, const unsigned int porcentaje);
bool tonalidad_verde(const char * origen, const char * dest, t_header * header, const unsigned int porcentaje);
bool recortar (const char * origen, const char * dest, t_header * header, const unsigned int porcentaje);
bool achicar (FILE * pf_origen, const char * dest, t_header * header, t_pixel ** matriz,const unsigned int porcentaje);
#endif // FILTROS_CON_PARAMETROS_H_INCLUDED
