# Cine - Variante B

Programa de consola en C++17 para reservar, cancelar y buscar butacas.
Hay 20 butacas. De la 1 a la 8 son VIP y cuestan Q50. De la 9 a la 20 son
General y cuestan Q35.

## Cómo correrlo en CLion

1. Abrí la carpeta `03_CODIGO_FINAL` y esperá a que cargue CMake.
2. Seleccioná `Cine`. En `Run → Edit Configurations`, poné
   `03_CODIGO_FINAL` como `Working directory`.
3. Presioná `Run` para compilar y ejecutar el programa.

## Prueba rápida

Reservá las butacas 8 y 9. Entrá a reportes con la opción 4 y elegí
la opción 2 para ver el mapa. El total debe ser Q85.

Las reservas se guardan en `cine.txt` y se respaldan en `cine.db` con
SQLite. Si cerrás y volvés a abrir el programa, las dos butacas deben
seguir ocupadas.
