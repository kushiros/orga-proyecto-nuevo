/*
 */
#include "colacp.h"

int ascendente(TEntrada t1, TEntrada t2) {
	int val = 0;

	float *c1, *c2;

	c1 = (float *) t1->clave;
	c2 = (float *) t2->clave;

	if (*c1 > *c2)
		val = -1;
	else if (*c1 < *c2)
		val = 1;

	return val;
}

int descendente(TEntrada t1, TEntrada t2) {
	return -ascendente(t1, t2);
}
