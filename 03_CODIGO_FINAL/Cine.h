#ifndef CINE_H
#define CINE_H

const int FILAS = 5;
const int COLUMNAS = 4;
const int TOTAL_BUTACAS = FILAS * COLUMNAS;

bool iniciarCine();
int leerNumero(int minimo, int maximo);
void reservarButaca();
void cancelarReserva();
void buscarPorNumero();
void buscarPorSector();
void mostrarDisponibilidadPorSector();
void mostrarMapaEIngresos();
void mostrarReservasPorPrecio();

#endif
