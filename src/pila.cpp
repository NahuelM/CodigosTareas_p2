/* 5431590 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/pila.h"

struct Nodo{
  TInfo info;
  Nodo *siguiente;
};

struct _rep_pila {
  nat cadntidadPila;
  Nodo *Cima;
};

TPila crearPila() {
  TPila newPila = new _rep_pila;
  newPila->Cima = NULL;
  newPila->cadntidadPila = 0;
  return newPila;
}

void liberarPila(TPila p) {
  Nodo *aux;
  for(nat i = 0; i < cantidadEnPila(p); i++)
  {
    aux = p->Cima;
    liberarInfo(aux->info);
    p->Cima = p->Cima->siguiente;
    delete aux;
  }
  delete p;
}

nat cantidadEnPila(TPila p) { 
  return (p != NULL)? p->cadntidadPila:0;
}

TPila apilar(TInfo info, TPila p) {
  Nodo *newNodo = new Nodo;
  newNodo->info = copiaInfo(info);
  newNodo->siguiente = p->Cima;
  p->Cima = newNodo;
  p->cadntidadPila++;
  return p;
}

TInfo cima(TPila p) { 
  return p->Cima->info;
}

TPila desapilar(TPila p) {
  Nodo *aux = p->Cima;
  p->Cima = p->Cima->siguiente;
  liberarInfo(aux->info);
  delete aux;
  p->cadntidadPila--;
  return p;
}
