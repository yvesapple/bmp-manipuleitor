#include "filtros_basicos.h"
#include "funciones_grupo.h"

bool negativo (FILE * pf_origen, const char * dest, t_header * header, t_pixel ** matriz)
{
    FILE * pf_dest = abrir_archivo(dest, "wb");
    if(!pf_dest)
        return false;

    copiar_bytes(pf_origen, pf_dest, header->offsetDatos);

    cargarMatriz(pf_origen, matriz, header);

    for(int i = 0; i < header->alto; i++)
    {
        for(int j = 0; j < header->ancho; j++)
        {
            matriz[i][j].b = 255 - matriz[i][j].b;
            matriz[i][j].g = 255 - matriz[i][j].g;
            matriz[i][j].r = 255 - matriz[i][j].r;
        }
    }

    guardarMatrizArchivo(matriz, header->alto, header->ancho, header->padding, pf_dest);

    fclose(pf_dest);
    return true;
}

bool escala_de_grises (FILE * pf_origen, const char * dest, t_header * header, t_pixel ** matriz)
{
    FILE * pf_dest = abrir_archivo(dest, "wb");
    if(!pf_dest)
        return false;

    copiar_bytes(pf_origen, pf_dest, header->offsetDatos);

    cargarMatriz(pf_origen, matriz, header);

    char gris;

    for(int i = 0; i < header->alto; i++)
    {
        for(int j = 0; j < header->ancho; j++)
        {
            gris = ((matriz[i][j].b + matriz[i][j].g + matriz[i][j].r) / 3);
            matriz[i][j].b = gris;
            matriz[i][j].g = gris;
            matriz[i][j].r = gris;
        }
    }

    guardarMatrizArchivo(matriz, header->alto, header->ancho, header->padding, pf_dest);

    fclose(pf_dest);
    return true;
}

bool espejar_horizontal (FILE * pf_origen, const char * dest, t_header * header, t_pixel **matriz)
{
    FILE * pf_dest = abrir_archivo(dest, "wb");
    if(!pf_dest)
        return false;

    copiar_bytes(pf_origen, pf_dest, header->offsetDatos);

    t_pixel aux;

    for(int i = 0; i < header->alto; i++)
    {
        for(int j = header->ancho - 1; j >= 0; j--)
        {
            fread(&aux, sizeof(t_pixel), 1, pf_origen);
            matriz[i][j] = aux;
        }
        fseek(pf_origen, header->padding, SEEK_CUR);
    }

    guardarMatrizArchivo(matriz, header->alto, header->ancho, header->padding, pf_dest);

    fclose(pf_dest);
    return true;
}

bool espejar_vertical (FILE * pf_origen, const char * dest, t_header * header, t_pixel **matriz)
{
    FILE * pf_dest = abrir_archivo(dest, "wb");
    if(!pf_dest)
        return false;

    copiar_bytes(pf_origen, pf_dest, header->offsetDatos);

    t_pixel aux;

    for(int i = header->alto - 1; i >= 0; i--)
    {
        for(int j = 0; j < header->ancho; j++)
        {
            fread(&aux, sizeof(t_pixel), 1, pf_origen);
            matriz[i][j] = aux;
        }
        fseek(pf_origen, header->padding, SEEK_CUR);
    }

    guardarMatrizArchivo(matriz, header->alto, header->ancho, header->padding, pf_dest);

    fclose(pf_dest);
    return true;
}