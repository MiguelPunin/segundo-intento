#include "funciones.h"
#include <stdio.h>
#include <string.h>

// Funciones para manejar archivos

void guardarDatos(char clientes[][2][MAX_LONGITUD], int numClientes, int reserva[][4], int numCompras) {
    FILE *archivoClientes = fopen("archivoClientes.txt", "w");
    FILE *archivoReservas = fopen("archivoReservas.txt", "w");

    if (archivoClientes != NULL) {
        for (int i = 0; i < numClientes; i++) {
            fprintf(archivoClientes, "%s,%s\n", clientes[i][0], clientes[i][1]);
        }
        fclose(archivoClientes);
    }

    if (archivoReservas != NULL) {
        for (int i = 0; i < numCompras; i++) {
            fprintf(archivoReservas, "%d,%d,%d,%d\n", reserva[i][0], reserva[i][1], reserva[i][2], reserva[i][3]);
        }
        fclose(archivoReservas);
    }
}

void cargarDatos(char clientes[][2][MAX_LONGITUD], int *numClientes, int reserva[][4], int *numCompras) {
    FILE *archivoClientes = fopen("archivoClientes.txt", "r");
    FILE *archivoReservas = fopen("archivoReservas.txt", "r");

    char linea[MAX_LONGITUD * 2];
    *numClientes = 0;
    *numCompras = 0;

    if (archivoClientes != NULL) {
        while (fgets(linea, sizeof(linea), archivoClientes)) {
            char *token = strtok(linea, ",");
            snprintf(clientes[*numClientes][0], MAX_LONGITUD, "%s", token);
            token = strtok(NULL, ",");
            snprintf(clientes[*numClientes][1], MAX_LONGITUD, "%s", token);
            clientes[*numClientes][1][strcspn(clientes[*numClientes][1], "\n")] = 0; // Elimina el salto de línea
            (*numClientes)++;
        }
        fclose(archivoClientes);
    }

    if (archivoReservas != NULL) {
        while (fgets(linea, sizeof(linea), archivoReservas)) {
            char *token = strtok(linea, ",");
            reserva[*numCompras][0] = atoi(token);
            token = strtok(NULL, ",");
            reserva[*numCompras][1] = atoi(token);
            token = strtok(NULL, ",");
            reserva[*numCompras][2] = atoi(token);
            token = strtok(NULL, ",");
            reserva[*numCompras][3] = atoi(token);
            (*numCompras)++;
        }
        fclose(archivoReservas);
    }
}

// Funciones originales

void ingresarCliente(char clientes[][2][MAX_LONGITUD], int *numClientes) {
    if (*numClientes >= MAX_CLIENTES) {
        printf("No se pueden ingresar más clientes.\n");
        return;
    }
    printf("Ingrese el nombre del cliente: ");
    fgets(clientes[*numClientes][0], MAX_LONGITUD, stdin);
    clientes[*numClientes][0][strcspn(clientes[*numClientes][0], "\n")] = 0; // Elimina el salto de línea
    printf("Ingrese el ID del cliente: ");
    fgets(clientes[*numClientes][1], MAX_LONGITUD, stdin);
    clientes[*numClientes][1][strcspn(clientes[*numClientes][1], "\n")] = 0; // Elimina el salto de línea
    (*numClientes)++;
    printf("Cliente ingresado con éxito.\n");
}

void listarPeliculas(char peliculas[][4][MAX_LONGITUD]) {
    printf("Películas disponibles:\n");
    for (int i = 0; i < MAX_PELICULAS; i++) {
        if (strcmp(peliculas[i][0], "") != 0) {
            printf("%s Nombre: %s Hora: %s Género: %s\n", peliculas[i][0], peliculas[i][1], peliculas[i][2], peliculas[i][3]);
        }
    }
}

void buscarporNombre(char peliculas[][4][MAX_LONGITUD]) {
    char nombre[MAX_LONGITUD];
    printf("Ingrese el nombre de la película: ");
    fgets(nombre, MAX_LONGITUD, stdin);
    nombre[strcspn(nombre, "\n")] = 0; // Elimina el salto de línea

    for (int i = 0; i < MAX_PELICULAS; i++) {
        if (strcmp(peliculas[i][1], nombre) == 0) {
            printf("%s Nombre: %s Hora: %s Género: %s\n", peliculas[i][0], peliculas[i][1], peliculas[i][2], peliculas[i][3]);
            return;
        }
    }
    printf("Película no encontrada.\n");
}

void buscarporGenero(char peliculas[][4][MAX_LONGITUD]) {
    char genero[MAX_LONGITUD];
    printf("Ingrese el género de la película: ");
    fgets(genero, MAX_LONGITUD, stdin);
    genero[strcspn(genero, "\n")] = 0; // Elimina el salto de línea

    for (int i = 0; i < MAX_PELICULAS; i++) {
        if (strcmp(peliculas[i][3], genero) == 0) {
            printf("%s Nombre: %s Hora: %s Género: %s\n", peliculas[i][0], peliculas[i][1], peliculas[i][2], peliculas[i][3]);
            return;
        }
    }
    printf("Película no encontrada.\n");
}

