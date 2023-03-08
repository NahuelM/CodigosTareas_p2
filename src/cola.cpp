/* 5431590 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/cola.h"

struct Nodo{
	TInfo info;
	Nodo *siguiente;
};

struct _rep_cola {
	nat cantidadCola;
	Nodo *inicio, *final;
};

TCola crearCola() { 
	TCola newCola = new _rep_cola;
	newCola->inicio = newCola->final = NULL;
	newCola->cantidadCola = 0;
	return newCola;
}

void liberarCola(TCola c) {
  nat cantEnCola = cantidadEnCola(c);
  Nodo *aux;
	for(nat i = 0; i < cantEnCola; i++)
	{
		liberarInfo(frente(c));
    aux = c->inicio;
		c->inicio = c->inicio->siguiente;
		delete aux;
	}
	delete c;
}

nat cantidadEnCola(TCola c) { 
  return (c != NULL)? c->cantidadCola:0; 
}

TCola encolar(TInfo info, TCola c) {
	Nodo *newNodo = new Nodo;
	newNodo->info = copiaInfo(info);
	newNodo->siguiente = NULL;
  if(c->final != NULL)
	  c->final->siguiente = newNodo;
  else
    c->inicio = newNodo;
	c->final = newNodo;
	c->cantidadCola++;
	return c;
}

TInfo frente(TCola c) {	
  return c->inicio->info; 
}

TCola desencolar(TCola c) { 
	Nodo *aux = c->inicio;
	c->inicio = c->inicio->siguiente;
	liberarInfo(aux->info);
	delete aux;
	c->cantidadCola--;
  if(c->cantidadCola == 0)
    c->inicio = c->final = NULL;
	return c;
}
