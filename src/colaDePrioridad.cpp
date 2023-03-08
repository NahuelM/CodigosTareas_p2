/* 5431590 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/colaDePrioridad.h"

typedef struct nodo *TNodo;

struct nodo {
  nat elem;
  double prioridad;
};

struct _rep_colaDePrioridad {
  nodo *Heap;
  nat *Posiciones;
  nat tope;
  nat MaxElem;
  bool minIsPrioritario;

};

TColaDePrioridad crearCP(nat N) { 
  TColaDePrioridad newCola = new _rep_colaDePrioridad;
  newCola->Heap = new nodo[N+1]; //NO se usa la posicion 0
  newCola->Posiciones = new nat[N+1];
  newCola->MaxElem = N;
  newCola->tope = 0;
  newCola->minIsPrioritario = true;
  for(nat i = 0; i <= N; i++)
    newCola->Posiciones[i] = 0;
  
  return newCola;
}

/* void ImprimirColaPrioridad(TColaDePrioridad cp)
{
  for (nat i = 1; i <= cp->tope; i++)
    printf("(%d %.2f)  ", cp->Heap[i].elem, cp->Heap[i].prioridad);

  printf("\n");

    for (nat i = 1; i <= cp->MaxElem; i++)
      if(cp->Posiciones[i]!=0)  printf("(%d %d)  ", cp->Heap[cp->Posiciones[i]].elem, cp->Posiciones[i]);
} */

static nat Min(TColaDePrioridad cp){
  nat res;
  double aux;
  //devuelve el maximo 
  aux = cp->Heap[cp->tope].prioridad;
  res = cp->Heap[cp->tope].elem;
  for (int i = cp->tope; i > 0; i--)
  {
    if(cp->Heap[i].prioridad < aux)
    {
      res = cp->Heap[i].elem;
      aux = cp->Heap[i].prioridad;
    }
  }
  return cp->Posiciones[res];
}

static nat Max(TColaDePrioridad cp){
  nat res;
  double aux;
  //devuelve el maximo 
  aux = cp->Heap[cp->tope].prioridad;
  res = cp->Heap[cp->tope].elem;
  for (int i = cp->tope; i > 0; i--)
  {
    if(cp->Heap[i].prioridad > aux)
    {
      res = cp->Heap[i].elem;
      aux = cp->Heap[i].prioridad;
    }
  }
  return cp->Posiciones[res];
}

TColaDePrioridad invertirPrioridad(TColaDePrioridad cp) { 
  if(cp != NULL)
  {
    if(cp->tope > 0)
    {
      if(cp->minIsPrioritario)
      {
        nodo *arrayAux = new nodo[cp->tope + 1];
        for (nat i = 0; i <= cp->tope; i++) //O(n)
          arrayAux[i] = cp->Heap[i];

        nat posMax = Max(cp);
        cp->Heap[1] = arrayAux[posMax];
        cp->Posiciones[cp->Heap[1].elem] = 1;
        nat aux = 2;
        for (int i = cp->tope; i >= 1; i--)
        {
          if((nat)i != posMax)
          {
            cp->Heap[aux] = arrayAux[i];
            cp->Posiciones[cp->Heap[aux].elem] = aux;
            aux++;
          }
        }
        delete[] arrayAux;
      }
      else
      {
        nodo *arrayAux = new nodo[cp->tope + 1];
        for (nat i = 0; i <= cp->tope; i++) //O(n)
          arrayAux[i] = cp->Heap[i];

        nat posMin = Min(cp);
        cp->Heap[1] = arrayAux[posMin];
        cp->Posiciones[cp->Heap[1].elem] = 1;
        nat aux = 2;
        for (int i = cp->tope; i >= 1; i--)
        {
          if((nat)i != posMin)
          {
            cp->Heap[aux] = arrayAux[i];
            cp->Posiciones[cp->Heap[aux].elem] = aux;
            aux++;
          }
        }
        delete[] arrayAux;
      }
    }
    cp->minIsPrioritario = !cp->minIsPrioritario;
  }
  return cp;
}
  
void liberarCP(TColaDePrioridad cp) {
  if(cp != NULL)
  { 
    delete[] cp->Heap;
    delete[] cp->Posiciones;
    delete cp;
  }
}

static TColaDePrioridad filtradoAscendente(TColaDePrioridad cp, nat pos){
  nodo swapAux = cp->Heap[pos];
  if(cp->minIsPrioritario)
  {
    while (pos > 1 && cp->Heap[pos].prioridad < cp->Heap[pos/2].prioridad)
    {
      cp->Posiciones[swapAux.elem] = cp->Posiciones[cp->Heap[pos/2].elem]; //posicion[swap] = posicion[padre]
      cp->Posiciones[cp->Heap[pos/2].elem] = pos; //posiciones[padre] = posiciones[swap]
      cp->Heap[pos] = cp->Heap[pos/2]; //Heap[swap] = padre
      cp->Heap[pos/2] = swapAux; // Heap[padre] = swap
      pos /= 2;
    }
  }
  else
  {
    while (pos > 1 && cp->Heap[pos].prioridad > cp->Heap[pos/2].prioridad)
    {
      cp->Posiciones[swapAux.elem] = cp->Posiciones[cp->Heap[pos/2].elem]; //posicion[swap] = posicion[padre]
      cp->Posiciones[cp->Heap[pos/2].elem] = pos; //posiciones[padre] = posiciones[swap]
      cp->Heap[pos] = cp->Heap[pos/2]; //Heap[swap] = padre
      cp->Heap[pos/2] = swapAux; // Heap[padre] = swap
      pos /= 2; //actualizar pos
    }
  }
  return cp;
}

