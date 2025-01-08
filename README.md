# get\_next\_line

get\_next\_line es un proyecto de 42 que consiste en implementar una función capaz de leer una línea completa desde un descriptor de archivo (file descriptor), incluso si la lectura debe realizarse en varias llamadas. El objetivo es mejorar la comprensión del manejo de archivos y memoria dinámica en C.

## Tabla de Contenidos

- [Instalación](#instalación)
- [Uso](#uso)
- [Especificaciones del Proyecto](#especificaciones-del-proyecto)
- [Tests](#tests)
- [Créditos](#créditos)

## Instalación

Clona este repositorio en tu directorio local:

```bash
$ git clone https://github.com/erico-ke/get_next_line.git
$ cd get_next_line
```

Compila los archivos con:

```bash
$ make
```

Esto generará un archivo `get_next_line.a`, que es la biblioteca compilada.

## Uso

Para usar `get_next_line` en tu proyecto, incluye el archivo de cabecera `get_next_line.h` y enlaza el archivo `get_next_line.a` al compilar tu programa. Por ejemplo:

```c
#include "get_next_line.h"
#include <fcntl.h> // Para usar open
#include <stdio.h> // Para usar printf

int main()
{
    int fd = open("archivo.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

Compila tu programa junto con la biblioteca:

```bash
$ gcc -Wall -Wextra -Werror -L. -lget_next_line tu_programa.c -o tu_programa
```

## Especificaciones del Proyecto

`get_next_line` debe cumplir con las siguientes características:

- Leer y devolver una línea completa de un descriptor de archivo.
- Gestionar correctamente archivos que contienen cualquier tipo de contenido, incluyendo grandes volúmenes de datos o líneas extremadamente largas.
- Permitir que varias llamadas a `get_next_line` funcionen de forma consecutiva.
- La función debe manejar errores y liberar memoria asignada dinámicamente para evitar fugas.

### Normas de 42

Este proyecto debe cumplir con las siguientes normas:

- Seguir la norma de codificación de 42 (Norminette).
- El código debe compilar sin errores ni warnings con las flags: `-Wall -Wextra -Werror`.
- No se permite el uso de funciones externas, excepto las especificadas en el PDF del proyecto: `read`, `malloc`, `free`, y `close`.
- Se debe gestionar correctamente la memoria dinámica, evitando fugas.
- `BUFFER_SIZE` debe ser un valor ajustable y utilizado para definir el tamaño del buffer de lectura.

## Tests

Puedes usar herramientas externas para verificar la funcionalidad de tu implementación de `get_next_line`. Algunas recomendadas son:

- [GNL Tester](https://github.com/Tripouille/gnlTester)
- [Unit Test GNL](https://github.com/Hellio404/Get_Next_Line_Tester)

Ejecuta estos tests para asegurarte de que tu implementación cumple con los requisitos.

## Créditos

Proyecto desarrollado por Elías Rico Kergaravat. Este es un proyecto obligatorio de 42 Málaga. Si tienes dudas o sugerencias, no dudes en contactarme.

