#ifndef PLAN_H
#define PLAN_H

#include <stdio.h>

#include "colacp.h"


struct punto {
	float x;
	float y;
};


typedef struct ciudad {
	char *nombre;
	float pos_x;
	float pos_y;
} * TCiudad;



void mostrar(FILE *fp, int(*comp)(TEntrada, TEntrada));


float reducir_horas_manejo(FILE *fp);


void salir(void);

#endif
