#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include "Cine.h"

const char ARCHIVO_TEXTO[] = "cine.txt";

bool cargarButacas(int sala[][COLUMNAS]);
bool guardarButacas(const int sala[][COLUMNAS]);

#endif
