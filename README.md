# Reservaciones de cine · Variante B

Sistema de consola en C++17 para una sala de 20 butacas. Las butacas 1 a 8 son VIP y cuestan Q50. Las butacas 9 a 20 son General y cuestan Q35.

## Abrir en CLion

1. Descomprime el ZIP en una carpeta nueva. En CLion selecciona **Open** y abre `Cine/03_CODIGO_FINAL`.
2. Espera a que cargue CMake y elige **Cine** arriba, junto al botón verde.
3. En **Run → Edit Configurations**, selecciona **Cine** y elige la carpeta `03_CODIGO_FINAL` en **Working directory**. Ahí se crearán `cine.txt` y `cine.db`.
4. Presiona **Run**. Reserva las butacas 8 y 9, entra a reportes y comprueba que el total sea Q85. Sal con `0` y abre el programa de nuevo para confirmar que siguen reservadas.

Si ya tienes tu carpeta `Cine` con `00_ASIGNACION`, `01_ENTREGA_1` y `02_ENTREGA_2`, consérvalas al reunir los archivos para tu entrega. Haz la primera prueba en la carpeta nueva para separar tus datos anteriores de los de demostración.

## Compilar por terminal

Desde `03_CODIGO_FINAL`, con CMake y un compilador de C y C++ disponibles, ejecuta lo siguiente.

```sh
cmake -S . -B build
cmake --build build
```

Desde esa misma carpeta, en Linux ejecuta `./build/Cine`. En PowerShell con MinGW ejecuta `.\build\Cine.exe`. Si el generador es Visual Studio, el ejecutable de la configuración predeterminada suele quedar en `.\build\Debug\Cine.exe`.

## Archivos del programa

| Archivo | Qué contiene |
| --- | --- |
| `main.cpp` | Menú principal y submenús con `switch`. |
| `Cine.cpp` y `Cine.h` | Matriz, precios, validación, reservas, búsquedas y reportes. |
| `Archivos.cpp` y `Archivos.h` | Lectura y escritura de `cine.txt` con `ifstream` y `ofstream`. |
| `BaseDatos.cpp` y `BaseDatos.h` | Copia de las 20 butacas en la tabla `butacas` de SQLite. |
| `sqlite/` | Archivos de SQLite que CMake compila con el proyecto. |

La sala se recupera primero de `cine.txt`, que contiene 20 estados. Si falta el texto, el programa usa `cine.db` cuando tiene las 20 butacas en la tabla `butacas` con las columnas `numero` y `estado`. En una carpeta nueva los dos archivos se crean con la sala libre. Usa una sola ejecución a la vez en la misma carpeta.

Para cargar el ejemplo de `04_DATOS`, copia `cine_prueba.txt` en el directorio de trabajo de una prueba y ponle `cine.txt`. El ejemplo reserva las butacas 1, 8, 9 y 20. El total es Q170. `06_EVIDENCIAS` contiene pruebas ejecutadas y una guía para grabar la defensa.

## Subir a GitHub Desktop

1. Si ya tienes repositorio, copia los archivos de la entrega dentro de su carpeta. Incluye `03_CODIGO_FINAL`, `04_DATOS`, `06_EVIDENCIAS`, `README.md` y `.gitignore`. Si es un repositorio nuevo, usa la carpeta `Cine` como raíz.
2. Revisa los cambios y haz un commit llamado `Entrega final cine variante B`. Pulsa **Push origin** o **Publish repository**, según lo que muestre GitHub Desktop.
3. En GitHub, copia el enlace del repositorio y el identificador de ese commit para el informe. Revisa que el catedrático pueda abrir el enlace.

SQLite 3.50.4 se distribuye en `sqlite/` a partir del [paquete oficial de SQLite](https://www.sqlite.org/2025/sqlite-amalgamation-3500400.zip).