void comprarTicket(char peliculas[][4][MAX_LONGITUD], double precios[], char clientes[][2][MAX_LONGITUD], int reserva[][4]) {
    int clienteCedula, peliculaID;
    char cedula[MAX_LONGITUD];
    int clienteEncontrado = -1;
    int cantidadEntradas[3] = {0, 0, 0};

    // Mostrar clientes registrados
    printf("Clientes registrados:\n");
    for (int i = 0; i < MAX_CLIENTES; i++) {
        printf("%d. %s - %s\n", i + 1, clientes[i][0], clientes[i][1]);
    }
    printf("¿Su cédula está en la lista? (1.Si / 2.No): ");
    int opcion;
    scanf("%d", &opcion);
    getchar();  // Limpia el buffer de entrada

    if (opcion == 1) {
        printf("Seleccione el número del cliente: ");
        scanf("%d", &clienteCedula);
        getchar();  // Limpia el buffer de entrada
        clienteCedula--; // Ajustar índice
        clienteEncontrado = clienteCedula;
    } else {
        printf("Ingrese su cédula: ");
        fgets(cedula, MAX_LONGITUD, stdin);
        cedula[strcspn(cedula, "\n")] = 0; // Elimina el salto de línea

        // Buscar cédula en la lista de clientes
        for (int i = 0; i < MAX_CLIENTES; i++) {
            if (strcmp(clientes[i][1], cedula) == 0) {
                clienteEncontrado = i;
                break;
            }
        }

        // Si no se encuentra, añadir nuevo cliente
        if (clienteEncontrado == -1) {
            printf("Ingrese su nombre: ");
            fgets(clientes[MAX_CLIENTES - 1][0], MAX_LONGITUD, stdin); // Leer hasta el final de la línea
            strcpy(clientes[MAX_CLIENTES - 1][1], cedula);
            clienteEncontrado = MAX_CLIENTES - 1;
        }
    }

    listarPeliculas(peliculas);

    printf("Seleccione el número de la película: ");
    scanf("%d", &peliculaID);
    getchar();  // Limpia el buffer de entrada

    // Solicitar la cantidad de entradas por tipo
    printf("¿Cuántas entradas de tipo Normal (0) quiere?: ");
    scanf("%d", &cantidadEntradas[0]);
    getchar();  // Limpia el buffer de entrada
    printf("¿Cuántas entradas de tipo Niños (1) quiere?: ");
    scanf("%d", &cantidadEntradas[1]);
    getchar();  // Limpia el buffer de entrada
    printf("¿Cuántas entradas de tipo Tercera Edad (2) quiere?: ");
    scanf("%d", &cantidadEntradas[2]);
    getchar();  // Limpia el buffer de entrada

    // Registrar la reserva y calcular la factura
    double total = 0.0;
    printf("Factura:\n");
    for (int tipoEntrada = 0; tipoEntrada < 3; tipoEntrada++) {
        if (cantidadEntradas[tipoEntrada] > 0) {
            printf("Tipo de Entrada: %d Cantidad: %d Precio por unidad: %.2f Subtotal: %.2f\n", tipoEntrada, cantidadEntradas[tipoEntrada], precios[tipoEntrada], cantidadEntradas[tipoEntrada] * precios[tipoEntrada]);
            total += cantidadEntradas[tipoEntrada] * precios[tipoEntrada];
        }
    }
    printf("Total a pagar: %.2f\n", total);

    for (int tipoEntrada = 0; tipoEntrada < 3; tipoEntrada++) {
        for (int i = 0; i < cantidadEntradas[tipoEntrada]; i++) {
            for (int j = 0; j < MAX_RESERVAS; j++) {
                if (reserva[j][0] == -1) {
                    reserva[j][0] = clienteEncontrado;
                    reserva[j][1] = peliculaID - 1;
                    reserva[j][2] = tipoEntrada;
                    reserva[j][3] = 1;
                    break;
                }
            }
        }
    }

    printf("Tickets comprados exitosamente.\n");
}

void verCompras(char peliculas[][4][MAX_LONGITUD], double precios[], char clientes[][2][MAX_LONGITUD], int reserva[][4]) {
    for (int i = 0; i < MAX_RESERVAS; i++) {
        if (reserva[i][0] != -1) {
            int clienteID = reserva[i][0];
            int peliculaID = reserva[i][1];
            int tipoEntrada = reserva[i][2];
            printf("Cliente: %s Película: %s Tipo de Entrada: %d Precio: %.2f\n", clientes[clienteID][0], peliculas[peliculaID][1], tipoEntrada, precios[tipoEntrada]);
        }
    }
}

void calcularCostoTotal(double precios[], int reserva[][4]) {
    double total = 0.0;
    for (int i = 0; i < MAX_RESERVAS; i++) {
        if (reserva[i][0] != -1) {
            int tipoEntrada = reserva[i][2];
            total += precios[tipoEntrada];
        }
    }
    printf("El costo total de todas las compras es: %.2f\n", total);
}
