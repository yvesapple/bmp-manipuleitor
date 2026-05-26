#include "rotaciones.h"
#include "funciones_grupo.h"

bool rotar_derecha (const char * origen, const char * dest, t_header * header)
{
    return rotar(origen, dest, header, DERECHA);
}

bool rotar_izquierda (const char * origen, const char * dest, t_header * header)
{
    return rotar(origen, dest, header, IZQUIERDA);
}

bool rotar (const char * origen, const char * dest, t_header * header, int metodo)
{
    FILE *pf_origen = fopen(origen, "rb");
    if(!pf_origen)
        return false;

    FILE *pf_dest = fopen(dest, "wb");
    if(!pf_dest)
    {
        fclose(pf_origen);
        return false;
    }

    copiar_bytes(pf_origen, pf_dest, header->offsetDatos);

    // Vuelvo para intercambiar alto y ancho
    fseek(pf_dest, 18, SEEK_SET);
    int nuevoAncho = header->alto;
    int nuevoAlto = header->ancho;

    fwrite(&nuevoAncho, sizeof(int), 1, pf_dest);
    fwrite(&nuevoAlto, sizeof(int), 1, pf_dest);

    // Vuelvo al offset
    fseek(pf_dest, header->offsetDatos, SEEK_SET);

    t_pixel **matOriginal = crearMatriz(header->alto, header->ancho);
    t_pixel **matRotada = crearMatriz(nuevoAlto, nuevoAncho);

    // Cargo la matriz original
    for(int i = 0; i < header->alto; i++)
    {
        for(int j = 0; j < header->ancho; j++)
        {
            fread(&matOriginal[i][j], sizeof(t_pixel), 1, pf_origen);
        }
        fseek(pf_origen, header->padding, SEEK_CUR);
    }

    // Cargo la matriz rotada
    if(metodo == IZQUIERDA)
    {
        for(int i = 0; i < header->alto; i++)
        {
            for(int j = 0; j < header->ancho; j++)
            {
                matRotada[j][nuevoAncho - 1 - i] = matOriginal[i][j];
            }
        }
    }
    else
    {
        for(int i = 0; i < header->alto; i++)
        {
            for(int j = 0; j < header->ancho; j++)
            {
                matRotada[nuevoAlto - 1 - j][i] = matOriginal[i][j];
            }
        }
    }

    int nuevoPadding = (4 - (nuevoAncho * 3) % 4) % 4;

    guardarMatrizArchivo(matRotada, nuevoAlto, nuevoAncho, nuevoPadding, pf_dest);

    liberarMatriz(matOriginal, header->alto);
    liberarMatriz(matRotada, nuevoAlto);

    fclose(pf_origen);
    fclose(pf_dest);
    return true;
}
