#include <stdio.h>
#include <stdlib.h>
#include "colacp.h"


int f(TEntrada entr1, TEntrada entr2) {
    if(entr1 ->clave < entr2 ->clave) {
        return -1;
    } else if(entr1 ->clave == entr2 ->clave) {
        return 0;
    } else if(entr1 ->clave > entr2 ->clave) {
        return 1;
    } else {
        return CCP_NO_INI;
    }
}

TColaCP crear_cola_cp(int (*f)(TEntrada, TEntrada)) {
    TColaCP cola= (struct cola_con_prioridad *) malloc(sizeof(struct cola_con_prioridad));

    cola ->cantidad_elementos=0;
    cola ->raiz= ELE_NULO;
    cola ->comparador= f;

    return cola;
}


int cp_insertar(TColaCP cola, TEntrada entr){
    int cantidad= (cola->cantidad_elementos);

    TNodo nuevo= (struct nodo *) malloc(sizeof(struct nodo)); //Inicializo los atributos del nodo que creé
    nuevo->entrada=entr;
    nuevo->hijo_derecho= ELE_NULO;
    nuevo->hijo_izquierdo= ELE_NULO;

    if(cantidad==0){      //si la cola está vacía, inserto el nodo como raíz
        cola -> raiz= nuevo;
        nuevo->padre= ELE_NULO;
    }
    else{               //si no está vacía la cola
        int pos_padre= buscar_camino((cantidad+1)/2); // busco el nodo que sera el padre de nuestro nuevo nodo
        TNodo nodo_padre= buscar_nodo(pos_padre, cola->raiz);
        if(nodo_padre->hijo_izquierdo == NULL){
            nodo_padre ->hijo_izquierdo=nuevo;
        }
        else{
            if(nodo_padre->hijo_derecho==NULL){
                nodo_padre ->hijo_derecho=nuevo;
            }
            else{
                return 0;
            }
        }
        nuevo->padre=nodo_padre;
        burbujear_arriba(cola, nuevo);
    }
    cola->cantidad_elementos= cantidad+1;

    return 1;
}

TEntrada cp_eliminar(TColaCP cola){
    if(cola->cantidad_elementos==0){
        return ELE_NULO;
    }
    TEntrada retorno= cola->raiz->entrada; //guardo el valor de la entrada con mayor prioridad
    if(cola->cantidad_elementos>1){
        TNodo ultimo= buscar_nodo(cola->cantidad_elementos, cola->raiz);
        cola->raiz->entrada= (ultimo->entrada); //tomo el valor del ultimo nodo y se lo asigno a la raiz
        TNodo padre_ult= ultimo->padre;
        if(padre_ult->hijo_derecho==ultimo){
            padre_ult->hijo_derecho=ELE_NULO;
        }
        else{
            padre_ult->hijo_izquierdo=ELE_NULO;
        }
        free(ultimo);
        burbujear_abajo(cola->raiz);
    }
    else{
        free(cola->raiz);
        cola->raiz=NULL;
    }
    cola->cantidad_elementos= (cola->cantidad_elementos)-1;
    return retorno;
}

void cp_destruir(TColaCP cola, void (*fEliminar)(TEntrada) ){
    TNodo ultimo;
    while(cola->raiz!=null){
      ultimo=  buscar_nodo(cola->cantidad_elementos);
      fEliminar(ultimo->entrada);
      free(ultimo);
      cola->cantidad_elementos= (cola->cantidad_elementos-1);
    }
}

int cp_cantidad(TColaCP cola){
    return cola->cantidad_elementos;
}



void burbujear_arriba(TColaCP cola, TNodo burbujear){
    TEntrada aux;
    TNodo actual=burbujear;
    TNodo padre= burbujear->padre;
    while(padre!= ELE_NULO && (cola->comparador(actual->entrada->clave,padre->entrada->clave))==1  ){
        aux= actual->entrada;
        actual-> entrada = (padre->entrada);
        padre->entrada = aux;
        actual=padre;
        padre= (actual->padre);
    }
}

void burbujear_abajo(TNodo primero){
    TNodo prioridad;
    int seguir= TRUE;
    while(seguir==TRUE){
        if(primero->hijo_izquierdo != NULL){  //si el nodo pasado por parametro tiene hijo izquierdo

            int comp_izq = f(primero->entrada, primero->hijo_izquierdo->entrada);
            if(primero->hijo_derecho != NULL){  //si el nodo tambien tiene hijo derecho

                int comp_der = f(primero->entrada, primero->hijo_derecho->entrada);
                if(comp_izq == -1 && comp_der == -1){ //si ambos hijos tienen mayor prioridad que el padre
                    int comp_hijos = f(primero->hijo_izquierdo->entrada, primero->hijo_derecho->entrada);
                    if(comp_hijos>=0){  //si el izquierdo tiene la misma o mayor prioridad que el derecgi
                        prioridad = primero->hijo_izquierdo;
                    }else{
                        prioridad = primero->hijo_derecho;
                    }
                }else{ //no es verdad que los dos hijos tienen mayor prioridad que el padre
                    if(comp_izq == -1){  //el hijo izq tiene mayor prioridad
                        prioridad = primero->hijo_izquierdo;
                    }else{
                        if(comp_der == -1){ //el hijo der tiene mayor prioridad
                            prioridad = primero->hijo_derecho;
                        }else{//ninguno de los hijos tiene mayor prioridad
                        prioridad = primero;
                        }
                    }
                }
            }else{// solo tiene hijo izq
                if(comp_izq == -1){ //si el hijo izq tiene mayor prioridad
                    prioridad = primero->hijo_izquierdo;
                }else{
                    prioridad = primero;
                }
            }
        }else{  //no tiene hjijos
            prioridad = primero;
        }
        if(prioridad != primero){
            TEntrada aux = primero->entrada;
            primero->entrada= prioridad->entrada;
            prioridad->entrada= aux;
        }else{
            seguir=FALSE;
        }
    }
}

int buscar_camino(int decimal){ //convierte el numero decimal a binario, pero ordenando los numeros al reves
    int cociente=decimal;
    int resto;
    int binario=0;
    while(cociente>0){ //sin embargo, como al dar vuelta el número los 0 se perderían al estar a la izquierda, le sumo 1 al numero correspondiente en binario
        resto= (cociente%2) +1;
        cociente=cociente/2;
        binario= binario+(resto);
        binario=binario*10;
    }
    return binario;
}

TNodo buscar_nodo(int posicion, TNodo raiz){
   int camino= buscar_camino(posicion); //el numero en binario me indica como debo recorrer el árbol desde la raíz para poder llegar al nodo deseado
   TNodo retorno= raiz;
   int direccion;
   camino=camino/10; // descarto el primer digito
   while(camino>0){
        direccion=camino % 10;
        camino=camino/10;
        switch(direccion) {
                case 1: retorno = retorno ->hijo_izquierdo;
                case 2: retorno = retorno ->hijo_derecho;
        }
    }
   return retorno;
}
