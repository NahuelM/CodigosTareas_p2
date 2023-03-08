/* 5431590 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/mapping.h"

typedef struct Nodo *TNodo;

struct Nodo{
  double info;
  TNodo sig;
};

struct _rep_mapping {
  TNodo *Array;
  nat Cantidad;
  nat cantMax;
};

TMapping crearMap(nat M) {
  TMapping newMapping = new _rep_mapping; 
  newMapping->Array = new TNodo[M];
  newMapping->Cantidad = 0;
  newMapping->cantMax = M;
  for(nat i = 0; i < M; i++)
    newMapping->Array[i] = NULL;

  return newMapping;
}

void liberarMap(TMapping map) {
  for (nat i = 0; i < map->cantMax; i++)
  {
    if(map->Array[i] != NULL)
      desasociarEnMap(i, map);
  }
  delete[] map->Array;
  delete map;
}

TMapping asociarEnMap(nat clave, double valor, TMapping map) { 
  //clave mod(map->cantMax) como funcion de hash
  if(map != NULL)
  {
    TNodo newNodo = new Nodo;
    newNodo->sig = NULL;
    newNodo->info = valor;
    if(map->Array[clave % map->cantMax] == NULL)
      map->Array[clave % map->cantMax] = newNodo;
    else  
    {
      //map = desasociarEnMap(clave, map);
      newNodo->sig = map->Array[clave % map->cantMax];
      map->Array[clave % map->cantMax] = newNodo;
    }
    map->Cantidad++;
  }
  return map;
}

TMapping desasociarEnMap(nat clave, TMapping map) { 
  if(map != NULL)
  {
    TNodo aux = map->Array[clave % map->cantMax];
    while(aux != NULL)
    {
      map->Array[clave % map->cantMax] = aux->sig;
      delete aux;
      aux = map->Array[clave % map->cantMax];
    }
    map->Cantidad--;
  }
  return map;
}

bool esClaveEnMap(nat clave, TMapping map) { 
  return (map != NULL)? map->Array[clave % map->cantMax] != NULL:false;
}

double valorEnMap(nat clave, TMapping map) { 
  return map->Array[clave % map->cantMax]->info;
}

bool estaLlenoMap(TMapping map) { 
  return (map != NULL)?map->cantMax == map->Cantidad:false;
}


