

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
