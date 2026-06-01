#include "funciones_grupo.h"
#include "filtros_con_parametros.h"






bool aumentar_contraste (const char * origen, const char * dest, t_header * header, const unsigned int porcentaje)
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
    int prom=0;


    copiar_bytes(pf_origen, pf_dest, header->offsetDatos);

    t_pixel **matriz = crearMatriz(header->alto, header->ancho);

    for(int i = 0; i < header->alto; i++)
    {
        for(int j = 0; j < header->ancho; j++)
        {



            fread(&matriz[i][j], sizeof(t_pixel), 1, pf_origen);



            prom = matriz[i][j].r + (matriz[i][j].r *(porcentaje / 100.0));
            matriz[i][j].r = (unsigned char)(prom > 255 ? 255 : (prom < 0 ? 0 : prom));
            prom = matriz[i][j].g + ( matriz[i][j].g *(porcentaje / 100.0));
            matriz[i][j].g = (unsigned char)(prom > 255 ? 255 : (prom < 0 ? 0 : prom));
            prom = matriz[i][j].b + (matriz[i][j].b *(porcentaje / 100.0));
            matriz[i][j].b = (unsigned char)(prom > 255 ? 255 : (prom < 0 ? 0 : prom));

        }
        fseek(pf_origen, header->padding, SEEK_CUR);
    }

    guardarMatrizArchivo(matriz, header->alto, header->ancho, header->padding, pf_dest);
    liberarMatriz(matriz, header->alto);

    fclose(pf_origen);
    fclose(pf_dest);
    return true;
}




bool reducir_contraste (const char * origen, const char * dest, t_header * header, const unsigned int porcentaje)
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
    int prom=0;


    copiar_bytes(pf_origen, pf_dest, header->offsetDatos);

    t_pixel **matriz = crearMatriz(header->alto, header->ancho);

    for(int i = 0; i < header->alto; i++)
    {
        for(int j = 0; j < header->ancho; j++)
        {



            fread(&matriz[i][j], sizeof(t_pixel), 1, pf_origen);



            prom = matriz[i][j].r - (matriz[i][j].r *(porcentaje / 100.0));
            matriz[i][j].r = (unsigned char)(prom > 255 ? 255 : (prom < 0 ? 0 : prom));
            prom = matriz[i][j].g - ( matriz[i][j].g *(porcentaje / 100.0));
            matriz[i][j].g = (unsigned char)(prom > 255 ? 255 : (prom < 0 ? 0 : prom));
            prom = matriz[i][j].b - (matriz[i][j].b *(porcentaje / 100.0));
            matriz[i][j].b = (unsigned char)(prom > 255 ? 255 : (prom < 0 ? 0 : prom));

        }
        fseek(pf_origen, header->padding, SEEK_CUR);
    }

    guardarMatrizArchivo(matriz, header->alto, header->ancho, header->padding, pf_dest);
    liberarMatriz(matriz, header->alto);

    fclose(pf_origen);
    fclose(pf_dest);
    return true;
}





bool tonalidad_azul (const char * origen, const char * dest, t_header * header, const unsigned int porcentaje)
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
    int pixelAzul= 0;
    for(int i = 0; i < header->alto; i++)
    {
        for(int j = 0; j < header->ancho; j++)
        {



            fread(&matriz[i][j], sizeof(t_pixel), 1, pf_origen);

            pixelAzul= matriz[i][j].b + (matriz[i][j].b*((porcentaje / 100.0)));
            matriz[i][j].b = (unsigned char)(pixelAzul > 255 ? 255 : (pixelAzul < 0 ? 0 : pixelAzul));





        }
        fseek(pf_origen, header->padding, SEEK_CUR);
    }

    guardarMatrizArchivo(matriz, header->alto, header->ancho, header->padding, pf_dest);
    liberarMatriz(matriz, header->alto);

    fclose(pf_origen);
    fclose(pf_dest);
    return true;
}




bool tonalidad_verde (const char * origen, const char * dest, t_header * header, const unsigned int porcentaje)
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
    int pixelAzul= 0;
    for(int i = 0; i < header->alto; i++)
    {
        for(int j = 0; j < header->ancho; j++)
        {



            fread(&matriz[i][j], sizeof(t_pixel), 1, pf_origen);

            pixelAzul= matriz[i][j].g + (matriz[i][j].g*((porcentaje / 100.0)));
            matriz[i][j].g = (unsigned char)(pixelAzul > 255 ? 255 : (pixelAzul < 0 ? 0 : pixelAzul));





        }
        fseek(pf_origen, header->padding, SEEK_CUR);
    }

    guardarMatrizArchivo(matriz, header->alto, header->ancho, header->padding, pf_dest);
    liberarMatriz(matriz, header->alto);

    fclose(pf_origen);
    fclose(pf_dest);
    return true;
}

