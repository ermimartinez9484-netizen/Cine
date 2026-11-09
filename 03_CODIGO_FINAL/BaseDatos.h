#ifndef BASE_DATOS_H
#define BASE_DATOS_H

#include "Cine.h"

const char ARCHIVO_BASE[] = "cine.db";

bool cargarBaseDatos(int sala[][COLUMNAS]);
bool guardarBaseDatos(const int sala[][COLUMNAS]);

#endif
