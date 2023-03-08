/* 5431590 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/cadena.h"

struct _rep_cadena {
  TInfo info;
  TCadena siguiente;
  TCadena anterior;
};

TCadena crearCadena() {
	TCadena newCadena = NULL;
  return newCadena;
}

void liberarCadena(TCadena cad) {
	if(cad != NULL)
  {
    TCadena posAux = cad->siguiente;
    while (posAux != cad)
    {
      liberarInfo(posAux->info);
      posAux = posAux->siguiente;
      delete posAux->anterior;
    }
    liberarInfo(cad->info);
    delete cad;
  }
}

nat cantidadEnCadena(TCadena cad) {
	nat contador = 0;
  if(cad != NULL)    
  {
    TCadena posAux = cad->siguiente; //para recorrer la cadena
    contador++;
    while(posAux != cad)
    {
      contador++;
      posAux = posAux->siguiente;
    }
  }
  return contador;
}

bool estaEnCadena(nat natural, TCadena cad) {
	bool esta = false;
  if(cad != NULL)
  {
    TCadena posAux = cad->siguiente;
    esta = natInfo(cad->info) == natural;
    while(posAux != cad && !esta)
    {
      esta = natInfo(posAux->info) == natural;
      posAux = posAux->siguiente;
    }

  }
  return esta;
}

TCadena insertarAlInicio(nat natural, double real, TCadena cad) {
  TCadena newNodo = new _rep_cadena;
  newNodo->info = crearInfo(natural, real);
  if(cad == NULL)// si la cadena es vacia
  {
    cad = newNodo;
    newNodo->siguiente = newNodo;
    newNodo->anterior = newNodo;
  }
  else // si la cadena tiene uno o mas elementos
  {
    newNodo->siguiente = cad;
    newNodo->anterior = cad->anterior;
    cad->anterior = newNodo;
    newNodo->anterior->siguiente = newNodo;
    cad = newNodo;
  }
  return cad;
}

TInfo infoCadena(nat natural, TCadena cad) {
	TCadena posAux = cad;
  bool encontrado = natInfo(cad->info) == natural;
  while (!encontrado)// uso precondicion de que natural esta en la cadena
  {
    posAux = posAux->siguiente;
    encontrado = natInfo(posAux->info) == natural;
  }
  return posAux->info;
}

TInfo primeroEnCadena(TCadena cad) { 
  return cad->info;
}

TCadena cadenaSiguiente(TCadena cad) {
	TCadena cadSig = cad;
  if(cad != NULL)
    cadSig = cadSig->siguiente;
  return cadSig;
}

TCadena removerDeCadena(nat natural, TCadena cad) {
	TCadena posAux = cad;
  bool encontrado = natInfo(posAux->info) == natural;
  while (!encontrado) // uso precondicion de que natural esta en la cadena
  {
    posAux = posAux->siguiente;
    encontrado = natInfo(posAux->info) == natural;
  }
  liberarInfo(posAux->info);
  if(cad->siguiente == cad) //si la cadena tiene un solo elemento
  {
    delete cad;
    return NULL;
  }
  //Cuando encuentro el nodo con el elemento
  posAux->anterior->siguiente = posAux->siguiente;
  posAux->siguiente->anterior = posAux->anterior;

  if(posAux == cad)
    cad = cad->siguiente;

  delete posAux;   
  return cad;
}

void imprimirCadena(TCadena cad) {
	if(cad != NULL)
  {
    nat largodeCad = cantidadEnCadena(cad);
    for(nat i = 0; i < largodeCad; i++)
    {
      imprimirInfo(cad->info);
      cad = cad->siguiente;
    }
  }
  printf("\n");
}

TCadena insertarAlFinal(nat natural, double real, TCadena cad) { 
  cad = insertarAlInicio(natural, real, cad);
  cad = cadenaSiguiente(cad);
  return cad;
}

TCadena removerPrimero(TCadena cad) { 
  TCadena auxBorrar = cad;
  liberarInfo(auxBorrar->info);
  if(cad->siguiente == cad) //si la cadena tiene un solo elemento
  {
    delete cad;
    return NULL;
  }
  auxBorrar->anterior->siguiente = auxBorrar->siguiente;
  auxBorrar->siguiente->anterior = auxBorrar->anterior;

  if(auxBorrar == cad)
    cad = cad->siguiente;

  delete auxBorrar; 
  return cad;
}

TCadena copiaCadena(TCadena cad) { 
  TCadena newCopia = crearCadena();
  nat largoDeCad = cantidadEnCadena(cad);
  if(largoDeCad > 0)
  {
    TInfo infoAux;
    TCadena siguiente = cad;
    for (nat i = 0; i < largoDeCad; i++)
    {
      infoAux = primeroEnCadena(siguiente);
      //en insertarAlFinal se llama a insertarAlInicio y ahi
      //se crea memoria fresca para TInfo
      newCopia = insertarAlFinal(natInfo(infoAux), realInfo(infoAux), newCopia);
      siguiente = cadenaSiguiente(siguiente); 
    }

  }
  return newCopia;
}
