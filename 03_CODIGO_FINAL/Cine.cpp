#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include "Archivos.h"
#include "BaseDatos.h"
#include "Cine.h"

using namespace std;

int salaCine[FILAS][COLUMNAS] = {0};
const int FILAS_VIP = 2;
const int PRECIO_VIP = 50;
const int PRECIO_GENERAL = 35;

void copiarEnBaseDatos() {
    if (!guardarBaseDatos(salaCine)) {
        cout << "Aviso: cine.txt esta guardado. No se pudo actualizar cine.db.\n";
    }
}

bool iniciarCine() {
    error_code error;
    bool hayTexto = filesystem::exists(ARCHIVO_TEXTO, error);
    if (error) {
        cout << "Error: No se pudo revisar cine.txt.\n";
        return false;
    }

    if (hayTexto) {
        if (!cargarButacas(salaCine)) {
            cout << "Error: No se pudo cargar cine.txt. Debe contener 20 estados 0 o 1.\n";
            return false;
        }
    } else {
        bool hayBase = filesystem::exists(ARCHIVO_BASE, error);
        if (error || (hayBase && !cargarBaseDatos(salaCine))) {
            cout << "Error: No se pudo recuperar la sala desde cine.db.\n";
            return false;
        }
        if (!guardarButacas(salaCine)) {
            cout << "Error: No se pudo crear cine.txt.\n";
            return false;
        }
    }

    copiarEnBaseDatos();
    return true;
}

int leerNumero(int minimo, int maximo) {
    string linea;
    if (!getline(cin, linea)) {
        return -1;
    }

    istringstream entrada(linea);
    int numero;
    char sobrante;
    if (!(entrada >> numero) || (entrada >> sobrante)) {
        cout << "Error: Ingrese un numero entero.\n";
        return -1;
    }
    if (numero < minimo || numero > maximo) {
        cout << "Error: El numero debe estar entre " << minimo << " y " << maximo << ".\n";
        return -1;
    }
    return numero;
}

bool estaDisponible(int fila, int columna) {
    return salaCine[fila][columna] == 0;
}

int obtenerPrecio(int fila) {
    if (fila < FILAS_VIP) {
        return PRECIO_VIP;
    }
    return PRECIO_GENERAL;
}

string obtenerZona(int fila) {
    if (fila < FILAS_VIP) {
        return "VIP";
    }
    return "General";
}

bool guardarCambio(int fila, int columna, int estado) {
    int estadoAnterior = salaCine[fila][columna];
    salaCine[fila][columna] = estado;
    if (!guardarButacas(salaCine)) {
        salaCine[fila][columna] = estadoAnterior;
        cout << "Error: No se pudo guardar cine.txt. La operacion no se aplico.\n";
        return false;
    }
    copiarEnBaseDatos();
    return true;
}

void reservarButaca() {
    mostrarDisponibilidadPorSector();
    cout << "Ingrese el numero de butaca a reservar (1 al " << TOTAL_BUTACAS << "): ";
    int numeroButaca = leerNumero(1, TOTAL_BUTACAS);
    if (numeroButaca == -1) {
        return;
    }

    int fila = (numeroButaca - 1) / COLUMNAS;
    int columna = (numeroButaca - 1) % COLUMNAS;
    if (!estaDisponible(fila, columna)) {
        cout << "Error: La butaca ya esta ocupada.\n";
        return;
    }

    if (guardarCambio(fila, columna, 1)) {
        cout << "Butaca " << numeroButaca << " reservada. Sector " << obtenerZona(fila)
             << ". Cobro Q" << obtenerPrecio(fila) << ".\n";
    }
}

void cancelarReserva() {
    cout << "Ingrese el numero de butaca a cancelar (1 al " << TOTAL_BUTACAS << "): ";
    int numeroButaca = leerNumero(1, TOTAL_BUTACAS);
    if (numeroButaca == -1) {
        return;
    }

    int fila = (numeroButaca - 1) / COLUMNAS;
    int columna = (numeroButaca - 1) % COLUMNAS;
    if (estaDisponible(fila, columna)) {
        cout << "Error: La butaca ya esta libre.\n";
        return;
    }

    if (guardarCambio(fila, columna, 0)) {
        cout << "Reserva cancelada. Reembolso Q" << obtenerPrecio(fila) << ".\n";
    }
}

void mostrarButaca(int fila, int columna) {
    int numero = fila * COLUMNAS + columna + 1;
    cout << "Butaca " << numero << " | " << obtenerZona(fila) << " | Q" << obtenerPrecio(fila);
    if (estaDisponible(fila, columna)) {
        cout << " | Libre\n";
    } else {
        cout << " | Ocupada\n";
    }
}

