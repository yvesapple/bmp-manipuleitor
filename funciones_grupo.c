#include "funciones_grupo.h"

int procesar_imagen (int argc, char* argv[])
{
    bool verbose = false;

    for(int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "--help") == 0)
        {
            mostrar_comandos();
            return EXITO;
        }
        else if(strcmp(argv[i], "--verbose") == 0)
            verbose = true;
    }

    if(verbose)
    {
        printf("[INFO] Iniciando bmpmanipuleitor...\n");
        printf("[INFO] Argumentos detectados: ");
        for(int i = 1; i < argc; i++)
        {
            printf("%s ", argv[i]);
        }
        printf("\n");
    }

    char* bmpEncontrados[MAX_BMP] = {NULL, NULL};
    int cantBMP = encontrarImagenes(argv, bmpEncontrados);

    if(!cantBMP)
        return ERROR_ARGUMENTOS;

    bool bmpValidos = true;

    t_header header;
    char archSalida[TAM_MAX_NOMBRE];

    if(cantBMP == 2)
    {
        for(int i = 0; i < cantBMP; i++)
        {
            cargar_header(bmpEncontrados[i], &header);
            if(!validar_bmp(&header))
                bmpValidos = false;
        }

        if(!bmpValidos)
            return ERROR_ARCHIVO;

        // Concatenación horizontal
        // Concatenación vertical

        return EXITO;
    }
      
    int flagFunciones[18]= {0};

    for(int i = 1; i < argc; i++)   // argv[0] es el nombre del programa
    {
        const char * opcion = argv[i];
        const char * imagen = bmpEncontrados[0];
        if(!cargar_header(imagen, &header))
            return ERROR_ARCHIVO;

        if((strcmp(opcion, imagen) != 0))
        {
            if(strncmp(opcion, "--validar", strlen("--validar")) == 0 && flagFunciones[0] != 1)
            {
                printf("Validando %s...", imagen);
                if(!comando_validar(&header))
                    printf("ARCHIVO INVALIDO - No se puede procesar\n");
                flagFunciones[0] = 1;
            }

            else if(strncmp(opcion, "--info", strlen("--info")) == 0 && flagFunciones[1] != 1)
            {
                printf("Archivo: %s\n", imagen);
                mostrar_info(&header);
                flagFunciones[1] = 1;
            }
            
            else
            {
                if(!validar_bmp(&header))
                    return BMP_INVALIDO;

                if(strncmp(opcion, "--negativo", strlen("--negativo")) == 0 && flagFunciones[2] != 1)
                {
                    generarNombreArchivo("DUALISMO_negativo_", imagen, archSalida);
                    negativo(imagen, archSalida, &header);
                    flagFunciones[2] = 1;
                }
            }
        }
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

bool validar_bmp (t_header * header)
{
    if(header->firma[0] != 'B' || header->firma[1] != 'M')
        return false;

    if(header->ancho < 1 || header->alto < 1)
        return false;

    if(header->bits != 24)
        return false;

    if(header->compresion != 0)
        return false;

    return true;
}

t_pixel** crearMatriz (int filas, int col)
{
    t_pixel **matriz = malloc(filas * sizeof(t_pixel*));
    if(!matriz)
    {
        printf("Error al asignar memoria\n");
        exit(ERROR_MEMORIA);
    }

    for(int i = 0; i < filas; i++)
    {
        matriz[i] = malloc(col * sizeof(t_pixel));

        if(!matriz[i])
        {
            for(int j = 0; j < i; j++)
            {
                free(matriz[j]);
            }
            free(matriz);
            printf("Error al asignar memoria\n");
            exit(ERROR_MEMORIA);
        }
    }

    return matriz;
}

void liberarMatriz (t_pixel** mat, int filas)
{
    for(int i = 0; i < filas; i++)
    {
        free(mat[i]);
    }
    free(mat);
}

void guardarMatrizArchivo (t_pixel ** matriz, int filas, int col, int padding, FILE * pf)
{
    unsigned char pad[3] = {0, 255, 0};

    for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < col; j++)
        {
            fwrite(&matriz[i][j], sizeof(t_pixel), 1, pf);
        }
        fwrite(pad, sizeof(unsigned char), padding, pf);
    }
}

void copiar_bytes (FILE * origen, FILE * dest, int offsetDatos)
{
    char byte;

    for(int i = 0; i < offsetDatos; i++)
    {
        fread(&byte, sizeof(char), 1, origen);
        fwrite(&byte, sizeof(char), 1, dest);
    }
}

void generarNombreArchivo (const char * prefijo, const char * nombreArch, char * resultado)
{
    const char * nombreBase = strrchr(nombreArch, '/');
    if(nombreBase == NULL)
        nombreBase = strrchr(nombreArch, '\\');

    if(nombreBase == NULL)
        nombreBase = nombreArch;
    else
        nombreBase++;

    snprintf(resultado, TAM_MAX_NOMBRE, "%s%s", prefijo, nombreBase);
}