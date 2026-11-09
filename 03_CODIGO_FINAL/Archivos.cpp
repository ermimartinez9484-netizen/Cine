#include <filesystem>
#include <fstream>
#include <string>
#include "Archivos.h"

using namespace std;

bool cargarButacas(int sala[][COLUMNAS]) {
    ifstream archivo(ARCHIVO_TEXTO);
    if (!archivo) {
        return false;
    }

    for (int fila = 0; fila < FILAS; fila++) {
        for (int columna = 0; columna < COLUMNAS; columna++) {
            string estado;
            if (!(archivo >> estado) || (estado != "0" && estado != "1")) {
                return false;
            }
            sala[fila][columna] = estado[0] - '0';
        }
    }

    string sobrante;
    if (archivo >> sobrante) {
        return false;
    }
    return archivo.eof() && !archivo.bad();
}

bool guardarButacas(const int sala[][COLUMNAS]) {
    // El archivo anterior queda en su lugar hasta terminar la nueva copia.
    const char temporal[] = "cine.tmp";
    ofstream archivo(temporal);
    if (!archivo) {
        return false;
    }

    for (int fila = 0; fila < FILAS; fila++) {
        for (int columna = 0; columna < COLUMNAS; columna++) {
            archivo << sala[fila][columna] << ' ';
        }
        archivo << '\n';
    }
    archivo.close();

    error_code error;
    if (archivo) {
        filesystem::rename(temporal, ARCHIVO_TEXTO, error);
    }
    if (!archivo || error) {
        filesystem::remove(temporal, error);
        return false;
    }
    return true;
}
