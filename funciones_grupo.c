

#include "funciones_grupo.h"

int procesar_imagen (int argc, char* argv[])
{
    char* bmpEncontrados[MAX_BMP] = {NULL, NULL};
    int cantBMP = encontrarImagenes(argv, bmpEncontrados);

    if(!cantBMP)
        return ERROR_ARGUMENTOS;

    bool bmpValidos = true;

    for(int i = 0; i < cantBMP; i++)
    {
        if(!validar_bmp(bmpEncontrados[i]))
            bmpValidos = false;
    }

    if(!bmpValidos)
        return ERROR_ARCHIVO;

    int i = 1;      // argv[0] es el nombre del programa
    int flagFunciones[20]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    while(i < argc)
    {
        const char * opcion = argv[i];

        if((strcmp(opcion, bmpEncontrados[0]) != 0) && (bmpEncontrados[1] == NULL || strcmp(opcion, bmpEncontrados[1]) != 0))
        {
            if(strncmp(opcion, "--validar", strlen("--validar")) == 0 && flagFunciones[0] != 1)
            {
                comando_validar(bmpEncontrados[0]);
                flagFunciones[0] = 1;
            }

            else if(strncmp(opcion, "--info", strlen("--info")) == 0 && flagFunciones[1] != 1)
            {
                mostrar_info(bmpEncontrados[0]);
                flagFunciones[1] = 1;
            }
        }

        i++;
    }

    return EXITO;
}

int encontrarImagenes (char* argv[], char * bmpEncontrados[MAX_BMP])
{
    int cantBmp = 0;
    char** p_argv = argv + 1;

    while(*p_argv && cantBmp < MAX_BMP)
    {
        if(strstr(*p_argv, ".bmp"))
        {
            *(bmpEncontrados + cantBmp) = *p_argv;
            cantBmp++;
        }

        p_argv++;
    }

    return cantBmp;
}

bool validar_bmp (const char * nombreArch)
{
    FILE * pf = fopen(nombreArch, "rb");
    if(!pf)
        return false;

    char firma[2];

    fread(firma, sizeof(char), 2, pf);
    if(firma[0] != 'B' || firma[1] != 'M')
    {
        fclose(pf);
        return false;
    }

    unsigned int ancho, alto;
    fseek(pf, 18, SEEK_SET);
    fread(&ancho, sizeof(int), 1, pf);
    fread(&alto, sizeof(int), 1, pf);

    if(ancho < 1 || alto < 1)
    {
        fclose(pf);
        return false;
    }

    unsigned short bits;
    fseek(pf, 28, SEEK_SET);
    fread(&bits, sizeof(short), 1, pf);

    if(bits != 24)
    {
        fclose(pf);
        return false;
    }

    unsigned int compresion;
    fread(&compresion, sizeof(int), 1, pf);

    if(compresion != 0)
    {
        fclose(pf);
        return false;
    }

    fclose(pf);
    return true;
}

bool comando_validar (const char * nombreArch)
{
    FILE * pf = fopen(nombreArch, "rb");
    if(!pf)
        return false;

    printf("Validando %s...\n", nombreArch);

    char firma[2];

    fread(firma, sizeof(char), 2, pf);
    if(firma[0] != 'B' || firma[1] != 'M')
    {
        printf("Signature BMP invalido\n");
        fclose(pf);
        return false;
    }

    printf("Signature BMP valido\n");

    unsigned short bits;
    fseek(pf, 28, SEEK_SET);
    fread(&bits, sizeof(short), 1, pf);

    if(bits != 24)
    {
        printf("ERROR: Profundidad de color incorrecta (%hu bits, esperado 24 bits\n)", bits);
        fclose(pf);
        return false;
    }

    printf("Profundidad de 24 bits confirmada\n");

    unsigned int compresion;
    fread(&compresion, sizeof(int), 1, pf);

    if(compresion != 0)
    {
        printf("Compresion: Comprimido\n");
        fclose(pf);
        return false;
    }

    printf("Compresion: No comprimido\n");

    fclose(pf);
    return true;
}

bool mostrar_info (const char * nombreArch)
{
    FILE * pf = fopen(nombreArch, "rb");
    if(!pf)
        return false;

    unsigned int tamArchivo, offsetDatos, alto, ancho, compresion, tamImagen;
    unsigned short bits;

    fseek(pf, 2, SEEK_SET);
    fread(&tamArchivo, sizeof(int), 1, pf);

    fseek(pf, 10, SEEK_SET);
    fread(&offsetDatos, sizeof(int), 1, pf);
    
    fseek(pf, 18, SEEK_SET);
    fread(&ancho, sizeof(int), 1, pf);
    fread(&alto, sizeof(int), 1, pf);

    fseek(pf, 28, SEEK_SET);
    fread(&bits, sizeof(short), 1, pf);

    fread(&compresion, sizeof(int), 1, pf);

    fread(&tamImagen, sizeof(int), 1, pf);

    int padding = (4 - (ancho * BYTES_X_PIXEL) % 4) % 4;
    if(tamImagen == 0)
        tamImagen = (ancho * BYTES_X_PIXEL + padding) * alto;

    printf("Archivo: %s\n", nombreArch);
    printf("Tamaño del archivo: %d bytes\n", tamArchivo);
    printf("Dimensiones: %dx%d pixeles\n", ancho, alto);
    printf("Profundida de color: %d bits\n", bits);
    
    printf("Offset de datos: %d\n", offsetDatos);
    printf("Tamaño de imagen: %d bytes\n", tamImagen);
    printf("Padding por fila: %d bytes\n", padding);

    fclose(pf);
    return true;
}