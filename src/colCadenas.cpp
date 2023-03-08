/* 5431590 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/colCadenas.h"

struct _rep_colCadenas {
  TCadena *Cadenas;
  nat tamanio;
};

TColCadenas crearColCadenas(nat tamanio) {  
  TColCadenas newColCadenas = new _rep_colCadenas;
  newColCadenas->Cadenas = new TCadena[tamanio];
  newColCadenas->tamanio = tamanio;
  for (nat i = 0; i < tamanio; i++)
    newColCadenas->Cadenas[i] = crearCadena();
  
  return newColCadenas;
}

void liberarColCadenas(TColCadenas col) {
  nat tamanio = tamanioColCadenas(col);
  for(nat i = 0; i < tamanio; i++)
    liberarCadena(col->Cadenas[i]);

  delete[] col->Cadenas;
  delete col;
}

nat tamanioColCadenas(TColCadenas col) {  
  //lo que ocupa todo el array / lo que ocupa un elemento del mismo (memoria)
  return (col->Cadenas != NULL)? col->tamanio:0;
}

TCadena cadenaDeColCadenas(nat pos, TColCadenas col) { 
  return col->Cadenas[pos];
}

nat cantidadColCadenas(nat pos, TColCadenas col) { 
  return cantidadEnCadena(col->Cadenas[pos]);
}

bool estaEnColCadenas(nat natural, nat pos, TColCadenas col) { 
  return estaEnCadena(natural, col->Cadenas[pos]); 
}

TColCadenas insertarEnColCadenas(nat natural, double real, nat pos, TColCadenas col) {
  col->Cadenas[pos] = insertarAlInicio(natural, real, col->Cadenas[pos]);
  return col;
}

TInfo infoEnColCadenas(nat natural, nat pos, TColCadenas col) { 
  return infoCadena(natural, col->Cadenas[pos]);
}

TColCadenas removerDeColCadenas(nat natural, nat pos, TColCadenas col) {
  col->Cadenas[pos] = removerDeCadena(natural, col->Cadenas[pos]);
  return col;
}
