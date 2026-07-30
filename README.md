# bmpmanipuleitor

Programa en C para procesar archivos **BMP de 24 bits sin compresión**, aplicando filtros, transformaciones geométricas y operaciones de concatenación sobre imágenes.

Trabajo Práctico para Universidad Nacional de La Matanza.

## Descripción

`bmpmanipuleitor` recibe uno o más archivos BMP de 24 bits por línea de comandos y aplica sobre ellos los filtros indicados, generando un archivo de salida por cada filtro aplicado con el formato:

```
GRUPO_filtro[-valor]_imagen.bmp
```

### Ejemplo básico

```bash
bmpmanipuleitor.exe --negativo imagen.bmp --escala-de-grises --aumentar-contraste=25
```

Genera:

- `GRUPO_negativo_imagen.bmp`
- `GRUPO_escala-de-grises_imagen.bmp`
- `GRUPO_aumentar-contraste-25_imagen.bmp`

## Requisitos y limitaciones

- Solo acepta archivos **BMP**.
- Solo BMP **sin compresión**.
- Solo **24 bits** de profundidad de color.

## Instalación

### Opción 1: Línea de comandos (gcc)

La forma más rápida de compilar el proyecto:

```bash
git clone https://github.com/yvesapple/bmp-manipuleitor
cd <repo>
gcc main.c funciones_grupo.c funciones_*.c -o bmpmanipuleitor -Wall -Wextra
```

Esto genera el ejecutable `bmpmanipuleitor` (o `bmpmanipuleitor.exe` en Windows) en la carpeta del proyecto.

### Opción 2: Code::Blocks

1. Clonar el repositorio:
   ```bash
   git clone https://github.com/yvesapple/bmp-manipuleitor
   ```
2. Abrir Code::Blocks y creá un proyecto nuevo: **File → New → Project… → Console Application → C**.
3. Elegir un nombre y una ubicación para el proyecto (puede ser una carpeta distinta a la del clone).
4. Una vez creado, borrar el `main.c` que genera Code::Blocks por defecto (o reemplazar su contenido).
5. Agregar todos los archivos `.c` y `.h` clonados al proyecto: click derecho sobre el proyecto en el panel *Projects* → **Add files…** → seleccionar todos los `.c`/`.h` del repo clonado.
6. Compilar con **Build → Build** (`Ctrl+F9`).

## Uso

```bash
bmpmanipuleitor.exe [OPCIONES] archivo(s).bmp
```

Los filtros pueden combinarse en una misma ejecución y el orden de los argumentos (imagen antes, en medio o después de las opciones) no afecta el resultado.

## Funcionalidades

### Filtros básicos

| Opción | Descripción |
|---|---|
| `--negativo` | Invierte los colores de la imagen |
| `--escala-de-grises` | Convierte a escala de grises promediando RGB |
| `--espejar-horizontal` | Voltea la imagen horizontalmente |
| `--espejar-vertical` | Voltea la imagen verticalmente |

### Filtros con parámetro (0–100%)

| Opción | Descripción |
|---|---|
| `--aumentar-contraste=X` | Aumenta el contraste en X% |
| `--reducir-contraste=X` | Reduce el contraste en X% |
| `--tonalidad-azul=X` | Aumenta la intensidad del canal azul en X% |
| `--tonalidad-verde=X` | Aumenta la intensidad del canal verde en X% |
| `--tonalidad-roja=X` | Aumenta la intensidad del canal rojo en X% |
| `--recortar=X` | Conserva solo el X% del tamaño original, desde la esquina inferior izquierda (rango válido 1–100) |
| `--achicar=X` | Reescala la imagen al X% de su tamaño original (rango válido 1–100) |

### Rotaciones

| Opción | Descripción |
|---|---|
| `--rotar-derecha` | Rota la imagen 90° en sentido horario |
| `--rotar-izquierda` | Rota la imagen 90° en sentido antihorario |

### Concatenaciones

Reciben **dos** imágenes como argumento y generan una nueva combinando ambas. Si difieren en altura/ancho, la más chica se rellena con un color verde hasta igualar la dimensión correspondiente.

| Opción | Descripción |
|---|---|
| `--concatenar-horizontal` | Une las imágenes una al lado de la otra, alineando por altura |
| `--concatenar-vertical` | Une las imágenes una arriba de la otra, alineando por ancho |

Ejemplos de uso válidos:

```bash
bmpmanipuleitor.exe --concatenar-horizontal imagen1.bmp imagen2.bmp
bmpmanipuleitor.exe imagen1.bmp --concatenar-horizontal imagen2.bmp
bmpmanipuleitor.exe imagen1.bmp imagen2.bmp --concatenar-horizontal
```

### Comodín

| Opción | Descripción |
|---|---|
| `--comodin` | Aplica un filtro VHS a la imagen |

### Utilidades

| Opción | Descripción |
|---|---|
| `--info` | Muestra información del archivo BMP (dimensiones, tamaño, etc.) |
| `--validar` | Solo valida el archivo sin procesarlo |
| `--verbose` | Modo detallado, muestra mensajes informativos durante la ejecución |
| `--help` | Muestra la ayuda de uso y la lista de comandos disponibles |

## Códigos de retorno

| Código | Significado |
|---|---|
| 0 | Éxito |
| 1 | Error de argumentos |
| 2 | Error de archivo (no encontrado, sin permisos) |
| 3 | Error de memoria (falló `malloc`) |
| 4 | Formato BMP inválido |

## Comportamiento ante errores y casos límite

- Los filtros duplicados se ejecutan una única vez.
- Los parámetros fuera de rango (0–100%) o inválidos se reportan por error y ese filtro específico se ignora, continuando con el resto.
- Los archivos de salida existentes se sobrescriben sin confirmación.
- Si falla la escritura por falta de permisos, se reporta el error y se continúa con los demás filtros.
- Ante un fallo de `malloc`, el programa finaliza de forma controlada devolviendo el código de error correspondiente.

## Licencia

Trabajo académico desarrollado para la cátedra de Tópicos de Programación (UNLaM). Uso educativo.
