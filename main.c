
#include <stdio.h>
#include <stdlib.h>

#include "colacp.h"
#include "comparable.h"
#include "planificador.h"
#include "const.h"

int ascendente(TEntrada t1, TEntrada t2);
int descendente(TEntrada t1, TEntrada t2);

/**
 * @brief Muestra el menu de opciones del planificador
 * @return Caracter identificador de la opcion elegida
 */

static char mostrar_menu(void);

int main(int argc, char **argv) {

	char seleccion;
	FILE *fp;

	if (argc != 2) {
		fprintf(stderr, "Error. Invocacion invalida.\n"
				"\t\tplanificador viajero.txt\n");
		return BAD_ARGS;
	}

	fp = fopen(argv[1], "r");
	if (!fp) {
		fprintf(stderr, "Error. no se puede abrir el archivo que nombraste %s.\n", argv[1]);
		return FILE_ERR;
	}

	seleccion = mostrar_menu();

	switch (seleccion) {
	case '1': // Mostrar ascendente
		mostrar(fp, &ascendente);
		break;
	case '2': // Mostrar descendente
		mostrar(fp, &descendente);
		break;
	case '3': // Reducir horas de manejo
		reducir_horas_manejo(fp);
		break;
	case '4':
		salir();
		break;
	default:
		fprintf(stderr, "Error. Operacion invalida.\n");
		return BAD_ARGS;
	}

	fclose(fp);

	return 0;
}

static char mostrar_menu(void) {

	char c;

	fprintf(stdout, "Hola! Estas en nuestro planificador de viajes.\n");
	fprintf(stdout,"Seleccione un número dependiendo de que desea realizar: \n"
          "1. Mostrar las ciudades en orden ascendente\n"
			"2. Mostrar las ciudades en orden descendente\n"
			"3. Motrar la ruta de menor tiempo al volante\n"
			"4. Salir del programa\n"
			);

	fscanf(stdin, "%c", &c);

	return c;
}
