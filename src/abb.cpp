/* 5431590 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/abb.h"

struct _rep_abb {
  TInfo info;
  TAbb izquierdo;
  TAbb derecho;
};

static void rotacionR(TAbb& abb) {
  if(abb != NULL)
  {
    TAbb izq = abb->izquierdo;
    if(izq != NULL)
    {
      abb->izquierdo = izq->derecho;
      izq->derecho = abb;
      abb = izq;
    }
  }
}

static void rotacionL(TAbb& abb) {
  if(abb != NULL)
  {
    TAbb der = abb->derecho;
    if(der != NULL)
    {
      abb->derecho = der->izquierdo;
      der->izquierdo = abb;
      abb = der;
    }
  }
}

TAbb rotar(nat clave, char tipo[2], TAbb abb) { 
  if(abb != NULL)
  {
    if(clave == natInfo(raiz(abb)))
    {
      if(tipo[0] == 'L')
      {
        if(abb->izquierdo != NULL)
        {
          if(tipo[1] == 'L')//rotacion LL
            rotacionR(abb);
          else //rotacion LR
          {
            if(abb->izquierdo->derecho != NULL)
            {
              rotacionL(abb->izquierdo);
              rotacionR(abb);
            }
          }
        }
      }
      else
      {
        if(abb->derecho != NULL)
        {
          if(tipo[1] == 'R')//Rotacion RR
            rotacionL(abb);
          else // Rotacion RL
          {
            if(abb->derecho->izquierdo != NULL)
            {
              rotacionR(abb->derecho);
              rotacionL(abb);
            }
          }
        }
      }
    }
    else
    {
      char *tipoaux = tipo;
      if(clave < natInfo(raiz(abb)))
        abb->izquierdo = rotar(clave, tipoaux, abb->izquierdo);
      else
        abb->derecho = rotar(clave, tipoaux, abb->derecho);
    }
  }
  return abb;
}

TAbb crearAbb() {   
	TAbb newTAbb = NULL;
  return newTAbb; 
}

void liberarAbb(TAbb abb) {
	if(abb != NULL)
  {
    liberarAbb(abb->izquierdo);
    liberarAbb(abb->derecho);
    liberarInfo(abb->info);
    delete abb;
  }
}

bool esVacioAbb(TAbb abb) { 
  return abb == NULL;
}

TAbb buscarSubarbol(nat clave, TAbb abb) { 
  TAbb res = NULL; 
  if(abb != NULL)
  {
    if(clave == natInfo(raiz(abb)))
      res = abb;
    else
    {
      if(clave < natInfo(raiz(abb)))
        res = buscarSubarbol(clave, abb->izquierdo);
      else
        res = buscarSubarbol(clave, abb->derecho);
    }
  }
  return res;
 }

TInfo raiz(TAbb abb) { 
  return abb->info;
}

TAbb izquierdo(TAbb abb) { 
  return abb->izquierdo;
}

TAbb derecho(TAbb abb) { 
  return abb->derecho; 
}

TInfo menorEnAbb(TAbb abb) {   
	//me muevo al elemento mas a la izquierda
  while(abb->izquierdo != NULL)
    abb = abb->izquierdo;
  return abb->info; 
}

TInfo mayorEnAbb(TAbb abb) { 
	//me muevon al elemento mas a a la derecha
  while(abb->derecho != NULL)
    abb = abb->derecho;
  return abb->info;
}

TAbb consAbb(TInfo dato, TAbb izq, TAbb der) { 
	TAbb newNodo = new _rep_abb;
  newNodo->info = dato;
  newNodo->derecho = der;
  newNodo->izquierdo = izq;
  return newNodo; 
}

TAbb insertarEnAbb(TInfo dato, TAbb abb) { 
	if(abb == NULL)
  {     
    TAbb newAbb = new _rep_abb;
    newAbb->derecho = NULL;
    newAbb->izquierdo = NULL;
    newAbb->info = dato;
    abb = newAbb;
  }
  else
  {
    nat claveDeNodo = natInfo(raiz(abb));
    if(natInfo(dato) < claveDeNodo)
      abb->izquierdo = insertarEnAbb(dato, abb->izquierdo);
    else if(natInfo(dato) > claveDeNodo)
      abb->derecho = insertarEnAbb(dato, abb->derecho);
  }
  return abb; 
}

TAbb removerDeAbb(nat clave, TAbb abb) { 
	if(abb != NULL)
  {
    if(clave == natInfo(abb->info))
    {
      if(abb->derecho == NULL)
      {
        TAbb aux = abb;
        abb = abb->izquierdo;
        liberarInfo(aux->info);
        delete aux;
      }
      else if(abb->izquierdo == NULL)
      {
        TAbb aux = abb;
        abb = abb->derecho;
        liberarInfo(aux->info);
        delete aux;
      }
      else
      {
        TInfo mayorDeIzq = mayorEnAbb(abb->izquierdo);
        liberarInfo(abb->info);
        abb->info = copiaInfo(mayorDeIzq);
        abb->izquierdo = removerDeAbb(natInfo(mayorDeIzq), abb->izquierdo); // va a caer en el caso abb->der == NULL
      }
    }
    else if(clave < natInfo(abb->info))
      abb->izquierdo = removerDeAbb(clave, abb->izquierdo);
    else
      abb->derecho = removerDeAbb(clave, abb->derecho);
  }
  return abb; 
}

TAbb copiaAbb(TAbb abb) { 
	if(abb == NULL)
    return NULL;
  else
  {
    TAbb newNodo = new _rep_abb;
    newNodo->info = copiaInfo(abb->info);
    newNodo->izquierdo = copiaAbb(abb->izquierdo);
    newNodo->derecho = copiaAbb(abb->derecho);

    return newNodo;
  }
}
