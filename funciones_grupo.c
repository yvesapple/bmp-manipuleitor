#include "funciones_grupo.h"

bool verbose = false;

int procesar_imagen (int argc, char* argv[])
{
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

    char nombre_salida[TAM_MAX_NOMBRE];
    unsigned int porcentaje=0;

    t_header header;
    const char * imagen = bmpEncontrados[0];
    FILE * archEntrada = abrir_archivo(imagen, "rb");
    if(!archEntrada)
        return ERROR_ARCHIVO;
    cargar_header(archEntrada, &header);
    t_pixel **matriz = crearMatriz(header.alto, header.ancho);
    cargarMatriz(archEntrada, matriz, &header);

    t_header header2;
    const char * imagen2 = NULL;
    FILE * archEntrada2 = NULL;
    t_pixel **matriz2 = NULL;
    if(cantBMP == 2)
    {
        imagen2 = bmpEncontrados[1];
        archEntrada2 = abrir_archivo(imagen2, "rb");
        if(!archEntrada2)
            return ERROR_ARCHIVO;
        cargar_header(archEntrada2, &header2);
        matriz2 = crearMatriz(header2.alto, header2.ancho);
        cargarMatriz(archEntrada2, matriz2, &header2);
    }

    int flagFunciones[18]= {0};
    // int filtros_hallados = argc - cantBMP;

    for(int i = 1; i < argc; i++)   // argv[0] es el nombre del programa
    {
        const char * opcion = argv[i];
        bool filtroValido = true;

        if((strcmp(opcion, imagen) != 0) && (cantBMP < 2 || strcmp(opcion, imagen2) != 0))
        {
            porcentaje=buscarPorcentaje(opcion); // por cada nueva pasada se busca porcentaje

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
                    generarNombreArchivo("DUALISMO_negativo_", imagen, nombre_salida);
                    negativo(archEntrada, nombre_salida, &header, matriz);
                    rewind(archEntrada);
                    flagFunciones[2] = 1;
                }

                else if(strncmp(opcion, "--escala-de-grises", strlen("--escala-de-grises")) == 0 && flagFunciones[3] != 1)
                {
                    generarNombreArchivo("DUALISMO_escala-de-grises_", imagen, nombre_salida);
                    escala_de_grises(archEntrada, nombre_salida, &header, matriz);
                    rewind(archEntrada);
                    flagFunciones[3] = 1;
                }

                else if(strncmp(opcion, "--espejar-horizontal", strlen("--espejar-horizontal")) == 0 && flagFunciones[4] != 1)
                {
                    generarNombreArchivo("DUALISMO_espejar-horizontal_", imagen, nombre_salida);
                    espejar_horizontal(archEntrada, nombre_salida, &header, matriz);
                    rewind(archEntrada);
                    flagFunciones[4] = 1;
                }

                else if(strncmp(opcion, "--espejar-vertical", strlen("--espejar-vertical")) == 0 && flagFunciones[5] != 1)
                {
                    generarNombreArchivo("DUALISMO_espejar-vertical_", imagen, nombre_salida);
                    espejar_vertical(archEntrada, nombre_salida, &header, matriz);
                    rewind(archEntrada);
                    flagFunciones[5] = 1;
                }

                else if(strncmp(opcion, "--rotar-derecha", strlen("--rotar-derecha")) == 0 && flagFunciones[6] != 1)
                {
                    generarNombreArchivo("DUALISMO_rotar-derecha_", imagen, nombre_salida);
                    rotar(archEntrada, nombre_salida, &header, matriz, DERECHA);
                    rewind(archEntrada);
                    flagFunciones[6] = 1;
                }

                else if(strncmp(opcion, "--rotar-izquierda", strlen("--rotar-izquierda")) == 0 && flagFunciones[7] != 1)
                {
                    generarNombreArchivo("DUALISMO_rotar-izquierda_", imagen, nombre_salida);
                    rotar(archEntrada, nombre_salida, &header, matriz, IZQUIERDA);
                    rewind(archEntrada);
                    flagFunciones[7] = 1;
                }

                else if(strncmp(opcion, "--aumentar-contraste", strlen("--aumentar-contraste")) == 0 && flagFunciones[8] != 1 && porcentaje!=-1 )
                {
                    generarNombreArchivo("DUALISMO_aumentar-contraste_", imagen,nombre_salida);
                    aumentar_contraste(imagen,nombre_salida,&header,porcentaje);
                    rewind(archEntrada);
                    flagFunciones[8] = 1;
                }

                else if(strncmp(opcion, "--reducir-contraste", strlen("--reducir-contraste")) == 0 && flagFunciones[9] != 1 && porcentaje!=-1 )
                {
                    generarNombreArchivo("DUALISMO_reducir-contraste_", imagen,nombre_salida);
                    reducir_contraste(imagen,nombre_salida,&header,porcentaje);
                    rewind(archEntrada);
                    flagFunciones[9] = 1;
                }

                else if(strncmp(opcion, "--tonalidad-azul", strlen("--tonalidad-azul")) == 0 && flagFunciones[10] != 1 && porcentaje!=-1 )
                {
                    generarNombreArchivo("DUALISMO_tonalidad-azul_", imagen,nombre_salida);
                    tonalidad_azul(imagen,nombre_salida,&header,porcentaje);
                    rewind(archEntrada);
                    flagFunciones[10] = 1;
                }

                else if(strncmp(opcion, "--tonalidad-verde", strlen("--tonalidad-verde")) == 0 && flagFunciones[11] != 1 && porcentaje!=-1 )
                {
                    generarNombreArchivo("DUALISMO_tonalidad-verde_", imagen,nombre_salida);
                    tonalidad_verde(imagen,nombre_salida,&header,porcentaje);
                    rewind(archEntrada);
                    flagFunciones[11] = 1;
                }
                else if(strncmp(opcion, "--tonalidad-roja", strlen("--tonalidad-roja")) == 0 && flagFunciones[12] != 1 && porcentaje!=-1 )
                {
                    generarNombreArchivo("DUALISMO_tonalidad-roja_", imagen,nombre_salida);
                    tonalidad_roja(imagen,nombre_salida,&header,porcentaje);
                    rewind(archEntrada);
                    flagFunciones[12] = 1;
                }

                else if(strncmp(opcion, "--recortar", strlen("--recortar")) == 0 && flagFunciones[13] != 1 && porcentaje!=-1 )
                {
                    generarNombreArchivo("DUALISMO_recortar_", imagen,nombre_salida);
                    recortar(imagen,nombre_salida,&header,porcentaje);
                    rewind(archEntrada);
                    flagFunciones[13] = 1;
                }

                else if(strncmp(opcion, "--achicar", strlen("--achicar")) == 0 && flagFunciones[14] != 1 && porcentaje!=-1 )
                {
                    generarNombreArchivo("DUALISMO_achicar_", imagen,nombre_salida);
                    achicar(archEntrada,nombre_salida,&header,matriz,porcentaje);
                    rewind(archEntrada);
                    flagFunciones[14] = 1;
                }

                else if(strncmp(opcion, "--concatenar-vertical", strlen("--concatenar-vertical")) == 0 && flagFunciones[15] != 1 && cantBMP == 2)
                {
                    generarNombreArchivo("DUALISMO_concatenar-vertical_", imagen,nombre_salida);
                    concatenar_vertical(archEntrada, archEntrada2, nombre_salida, &header, &header2, matriz, matriz2);
                    rewind(archEntrada);
                    flagFunciones[15] = 1;
                }

                else if(strncmp(opcion, "--concatenar-horizontal", strlen("--concatenar-horizontal")) == 0 && flagFunciones[16] != 1 && cantBMP == 2)
                {
                    generarNombreArchivo("DUALISMO_concatenar-horizontal_", imagen,nombre_salida);
                    concatenar_horizontal(archEntrada, archEntrada2, nombre_salida, &header, &header2, matriz, matriz2);
                    rewind(archEntrada);
                    flagFunciones[16] = 1;
                }

                else
                {
                    filtroValido = false;
                    if(!esParametroUtilidad(opcion))
                    {
                        printf("Filtro invalido: %s\n", opcion);
                    }
                }

                if(verbose && filtroValido)
                {
                    printf("[INFO] Aplicando filtro: %s\n", opcion);
                    printf("[INFO] Guardando resultado: %s\n", nombre_salida);
                    printf("[INFO] Filtro %s completado exitosamente\n", opcion);
                }
            }
        }
    }

    liberarMatriz(matriz, header.alto);
    if(cantBMP == 2)
    {
        liberarMatriz(matriz2, header2.alto);
        fclose(archEntrada2);
    }
    fclose(archEntrada);

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
    if(verbose)
        printf("[INFO] Reservando memoria para matriz %dx%d...\n", filas, col);

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

    if(verbose)
        printf("[INFO] Memoria reservada exitosamente (%d pixeles)\n", filas * col * BYTES_X_PIXEL);

    return matriz;
}

