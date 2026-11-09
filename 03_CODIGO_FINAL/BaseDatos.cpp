#include <string>
#include "BaseDatos.h"
#include "sqlite/sqlite3.h"

using namespace std;

bool cargarBaseDatos(int sala[][COLUMNAS]) {
    sqlite3* base = nullptr;
    if (sqlite3_open_v2(ARCHIVO_BASE, &base, SQLITE_OPEN_READONLY, nullptr) != SQLITE_OK) {
        sqlite3_close(base);
        return false;
    }

    const char consulta[] = "SELECT numero, estado FROM butacas ORDER BY numero;";
    sqlite3_stmt* filaBase = nullptr;
    if (sqlite3_prepare_v2(base, consulta, -1, &filaBase, nullptr) != SQLITE_OK) {
        sqlite3_close(base);
        return false;
    }

    int esperado = 1;
    int resultado = sqlite3_step(filaBase);
    while (resultado == SQLITE_ROW && esperado <= TOTAL_BUTACAS) {
        sqlite3_int64 numero = sqlite3_column_int64(filaBase, 0);
        sqlite3_int64 estado = sqlite3_column_int64(filaBase, 1);
        if (sqlite3_column_type(filaBase, 0) != SQLITE_INTEGER ||
            sqlite3_column_type(filaBase, 1) != SQLITE_INTEGER ||
            numero != esperado || (estado != 0 && estado != 1)) {
            break;
        }
        sala[(numero - 1) / COLUMNAS][(numero - 1) % COLUMNAS] = estado;
        esperado++;
        resultado = sqlite3_step(filaBase);
    }

    sqlite3_finalize(filaBase);
    sqlite3_close(base);
    return resultado == SQLITE_DONE && esperado == TOTAL_BUTACAS + 1;
}

bool guardarBaseDatos(const int sala[][COLUMNAS]) {
    sqlite3* base = nullptr;
    if (sqlite3_open(ARCHIVO_BASE, &base) != SQLITE_OK) {
        sqlite3_close(base);
        return false;
    }

    // SQLite confirma la tabla completa en una sola transaccion.
    string sql = "BEGIN;"
                 "CREATE TABLE IF NOT EXISTS butacas ("
                 "numero INTEGER PRIMARY KEY, "
                 "estado INTEGER NOT NULL CHECK (estado IN (0, 1)));"
                 "DELETE FROM butacas;";
    int numero = 1;
    for (int fila = 0; fila < FILAS; fila++) {
        for (int columna = 0; columna < COLUMNAS; columna++) {
            sql += "INSERT INTO butacas (numero, estado) VALUES (" + to_string(numero) + ", "
                + to_string(sala[fila][columna]) + ");";
            numero++;
        }
    }
    sql += "COMMIT;";

    int resultado = sqlite3_exec(base, sql.c_str(), nullptr, nullptr, nullptr);
    if (resultado != SQLITE_OK) {
        sqlite3_exec(base, "ROLLBACK;", nullptr, nullptr, nullptr);
    }
    sqlite3_close(base);
    return resultado == SQLITE_OK;
}
