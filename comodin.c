#include "comodin.h"
#include "funciones_grupo.h"

bool comodin_efecto_VHS (FILE * pf_origen, const char * dest, t_header * header, t_pixel ** matriz)
{
    FILE * pf_dest = abrir_archivo(dest, "wb");
    if(!pf_dest)
        return false;

    unsigned int i, j;

    copiar_bytes(pf_origen, pf_dest, header->offsetDatos);
    cargarMatriz(pf_origen, matriz, header);

    t_pixel ** matriz_VHS = crearMatriz(header->alto, header->ancho);
    cargarMatriz(pf_origen, matriz_VHS, header);



    int altura_banda = 20;

    unsigned int bandas = (unsigned int) (header->alto / altura_banda + 1);
    unsigned int* mapa_desplazamiento = (unsigned int*) calloc(bandas, sizeof(unsigned int));
    if(!mapa_desplazamiento)
    {
        puts("Falla al reservar memoria para mapa de desplazamiento.");
        return false;
    }

    for(i = 0; i < bandas; i++)
    {
        *(mapa_desplazamiento+i) = (rand() % 11) - 15;
    }

    // visualizo mapa
    puts("mapa desplazamiento");
    for(i = 0; i < bandas; i++)
    {

        printf("pos = %d, valor = %d\n",i, *(mapa_desplazamiento+i));
    }

    // inicio desplazamiento
    for(i = 0; i < header->alto; i++)
    {
        int offset = mapa_desplazamiento[i / altura_banda];

        for(j = 0; j < header->ancho; j++)
        {
            int j_destino = j + offset;

            if(j_destino >= 0 && j_destino < header->ancho)
            {
                matriz_VHS[i][j_destino] = matriz[i][j];
            }
        }
    }

    guardarMatrizArchivo(matriz_VHS, header->alto, header->ancho, header->padding, pf_dest);

    liberarMatriz(matriz_VHS, header->alto);

    fclose(pf_dest);
    return true;
}

unsigned int ondular (unsigned int pos, unsigned int fila, unsigned int columna, unsigned int bandas, unsigned int* mapa_pos_extremos)
{
    static int direccion = -1;
    static unsigned int limite_vueltas = 1;
    static unsigned int fila_margen = 1;
    static unsigned int primera_pasada = 1;
    unsigned int dir_res = 0;


    if(fila < 4)
        dir_res = pos + fila;
    if(fila == 3)
    {
        *(mapa_pos_extremos + columna) = dir_res;
    }
    else
    {
        if(fila_margen == 1 && primera_pasada == 1)
            *(mapa_pos_extremos + columna)= pos; // por cada 8 pasadas guarda la posición extrema

        if(limite_vueltas % (bandas * 8) == 0)
        {
            direccion *= -1;
            limite_vueltas = 1;
        }

        if(fila_margen == 8)
        {
            fila_margen = 1;
            primera_pasada = 1;
        }
        dir_res = pos + *(mapa_pos_extremos + columna) + (fila_margen * direccion);
        limite_vueltas++;

        if(limite_vueltas % bandas == 0)
            fila_margen++;
    }
    return dir_res;
}
