#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX_PELICULAS 20
#define MAX_CLIENTES 5
#define MAX_LONGITUD 40
#define MAX_RESERVAS 10

void ingresarCliente(char clientes[][2][MAX_LONGITUD], int *numClientes);
void listarPeliculas(char peliculas[][4][MAX_LONGITUD]);
void buscarporNombre(char peliculas[][4][MAX_LONGITUD]);
void buscarporGenero(char peliculas[][4][MAX_LONGITUD]);
void comprarTicket(char peliculas[][4][MAX_LONGITUD], double precios[], char clientes[][2][MAX_LONGITUD], int reserva[][4]);
void verCompras(char peliculas[][4][MAX_LONGITUD], double precios[], char clientes[][2][MAX_LONGITUD], int reserva[][4]);
void calcularCostoTotal(double precios[], int reserva[][4]);
void guardarDatos(char clientes[][2][MAX_LONGITUD], int numClientes, int reserva[][4], int numCompras);
void cargarDatos(char clientes[][2][MAX_LONGITUD], int *numClientes, int reserva[][4], int *numCompras);

#endif