bool tonalidad_roja (const char * origen, const char * dest, t_header * header, const unsigned int porcentaje)
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
    int pixelAzul= 0;
    for(int i = 0; i < header->alto; i++)
    {
        for(int j = 0; j < header->ancho; j++)
        {



            fread(&matriz[i][j], sizeof(t_pixel), 1, pf_origen);

            pixelAzul= matriz[i][j].r + (matriz[i][j].r*((porcentaje / 100.0)));
            matriz[i][j].r = (unsigned char)(pixelAzul > 255 ? 255 : (pixelAzul < 0 ? 0 : pixelAzul));





        }
        fseek(pf_origen, header->padding, SEEK_CUR);
    }

    guardarMatrizArchivo(matriz, header->alto, header->ancho, header->padding, pf_dest);
    liberarMatriz(matriz, header->alto);

    fclose(pf_origen);
    fclose(pf_dest);
    return true;
}




bool recortar (const char * origen, const char * dest, t_header * header, const unsigned int porcentaje)
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



    t_header nuevo_header;
    copiar_header(header,&nuevo_header);



    nuevo_header.ancho=(unsigned int)((nuevo_header.ancho) * (porcentaje/100.0));
    nuevo_header.alto =(unsigned int)((nuevo_header.alto) * (porcentaje/100.0));
    nuevo_header.padding=(4 - (nuevo_header.ancho * BYTES_X_PIXEL) % 4) % 4;
    nuevo_header.tamImagen =(nuevo_header.ancho * BYTES_X_PIXEL + nuevo_header.padding) * nuevo_header.alto;
    nuevo_header.tamArchivo= (nuevo_header.tamImagen)+(nuevo_header.offsetDatos);


    copiar_bytes(pf_origen, pf_dest, header->offsetDatos);



    // Vuelvo para intercambiar tamanio del archivo
    fseek(pf_dest, 2, SEEK_SET);
    fwrite(&nuevo_header.tamArchivo, sizeof(int), 1, pf_dest);

    // Vuelvo para intercambiar alto y ancho
    fseek(pf_dest, 18, SEEK_SET);
    fwrite(&nuevo_header.ancho, sizeof(int), 1, pf_dest);
    fwrite(&nuevo_header.alto, sizeof(int), 1, pf_dest);

    // Vuelvo para intercambiar tamanio de la imagen
    fseek(pf_dest, 34, SEEK_SET);
    fwrite(&nuevo_header.tamImagen, sizeof(int), 1, pf_dest);

    // Vuelvo al offset
    fseek(pf_dest, header->offsetDatos, SEEK_SET);



    t_pixel **matriz = crearMatriz(header->alto, header->ancho);

    cargarMatriz(pf_origen, matriz, header);

    guardarMatrizArchivo(matriz,nuevo_header.alto, nuevo_header.ancho, nuevo_header.padding, pf_dest);
    liberarMatriz(matriz, header->alto);

    fclose(pf_origen);
    fclose(pf_dest);
    return true;



}

bool achicar (FILE * pf_origen, const char * dest, t_header * header, t_pixel ** matriz,const unsigned int porcentaje)
{
    FILE * pf_dest = abrir_archivo(dest, "wb");
    if(!pf_dest)
        return false;



    cargarMatriz(pf_origen, matriz, header);



    t_header nuevo_header;
    copiar_header(header,&nuevo_header);



    nuevo_header.ancho=(unsigned int)((nuevo_header.ancho) * (porcentaje/100.0));
    nuevo_header.alto =(unsigned int)((nuevo_header.alto) * (porcentaje/100.0));
    nuevo_header.padding=(4 - (nuevo_header.ancho * BYTES_X_PIXEL) % 4) % 4;
    nuevo_header.tamImagen =(nuevo_header.ancho * BYTES_X_PIXEL + nuevo_header.padding) * nuevo_header.alto;
    nuevo_header.tamArchivo= (nuevo_header.tamImagen)+(nuevo_header.offsetDatos);

    t_pixel**  matriz_achicada=crearMatriz(nuevo_header.alto,nuevo_header.ancho);
    copiar_bytes(pf_origen, pf_dest, header->offsetDatos);



    // Vuelvo para intercambiar tamanio del archivo
    fseek(pf_dest, 2, SEEK_SET);
    fwrite(&nuevo_header.tamArchivo, sizeof(int), 1, pf_dest);

    // Vuelvo para intercambiar alto y ancho
    fseek(pf_dest, 18, SEEK_SET);
    fwrite(&nuevo_header.ancho, sizeof(int), 1, pf_dest);
    fwrite(&nuevo_header.alto, sizeof(int), 1, pf_dest);

    // Vuelvo para intercambiar tamanio de la imagen
    fseek(pf_dest, 34, SEEK_SET);
    fwrite(&nuevo_header.tamImagen, sizeof(int), 1, pf_dest);

    // Vuelvo al offset
    fseek(pf_dest, header->offsetDatos, SEEK_SET);

    float saltoFila =(float)header->alto/nuevo_header.alto;
    float saltoCol =(float)header->ancho/nuevo_header.ancho;

    for (int i = 0; i < nuevo_header.alto; i++)
    {
        for (int j = 0; j < nuevo_header.ancho; j++)
        {
            matriz_achicada[i][j] = matriz[(int)(i * saltoFila)][(int)(j * saltoCol)];
        }
    }

    guardarMatrizArchivo(matriz_achicada, nuevo_header.alto,nuevo_header.ancho,nuevo_header.padding, pf_dest);
    liberarMatriz(matriz_achicada,nuevo_header.alto);

    fclose(pf_dest);
    return true;
}

