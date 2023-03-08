/* 5431590 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/iterador.h"

typedef struct Nodo *PunteroaNodo;

struct Nodo {
  nat info;
  PunteroaNodo siguiente;
};

struct _rep_iterador {
  PunteroaNodo inicioDeIterador;
  PunteroaNodo finalDeIterador;
  PunteroaNodo actualEnIterador;
};

TIterador crearIterador() { 
	TIterador newIterador = new _rep_iterador;
  newIterador->inicioDeIterador = NULL;
  newIterador->finalDeIterador = NULL;
  newIterador->actualEnIterador = NULL;
  return newIterador;
}

void liberarIterador(TIterador iter) {
	iter->actualEnIterador = iter->inicioDeIterador;
  while(estaDefinidaActual(iter))
  {
    iter->inicioDeIterador = iter->actualEnIterador->siguiente;
    delete iter->actualEnIterador;
    iter->actualEnIterador = iter->inicioDeIterador;
  }
  delete iter;
}

bool estaDefinidaActual(TIterador iter) { 
  return iter->actualEnIterador != NULL;
}

void agregarAIterador(nat elem, TIterador const iter) {
	PunteroaNodo newNode = new Nodo;
  newNode->info = elem;
  newNode->siguiente = NULL;
  if(iter->finalDeIterador != NULL)
    iter->finalDeIterador->siguiente = newNode;
  if(iter->inicioDeIterador == NULL) // si iter esta vacio apunto el principio a el nuevo nodo
    iter->inicioDeIterador = newNode;
  iter->finalDeIterador = newNode;
}

void reiniciarIterador(TIterador const iter) {
	if(iter->inicioDeIterador != NULL)
    iter->actualEnIterador = iter->inicioDeIterador;
}

void avanzarIterador(TIterador const iter) {
	if(estaDefinidaActual(iter))
    iter->actualEnIterador = iter->actualEnIterador->siguiente;
}

nat actualEnIterador(TIterador iter) { 
  return iter->actualEnIterador->info;
}