void buscarPorNumero() {
    cout << "Numero de butaca: ";
    int buscada = leerNumero(1, TOTAL_BUTACAS);
    if (buscada == -1) {
        return;
    }

    // Busqueda secuencial, recorriendo las filas de la matriz.
    for (int fila = 0; fila < FILAS; fila++) {
        for (int columna = 0; columna < COLUMNAS; columna++) {
            int numero = fila * COLUMNAS + columna + 1;
            if (numero == buscada) {
                mostrarButaca(fila, columna);
                return;
            }
        }
    }
}

void buscarPorSector() {
    cout << "Sector (1. VIP, 2. General): ";
    int sector = leerNumero(1, 2);
    if (sector == -1) {
        return;
    }

    int inicio = 0;
    int fin = FILAS_VIP;
    if (sector == 2) {
        inicio = FILAS_VIP;
        fin = FILAS;
    }
    for (int fila = inicio; fila < fin; fila++) {
        for (int columna = 0; columna < COLUMNAS; columna++) {
            mostrarButaca(fila, columna);
        }
    }
}

void mostrarDisponibilidadPorSector() {
    int libresVIP = 0;
    int libresGeneral = 0;

    for (int fila = 0; fila < FILAS; fila++) {
        for (int columna = 0; columna < COLUMNAS; columna++) {
            if (estaDisponible(fila, columna)) {
                if (fila < FILAS_VIP) {
                    libresVIP++;
                } else {
                    libresGeneral++;
                }
            }
        }
    }

    cout << "\n--- DISPONIBILIDAD POR SECTOR ---\n";
    cout << "VIP (Q" << PRECIO_VIP << "): " << libresVIP << " libres de "
         << FILAS_VIP * COLUMNAS << '\n';
    cout << "General (Q" << PRECIO_GENERAL << "): " << libresGeneral << " libres de "
         << (FILAS - FILAS_VIP) * COLUMNAS << '\n';
}

void mostrarMapaEIngresos() {
    int ocupadas = 0;
    int ingresosTotales = 0;
    cout << "\n--- MAPA DE LA SALA ---\n";
    cout << "0 = Libre | 1 = Ocupada\n";

    for (int fila = 0; fila < FILAS; fila++) {
        cout << obtenerZona(fila) << " | ";
        for (int columna = 0; columna < COLUMNAS; columna++) {
            int numero = fila * COLUMNAS + columna + 1;
            cout << "[B" << numero << ": " << salaCine[fila][columna] << "] ";
            if (!estaDisponible(fila, columna)) {
                ocupadas++;
                ingresosTotales += obtenerPrecio(fila);
            }
        }
        cout << '\n';
    }
    cout << "Ocupadas: " << ocupadas << " de " << TOTAL_BUTACAS << '\n';
    cout << "Ingresos totales: Q" << ingresosTotales << '\n';
}

void ordenarPorPrecio(int butacas[], int cantidad) {
    // Burbuja: comparar precios vecinos e intercambiar si estan al reves.
    for (int i = 0; i < cantidad - 1; i++) {
        for (int j = 0; j < cantidad - 1 - i; j++) {
            int filaActual = (butacas[j] - 1) / COLUMNAS;
            int filaSiguiente = (butacas[j + 1] - 1) / COLUMNAS;
            if (obtenerPrecio(filaActual) > obtenerPrecio(filaSiguiente)) {
                int auxiliar = butacas[j];
                butacas[j] = butacas[j + 1];
                butacas[j + 1] = auxiliar;
            }
        }
    }
}

void mostrarReservasPorPrecio() {
    int reservadas[TOTAL_BUTACAS];
    int cantidad = 0;
    for (int fila = 0; fila < FILAS; fila++) {
        for (int columna = 0; columna < COLUMNAS; columna++) {
            if (!estaDisponible(fila, columna)) {
                reservadas[cantidad] = fila * COLUMNAS + columna + 1;
                cantidad++;
            }
        }
    }

    cout << "\n--- RESERVAS DE MENOR A MAYOR PRECIO ---\n";
    if (cantidad == 0) {
        cout << "No hay reservas.\n";
        return;
    }
    ordenarPorPrecio(reservadas, cantidad);
    for (int i = 0; i < cantidad; i++) {
        int fila = (reservadas[i] - 1) / COLUMNAS;
        int columna = (reservadas[i] - 1) % COLUMNAS;
        mostrarButaca(fila, columna);
    }
}