void liberarMatriz (t_pixel** mat, int filas)
{
    if(verbose)
        printf("[INFO] Liberando memoria...\n");

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

bool esParametroUtilidad (const char * opcion)
{
    if(strncmp(opcion, "--info", strlen("--info")) == 0)
        return true;

    if(strncmp(opcion, "--validar", strlen("--validar")) == 0)
        return true;

    if(strncmp(opcion, "--verbose", strlen("--verbose")) == 0)
        return true;

    if(strncmp(opcion, "--help", strlen("--help")) == 0)
        return true;

    return false;
}

int buscarPorcentaje (const char * parametro)
{
    char aux[4];        // 3 bytes (0-100) 1 byte (\0)
    const char * ptrCadena = strrchr(parametro, '=');
    if(!ptrCadena)
        return ERROR_ARGUMENTOS;

    ptrCadena++;        // Saltear '='
    strcpy(aux, ptrCadena);
    aux[3] = '\0';
    int porcentaje=0;
    porcentaje = atoi(aux);
    if(porcentaje <= 0 || porcentaje > 100)
    {
        printf("Valor incorrecto para el porcentaje, ingresar valor entre 0 y 100.\n");
        return ERROR_ARGUMENTOS;
    }

    return porcentaje;
}

FILE* abrir_archivo (const char * path, const char * metodo)
{
    FILE * pf = fopen(path, metodo);
    if(!pf)
    {
        printf("Sin permisos de lectura/escritura\n");
        return NULL;
    }

    return pf;
}

void cargarMatriz (FILE * pf, t_pixel ** mat, t_header * header)
{
    long posInicial = ftell(pf);
    fseek(pf, header->offsetDatos, SEEK_SET);

    for(int i = 0; i < header->alto; i++)
    {
        for(int j = 0; j < header->ancho; j++)
        {
            fread(&mat[i][j], sizeof(t_pixel), 1, pf);
        }
        fseek(pf, header->padding, SEEK_CUR);
    }

    fseek(pf, posInicial, SEEK_SET);
}

void copiar_header(t_header* original, t_header* nuevo)
{
    nuevo->alto = original->alto;
    nuevo->ancho = original->ancho;
    nuevo->bits = original->bits;
    nuevo->compresion = original->compresion;
    strncpy(nuevo->firma,original->firma,2);
    nuevo->offsetDatos = original->offsetDatos;
    nuevo->padding = original->padding;
    nuevo->tamArchivo = original->tamArchivo;
    nuevo->tamImagen = original->tamImagen;
}

t_pixel** copiarMatriz (t_pixel** matOriginal, int filas, int col)
{
    t_pixel ** copia = crearMatriz(filas, col);
    for(int i = 0; i < filas; i++)
    {
        memcpy(copia[i], matOriginal[i], col * sizeof(t_pixel));
    }

    return copia;
}
