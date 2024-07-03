#include <stdio.h>
#include <string.h>
#include "funciones.h"

#define MAX_PELICULAS 20
#define MAX_CLIENTES 5
#define MAX_LONGITUD 40
#define MAX_RESERVAS 10

int main() {
    char peliculas[MAX_PELICULAS][4][MAX_LONGITUD] = {
        {"1", "Avatar", "10:20", "Fantasia"},
        {"2", "Cars 1", "11:20", "Animada"},
        {"3", "Barbie y el castillo de princesas", "12:20", "Animada"},
        {"4", "El conjuro 1", "17:50", "Terror"},
        {"5", "Mision Imposible", "15:30", "Accion"},
        {"6", "Matrix", "13:30", "Ciencia ficcion"},
        {"7", "Intensamente 2", "18:00", "Animada"},
        {"8", "BAD BOYS", "16:00", "Accion"},
        {"9", "Fast and furious", "14:30", "Accion"},
        {"10", "La llorona", "18:20", "Terror"},
        {"11", "50 sombras de grey", "20:00", "Romance"},
        {"12", "Pocoyo", "11:40", "Animado"}
    };

    double precios[3] = {7, 3.5, 3};
    char clientes[MAX_CLIENTES][2][MAX_LONGITUD] = {
        {"Maria Gomez", "142658735"},
        {"Luis Perez", "123456788"},
        {"Pedro Rodriguez", "84824692"},
        {"Ana Hernandez", "459276183"},
        {"Alejandro Larrea", "102795432"}
    };

    int reserva[MAX_RESERVAS][4] = {
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1}
    };

    int numClientes = 5;
    int numCompras = 0;

    // Cargar datos desde los archivos
    cargarDatos(clientes, &numClientes, reserva, &numCompras);

    int opcion;

    do {
        printf("\nMenú de películas disponibles\n");
        printf("1. Ingresar un nuevo cliente\n");
        printf("2. Ver las películas\n");
        printf("3. Buscar película\n");
        printf("4. Comprar un ticket\n");
        printf("5. Ver las compras realizadas\n");
        printf("6. Salir\n");
        printf("Ingrese una opción: ");
        scanf("%d", &opcion);
        getchar();  // Limpia el buffer de entrada

        switch (opcion) {
            case 1:
                ingresarCliente(clientes, &numClientes);
                guardarDatos(clientes, numClientes, reserva, numCompras);
                break;
            case 2:
                listarPeliculas(peliculas);
                break;
            case 3:
                printf("1. Por nombre\n2. Por Género\n>> ");
                int opcionBusqueda;
                scanf("%d", &opcionBusqueda);
                getchar();  // Limpia el buffer de entrada
                if (opcionBusqueda == 1) {
                    buscarporNombre(peliculas);
                } else if (opcionBusqueda == 2) {
                    buscarporGenero(peliculas);
                } else {
                    printf("Opción no válida.\n");
                }
                break;
            case 4:
                comprarTicket(peliculas, precios, clientes, reserva);
                guardarDatos(clientes, numClientes, reserva, numCompras);
                break;
            case 5:
                verCompras(peliculas, precios, clientes, reserva);
                break;
            case 6:
                printf("Saliendo del programa...\n");
                guardarDatos(clientes, numClientes, reserva, numCompras);
                break;
            default:
                printf("Opción no válida, por favor intente nuevamente.\n");
        }
    } while (opcion != 6);

    return 0;
}
