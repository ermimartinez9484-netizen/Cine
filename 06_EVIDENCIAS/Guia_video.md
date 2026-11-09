# Guía para la defensa en video

## Preparación

Abre `03_CODIGO_FINAL` en CLion. Graba la pantalla y tu voz. Para que los resultados de esta secuencia coincidan, empieza con una sala vacía en una carpeta nueva. Ten visibles el código y la consola.

## Qué mostrar y explicar

1. **Presentación.** Di tu nombre, carné, el nombre del proyecto y que te asignaron la Variante B. Explica que una taquilla reserva y cancela butacas de dos sectores con precios distintos.
2. **Menú.** En `main.cpp`, muestra cómo el `while` repite el menú y el `switch` llama a la función de la opción elegida. En los submenús, `0` vuelve al menú principal.
3. **Matriz y validación.** En `Cine.cpp`, señala `salaCine`, `FILAS_VIP`, los precios y `leerNumero`. Para la butaca 9 se resta 1, queda 8, y se obtiene la fila con `8 / 4 = 2` y la columna con `8 % 4 = 0`. Los índices empiezan en cero. El estado `0` es libre y el `1` es ocupado. `estaDisponible` evita reservar dos veces la misma posición.
4. **Búsquedas.** En `buscarPorNumero`, el primer `for` avanza por filas y el segundo por columnas. Se compara el número calculado con el número ingresado. `buscarPorSector` usa un rango de filas y muestra las butacas de la zona elegida.
5. **Ordenamiento.** Muestra `mostrarReservasPorPrecio` y `ordenarPorPrecio`. El primer procedimiento copia los números ocupados a un arreglo. El segundo compara dos precios vecinos y cambia los números de lugar con `auxiliar` si están al revés. La matriz queda en su orden original.
6. **Archivos y base.** Muestra `cargarButacas` y `guardarButacas` en `Archivos.cpp`. Los dos ciclos pasan por los mismos 20 espacios para leerlos o escribirlos. El archivo temporal permite terminar la escritura antes de sustituir `cine.txt`. En `BaseDatos.cpp`, `guardarBaseDatos` guarda la misma matriz en la tabla `butacas` de `cine.db`.

## Prueba en pantalla

| Paso | Qué elegir | Qué debe pasar |
| --- | --- | --- |
| 1 | Compila y ejecuta **Cine**. Reserva la 8 y después la 9. | Cobros de Q50 y Q35. |
| 2 | Intenta reservar otra vez la 8 y luego la 21. | Avisos de butaca ocupada y número fuera de rango. |
| 3 | Busca la 9 por número y consulta el sector VIP. | La 9 sale ocupada y el sector VIP muestra las butacas 1 a 8. |
| 4 | Abre los tres reportes desde la opción 4. | 7 VIP y 11 General libres, total Q85 y la 9 antes de la 8 en la lista por precio. |
| 5 | Cancela la reserva de la 8. Prueba cancelarla una segunda vez. | Primero se reembolsan Q50. Después aparece el aviso de que ya está libre. |
| 6 | Sal con `0`, vuelve a ejecutar y abre el mapa. | La 9 sigue ocupada. Queda 1 ocupada de 20 e ingresos de Q35. |

Al cerrar el video, explica con tus palabras qué validación fue más importante y cómo comprobaste que el archivo se carga. Practica localizar `PRECIO_GENERAL` y explicar qué pasaría si se cambia de Q35 a Q40. Comprueba el audio y la legibilidad al terminar.