static TColaDePrioridad filtradoDescendente(TColaDePrioridad cp, nat pos){
  nodo swapAux = cp->Heap[pos];
  if(cp->minIsPrioritario)
  {
    while ((pos*2 <= cp->tope && swapAux.prioridad > cp->Heap[pos*2].prioridad) || (pos*2+1 <= cp->tope && swapAux.prioridad > cp->Heap[pos*2+1].prioridad))
    {
      nodo hijo = cp->Heap[pos*2];
      nat posHijo = cp->Posiciones[cp->Heap[pos*2].elem];
      if(pos*2+1 <= cp->tope && cp->Heap[pos*2+1].prioridad < cp->Heap[pos*2].prioridad)
      {
        hijo = cp->Heap[pos*2+1];
        posHijo = cp->Posiciones[cp->Heap[pos*2+1].elem];
      }
      if(swapAux.prioridad > hijo.prioridad) //hago swap
      {
        cp->Posiciones[hijo.elem] = cp->Posiciones[swapAux.elem];
        cp->Posiciones[swapAux.elem] = posHijo;
        cp->Heap[pos] = cp->Heap[posHijo];
        cp->Heap[posHijo] = swapAux;      
      }
      pos = posHijo;
    }
  }
  else
  {
    while ((pos*2 <= cp->tope && swapAux.prioridad < cp->Heap[pos*2].prioridad) || (pos*2+1 <= cp->tope && swapAux.prioridad < cp->Heap[pos*2+1].prioridad))
    {
      nodo hijo = cp->Heap[pos*2];
      nat posHijo = cp->Posiciones[cp->Heap[pos*2].elem];
      if(pos*2+1 <= cp->tope && cp->Heap[pos*2+1].prioridad > cp->Heap[pos*2].prioridad)
      {
        hijo = cp->Heap[pos*2+1];
        posHijo = cp->Posiciones[cp->Heap[pos*2+1].elem];
      }
      if(swapAux.prioridad < hijo.prioridad) //hago swap
      {
        cp->Posiciones[hijo.elem] = cp->Posiciones[swapAux.elem];
        cp->Posiciones[swapAux.elem] = posHijo;
        cp->Heap[pos] = cp->Heap[posHijo];
        cp->Heap[posHijo] = swapAux;      
      }
      pos = posHijo;
    }
  }
  return cp;
}

TColaDePrioridad insertarEnCP(nat elem, double valor, TColaDePrioridad cp) {
  if(cp != NULL && elem <= cp->MaxElem && elem != 0)
  {
    if(cp->Posiciones[elem] != 0) // si ya esta actualizo prioridad
    {
      cp->Heap[cp->Posiciones[elem]].prioridad = valor;
      nat pos = cp->Posiciones[elem];
      if(pos > 1 && cp->Heap[pos/2].prioridad > valor) //padre.prioridad < elem.prioridad
        cp = filtradoAscendente(cp, pos);
      else if((pos*2 <= cp->tope && valor > cp->Heap[pos*2].prioridad) || (pos*2+1 <= cp->tope && valor > cp->Heap[pos*2+1].prioridad)) //elem.prioridad < hijoIzq.prioridad || elem.prioridad < hijoDer.prioridad
        cp = filtradoDescendente(cp, pos);
    }
    else if(cp->tope < cp->MaxElem) // inserto normal
    {
      cp->tope++;
      cp->Heap[cp->tope] = (nodo){elem, valor};
      cp->Posiciones[elem] = cp->tope;
      cp = filtradoAscendente(cp, cp->tope); // O(log N)
    }
  }
  return cp;
}

bool estaVaciaCP(TColaDePrioridad cp) { 
  if(cp == NULL)
    return true;
  else
    return cp->tope == 0;
}

nat prioritario(TColaDePrioridad cp) { 
  return cp->Heap[1].elem;
}

TColaDePrioridad eliminarPrioritario(TColaDePrioridad cp) { 
  if(cp != NULL && cp->tope > 0)
  {
    cp->Posiciones[cp->Heap[1].elem] = 0; //elimino en Posiciones la direccion del prioritario
    cp->Heap[1] = cp->Heap[cp->tope];
    cp->tope--;
    if(cp->tope > 1)
    {
      cp->Posiciones[cp->Heap[cp->tope + 1].elem] = 1;
      cp = filtradoDescendente(cp, 1); //O(log N)
    }
  }
  return cp;
}

bool estaEnCP(nat elem, TColaDePrioridad cp) { 
  if(cp == NULL || elem == 0)
    return false;
  else
    return (elem > cp->MaxElem)?false:cp->Posiciones[elem] != 0;
}

double prioridad(nat elem, TColaDePrioridad cp) { 
  return cp->Heap[cp->Posiciones[elem]].prioridad;
}
