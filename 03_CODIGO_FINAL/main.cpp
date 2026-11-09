#include <iostream>
#include "Cine.h"

using namespace std;

void menuBusquedas() {
    int opcion = -1;
    while (opcion != 0 && cin) {
        cout << "\n--- BUSQUEDAS ---\n";
        cout << "1. Por numero de butaca\n";
        cout << "2. Por sector\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";
        opcion = leerNumero(0, 2);
        switch (opcion) {
            case 1:
                buscarPorNumero();
                break;
            case 2:
                buscarPorSector();
                break;
        }
    }
}

void menuReportes() {
    int opcion = -1;
    while (opcion != 0 && cin) {
        cout << "\n--- REPORTES ---\n";
        cout << "1. Disponibilidad por sector\n";
        cout << "2. Mapa de la sala e ingresos\n";
        cout << "3. Reservas ordenadas por precio\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";
        opcion = leerNumero(0, 3);
        switch (opcion) {
            case 1:
                mostrarDisponibilidadPorSector();
                break;
            case 2:
                mostrarMapaEIngresos();
                break;
            case 3:
                mostrarReservasPorPrecio();
                break;
        }
    }
}

void mostrarMenu() {
    cout << "\n--- RESERVACIONES DE CINE ---\n";
    cout << "1. Reservar butaca\n";
    cout << "2. Cancelar reserva\n";
    cout << "3. Buscar butacas\n";
    cout << "4. Ver reportes\n";
    cout << "0. Salir\n";
    cout << "Opcion: ";
}

int main() {
    if (!iniciarCine()) {
        return 1;
    }

    int opcion = -1;
    while (opcion != 0 && cin) {
        mostrarMenu();
        opcion = leerNumero(0, 4);
        switch (opcion) {
            case 1:
                reservarButaca();
                break;
            case 2:
                cancelarReserva();
                break;
            case 3:
                menuBusquedas();
                break;
            case 4:
                menuReportes();
                break;
        }
    }
    return 0;
}
