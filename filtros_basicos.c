#include "filtros_basicos.h"
#include "funciones_grupo.h"

bool negativo (const char * origen, const char * dest, t_header * header)
{
    FILE * pf_origen = fopen(origen, "rb");
    if(!pf_origen)
        return false;

    FILE * pf_dest = fopen(dest, "wb");
    if(!pf_dest)
    {
        fclose(pf_origen);
        return false;
    }

    copiar_bytes(pf_origen, pf_dest, header->offsetDatos);

    t_pixel **matriz = crearMatriz(header->alto, header->ancho);

    for(int i = 0; i < header->alto; i++)
    {
        for(int j = 0; j < header->ancho; j++)
        {
            fread(&matriz[i][j], sizeof(t_pixel), 1, pf_origen);
            matriz[i][j].b = 255 - matriz[i][j].b;
            matriz[i][j].g = 255 - matriz[i][j].g;
            matriz[i][j].r = 255 - matriz[i][j].r;
        }
        fseek(pf_origen, header->padding, SEEK_CUR);
    }

    guardarMatrizArchivo(matriz, header->alto, header->ancho, header->padding, pf_dest);
    liberarMatriz(matriz, header->alto);

    fclose(pf_origen);
    fclose(pf_dest);
    return true;
}