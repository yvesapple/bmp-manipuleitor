#include "comodin.h"
#include "funciones_grupo.h"

bool comodin_efecto_VHS (FILE * pf_origen, const char * dest, t_header * header, t_pixel ** matriz)
{
    t_pixel ** matriz_VHS = crearMatriz(header->alto, header->ancho);
    if(!matriz_VHS)
        return false;

    int altura_cinta = 20, offset = 0, j_destino;
    unsigned int bandas = (unsigned int) (header->alto / altura_cinta);
    unsigned int* mapa_desplazamiento = (unsigned int*) calloc(bandas, sizeof(unsigned int));
    if(!mapa_desplazamiento)
    {
        puts("Falla al reservar memoria para mapa de desplazamiento.");
        liberarMatriz(matriz_VHS, header->alto);
        return false;
    }

    copiarMatriz(matriz, matriz_VHS, header->alto, header->ancho);

    FILE * pf_dest = abrir_archivo(dest, "wb");
    if(!pf_dest)
    {
        free(mapa_desplazamiento);
        liberarMatriz(matriz_VHS, header->alto);
        return false;
    }

    unsigned int i, j;

    copiar_bytes(pf_origen, pf_dest, header->offsetDatos);

    /// Primer paso efecto cromatico
    int offset_croma = 3;
    int j_destino_rojo = 0, j_destino_azul = 0;

    for(i = 0; i < header->alto; i++)
    {
        for(j = 0; j < header->ancho; j++)
        {
            j_destino_rojo = j+offset_croma;
            j_destino_azul = j-offset_croma;
            if(j_destino_azul >= 0 && j_destino_rojo < header->ancho)
            {
                matriz_VHS[i][j_destino_rojo].r = matriz[i][j].r;
                matriz_VHS[i][j].g = matriz[i][j].g;
                matriz_VHS[i][j_destino_azul].b = matriz[i][j].b;

            }
        }
    }
    copiarMatriz(matriz_VHS, matriz, header->alto, header->ancho);

    /// Segundo paso barrido de cinta
    for(i = 0; i < bandas; i++)
    {
        *(mapa_desplazamiento+i) = (rand() % 11) - 15;
    }

    for(i = 0; i < header->alto; i++)
    {
        offset = mapa_desplazamiento[i / altura_cinta];
        for(j = 0; j < header->ancho; j++)
        {
            j_destino = j + offset;
            if(j_destino >= 0 && j_destino < header->ancho)
            {
                matriz_VHS[i][j_destino] = matriz[i][j];
            }
        }
    }

    int efecto = 0;
    /// tercer paso efecto ruido en verde
    for(i = 0; i < header->alto; i++)
    {
        efecto = rand() % 100;

        if(efecto < 3)
        {
            for(int j = 0; j < header->ancho; j++)
            {
                matriz_VHS[i][j].g = 1 + rand() % 255;
            }
        }
    }

    guardarMatrizArchivo(matriz_VHS, header->alto, header->ancho, header->padding, pf_dest);

    free(mapa_desplazamiento);
    liberarMatriz(matriz_VHS, header->alto);

    fclose(pf_dest);
    return true;
}
