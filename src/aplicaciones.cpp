/* 5431590 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/aplicaciones.h"
#include "../include/colCadenas.h"
#include "../include/mapping.h"

static bool esAvlAux(TAbb abb, nat& alturaHijo) {
  if(esVacioAbb(abb))
  {
    alturaHijo = 0;
    return true;
  }
  else
  {
    bool resDer = esAvlAux(derecho(abb), alturaHijo);
    nat auxAlturaDer = alturaHijo;
    if(resDer)
    {
      bool resIzq = esAvlAux(izquierdo(abb), alturaHijo);
      nat auxAlturaIzq = alturaHijo;

      alturaHijo = 1 + ((auxAlturaIzq > auxAlturaDer)?auxAlturaIzq:auxAlturaDer);
      int FE = auxAlturaIzq - auxAlturaDer;
      FE = (FE < 0)?FE*-1:FE;
      
      return resDer && resIzq && FE <= 1;
    }
    else 
      return resDer;
  }
} 

bool esAvl(TAbb abb) { 
  nat a1 = 0;
  return esAvlAux(abb, a1);
}

static nat *cantidadNodosAVL(nat h){
  nat *res = new nat[h];
  res[0] = 1;
  if(h >= 2)
  {
    res[1] = 2;
    for (nat i = 2; i < h; i++)
      res[i] = res[i-1] + res[i-2] + 1;
  }
  return res;
}

static TAbb crearAvlMin(TInfo *arrayInfos, nat *arrayAlturas, nat inf, nat h, TAbb abb){
  if(h >= 2)
  {
    TInfo infoAux = arrayInfos[arrayAlturas[h-2] + inf];
    TAbb abbDer = crearAvlMin(arrayInfos, arrayAlturas, arrayAlturas[h-2] + 1 + inf, h-2, abb);
    TAbb abbIzq = crearAvlMin(arrayInfos, arrayAlturas, 0 + inf, h-1, abb);
    return abb = consAbb(infoAux, abbIzq, abbDer);
    
  }
  else if(h==1)
  {
    TInfo infoAux = arrayInfos[inf];
    return abb = consAbb(infoAux, NULL, NULL);
  }
  else 
    return NULL;
}

TAbb avlMin(nat h) { 
  nat *arrayAlturas = cantidadNodosAVL(h); //O(h)
  TInfo *arrayInfos = new TInfo[arrayAlturas[h-1]];
  for(nat i = 0; i < arrayAlturas[h-1]; i++)
    arrayInfos[i] = crearInfo(i+1, 0);
  
  TAbb res = crearAbb();
  res = crearAvlMin(arrayInfos, arrayAlturas, 0, h, res);

  delete[] arrayInfos; 
  delete[] arrayAlturas;
  return res;
}

TCadena filtradaOrdenada(TCadena cad, TIterador it) { 
  TCadena res = crearCadena();
  if(cad != NULL)
  {
    while(estaDefinidaActual(it))
    {
      TCadena inicioCad = cad;
      double acumulador = 0;
      bool insertar = false;
      nat actulalIter = actualEnIterador(it);
      do
      {
        if(natInfo(primeroEnCadena(cad)) == actulalIter)
        {
          insertar = true;
          acumulador += realInfo(primeroEnCadena(cad));
        }
        cad = cadenaSiguiente(cad);
      }while(cad != inicioCad);

      if(insertar)
        res = insertarAlFinal(actulalIter, acumulador, res);
      avanzarIterador(it);
    }
  }
  return res;
 /*  //mapeo cad
  TCadena res = crearCadena();
  if(cad != NULL)
  {
    nat largoCad = cantidadEnCadena(cad); //O(ncad)
    TMapping map = crearMap(largoCad*25);
    for(nat i = 0;i < largoCad; i++) //O(ncad)
    {
      TInfo actualEnCad = primeroEnCadena(cad);
      if(esClaveEnMap(natInfo(actualEnCad), map))
      {
        double aux = valorEnMap(natInfo(actualEnCad), map);
        map = desasociarEnMap(natInfo(actualEnCad), map);
        map = asociarEnMap(natInfo(actualEnCad), realInfo(actualEnCad) + aux, map);
      }
      else 
        map = asociarEnMap(natInfo(actualEnCad), realInfo(actualEnCad), map);
      cad = cadenaSiguiente(cad);
    }   
    while(estaDefinidaActual(it))//O(nit)
    {
      if(esClaveEnMap(actualEnIterador(it), map))
        res = insertarAlFinal(actualEnIterador(it), valorEnMap(actualEnIterador(it), map), res);
      avanzarIterador(it);
    }
    //recorro it y veo si existe asociacion en map
    //si existe sumo el valor de real
    //en otro caso creo asociacion 
    liberarMap(map);
  }
  return res; */
}

bool estaOrdenada(TCadena cad) { 
  if(cad != NULL)
  {
    TCadena aux = cadenaSiguiente(cad);
    TCadena inicioCad = cad;
    if(aux == inicioCad)
      return true;
    bool res = true;
    while(aux != inicioCad && res)
    {
      res = natInfo(primeroEnCadena(cad)) < natInfo(primeroEnCadena(aux)); 
      cad = cadenaSiguiente(cad);
      aux = cadenaSiguiente(aux);
    }
    return res;
  }
  else 
    return true;
}

TCadena mezclaCadenas(TCadena cad1, TCadena cad2) { 
  nat largoCad1 = cantidadEnCadena(cad1);
  nat largoCad2 = cantidadEnCadena(cad2);
  TCadena cadenaRes = crearCadena();
  nat i1 = 0;
  nat i2 = 0;
  TInfo infoAux;
  if(cad1 == NULL)
  {
    cadenaRes = copiaCadena(cad2);
    return cadenaRes;
  }
  else if(cad2 == NULL)
  {
    cadenaRes = copiaCadena(cad1);
    return cadenaRes;
  }
  while(i1 != largoCad1 || i2 != largoCad2)
  {
    if(natInfo(primeroEnCadena(cad1)) <= natInfo(primeroEnCadena(cad2)) && i1 != largoCad1)
      infoAux = primeroEnCadena(cad1);
    else if(i2 != largoCad2)
      infoAux = primeroEnCadena(cad2);
    else
      infoAux = primeroEnCadena(cad1);
    cadenaRes = insertarAlFinal(natInfo(infoAux), realInfo(infoAux), cadenaRes);
    if(natInfo(primeroEnCadena(cad1)) == natInfo(primeroEnCadena(cad2)))
    {
      cad1 = cadenaSiguiente(cad1);
      cad2 = cadenaSiguiente(cad2);
      i1++;
      i2++;
    }
    else if(natInfo(infoAux) == natInfo(primeroEnCadena(cad1)))
    {
      cad1 = cadenaSiguiente(cad1);
      i1++;
    }
    else
    {
      cad2 = cadenaSiguiente(cad2);
      i2++;
    }
  }

  return cadenaRes;
}

static TAbb crearBalanceadoAux(nat inf, nat n, TInfo *arreglo, TAbb abb){
  if(n > 0)
  {
    if(n % 2 != 0)//si es inpar
    {
      TInfo infoAux = copiaInfo((arreglo[(n / 2) + inf]));
      TAbb abbDer = crearBalanceadoAux((n / 2) + 1 + inf, n / 2, arreglo, abb);
      TAbb abbIzq = crearBalanceadoAux(0 + inf, n / 2, arreglo, abb);
      abb = consAbb(infoAux, abbIzq, abbDer);

    }
    else if( n % 2 == 0) //si es par
    {
      TInfo infoAux = copiaInfo(arreglo[((n - 1) / 2) + inf]);
      TAbb abbDer = crearBalanceadoAux(((n - 1) / 2) + 1 + inf, n / 2, arreglo, abb);
      TAbb abbIzq = crearBalanceadoAux(0 + inf, (n / 2) - 1, arreglo, abb);
      abb = consAbb(infoAux, abbIzq, abbDer);
    }
    return abb;
  }
  else 
    return NULL;
}

TAbb crearBalanceado(TInfo *arreglo, nat n) { 
  TAbb abbRes = crearAbb();
  return crearBalanceadoAux(0, n, arreglo, abbRes);
}

TAbb unionAbbs(TAbb abb1, TAbb abb2) { 
  TCadena abb1Lineal = linealizacion(abb1); //O(n1)
  TCadena abb2Lineal = linealizacion(abb2); //O(n2)
  TCadena mezclaCads = mezclaCadenas(abb1Lineal, abb2Lineal); //O(n1 + n2)
  liberarCadena(abb1Lineal);
  liberarCadena(abb2Lineal);
  nat largoMezclaCad = cantidadEnCadena(mezclaCads);
  TInfo *arrayInfos =  new TInfo[largoMezclaCad];
  for (nat i = 0; i < largoMezclaCad; i++) // O(n1 + n2)
  {
    arrayInfos[i] = primeroEnCadena(mezclaCads);
    mezclaCads = cadenaSiguiente(mezclaCads);
  }

  TAbb unionAbb = crearBalanceado(arrayInfos, largoMezclaCad); //O(n1 + n2)
  liberarCadena(mezclaCads);
  delete[] arrayInfos;
  return unionAbb;
}

TCola ordenadaPorModulo(nat p, TCadena cad) { 
  TCola colRes = crearCola();
  TColCadenas colCad = crearColCadenas(p);
  nat cantCad = cantidadEnCadena(cad);
  //Recorrer cad y rellenar array[p] O(n)
  for (nat i = 0; i < cantCad; i++)
  {
    //Funcion de hash n mod(p)
    colCad = insertarEnColCadenas(natInfo(primeroEnCadena(cad)), realInfo(primeroEnCadena(cad)), natInfo(primeroEnCadena(cad)) % p, colCad);
    cad = cadenaSiguiente(cad);
  }
  //Recorrer array O(p)
  TPila pilaAux = crearPila();
  for (int i = p-1; i >= 0; i--)
  {
    if(cadenaDeColCadenas(i, colCad) != NULL)
    {
      nat largoCadActual = cantidadColCadenas(i, colCad);
      TCadena cadenaActual = cadenaDeColCadenas(i, colCad);
      for(nat j = 0; j < largoCadActual; j++)
      {
        pilaAux = apilar(primeroEnCadena(cadenaActual), pilaAux);
        cadenaActual = cadenaSiguiente(cadenaActual);
      }
    }
  }
  nat cantPila = cantidadEnPila(pilaAux);
  //O(max(n, p))
  for (nat i = 0; i < cantPila; i++)
  {
    colRes = encolar(cima(pilaAux), colRes);
    pilaAux = desapilar(pilaAux);
  }
  liberarPila(pilaAux);
  liberarColCadenas(colCad);
  return colRes;
}

TPila menoresQueElResto(TCadena cad, nat cantidad) { 
  TPila pilaRes = crearPila();
  TCadena inicioCad = cad;
  TCadena menor = cad;
  cad = cadenaSiguiente(cad);
  if(cad == inicioCad && cad != NULL)
    return apilar(primeroEnCadena(cad), pilaRes);
  //buscar el elemento minimo de cada cadena y subcadena tomando como inicio el elemnto minimo de la cadena anterior
  while(cad != inicioCad)
  {
    if(natInfo(primeroEnCadena(cad)) <= natInfo(primeroEnCadena(menor)))
      menor = cad;

    if(cadenaSiguiente(cad) == inicioCad ) // si llegue al final de la cadena
    {
      pilaRes = apilar(primeroEnCadena(menor), pilaRes);
      if( cadenaSiguiente(menor) != inicioCad)
      {
        cad = menor;
        menor = cadenaSiguiente(cad);
      }
    }
    cad = cadenaSiguiente(cad);
    //}
  }
  return pilaRes;
}

static void linealizacionAuxRecursivo(TCadena& cad, TAbb abb) {
  if(!esVacioAbb(abb))
  {
    linealizacionAuxRecursivo(cad, derecho(abb));
    cad = insertarAlInicio(natInfo(raiz(abb)), realInfo(raiz(abb)), cad);
    linealizacionAuxRecursivo(cad, izquierdo(abb));
  }
}

TCadena linealizacion(TAbb abb) { 
  TCadena AbbLineal = crearCadena();
  linealizacionAuxRecursivo(AbbLineal, abb); 
  return AbbLineal;
}

static void imprimirAbbAux(TAbb abb, nat profundidad)
{
  if(!esVacioAbb(abb))
  {    
    imprimirAbbAux(derecho(abb), profundidad + 1);

    for (nat i = 0; i < profundidad; i++)
      printf("-"); 
      
    imprimirInfo(raiz(abb));
    printf("\n");
    
    imprimirAbbAux(izquierdo(abb), profundidad + 1);
  }
}

void imprimirAbb(TAbb abb) {
  imprimirAbbAux(abb, 0);
}

bool esPerfectoAux(TAbb abb, nat& altura) {
if(esVacioAbb(abb))
{
  altura = 0;
  return true;
}
else
{
  bool resDer = esPerfectoAux(derecho(abb), altura);
  nat alturaDer = altura;
  if(resDer)
  {
    bool resIzq = esPerfectoAux(izquierdo(abb), altura);
    nat alturaIzq = altura;

    altura = 1 + ((alturaDer > alturaIzq)?alturaDer:alturaIzq);

    int FE = alturaIzq - alturaDer;
     FE = (FE < 0)?FE*-1:FE;
    return resDer && resIzq && FE == 0;
  }
  else 
    return resDer;
}

/*   if(esVacioAbb(abb))
    return true;
  else
  {
    // Si un nodo es hoja tiene que estar al mismo nivel que las demas
    if(esVacioAbb(izquierdo(abb)) && esVacioAbb(derecho(abb)))
      return (altura == nivel + 1);

    if(esVacioAbb(izquierdo(abb)) || esVacioAbb(derecho(abb)))
      return false;
      
    return esPerfectoAux(derecho(abb), altura, nivel + 1) && esPerfectoAux(izquierdo(abb), altura, nivel + 1);
  } */
}

bool esPerfecto(TAbb abb) {  
  nat altura = 0;
  return esPerfectoAux(abb, altura); 
}

TAbb menores(double limite, TAbb abb) {
  TAbb resultado = crearAbb();
  if(!esVacioAbb(abb))
  {
    TAbb izq = menores(limite, izquierdo(abb));
    TAbb der = menores(limite, derecho(abb));

    if(realInfo(raiz(abb)) < limite)
      resultado = consAbb(copiaInfo(raiz(abb)), izq, der);
    else if(esVacioAbb(izq))
      resultado = der;
    else if(esVacioAbb(der))
      resultado = izq;
    else
    {
      TInfo mayor = mayorEnAbb(izq);
      resultado = consAbb(copiaInfo(mayor), izq, der);
      resultado = removerDeAbb(natInfo(mayor), resultado);
    }
  }
  return resultado;
}

static TIterador caminoAscendenteAux(nat clave, nat &k, bool &encontrado, TAbb abb, TIterador iter){
  if(esVacioAbb(abb)) 
    return NULL;
  else
  {
    if(clave == natInfo(raiz(abb)))
      encontrado = true;
    else if(clave < natInfo(raiz(abb)))
      iter = caminoAscendenteAux(clave, k, encontrado, izquierdo(abb), iter);
    else
      iter = caminoAscendenteAux(clave, k, encontrado, derecho(abb), iter);
    
    if(encontrado && k > 0)
    {
      agregarAIterador(natInfo(raiz(abb)), iter);
      k--;
    }

    return iter;
  }
}

TIterador caminoAscendente(nat clave, nat k, TAbb abb) {
  TIterador iterador = crearIterador();
  bool encontrado = 0;
  return caminoAscendenteAux(clave, k,  encontrado, abb, iterador);
}

static void imprimirPalabrasCortasAux(ArregloChars palabra, nat k, nat index, TPalabras palabras)
{
  if (letra(palabras) != '\0') 
  {  
    if(k > 0)
    {
      palabra[index] = letra(palabras);
      imprimirPalabrasCortasAux(palabra, k - 1, index + 1, subarboles(palabras));
    }
  }
  else 
  {
    palabra[index] = '\0';
    // %s | imprime  cadena de caracteres terminada en \0
    printf("%s\n", palabra);
  }
  if (siguientes(palabras) != NULL)
    imprimirPalabrasCortasAux(palabra, k, index, siguientes(palabras));
}

void imprimirPalabrasCortas(nat k, TPalabras palabras) {
  if(subarboles(palabras) != NULL)
  {
    char palabra[k];
    imprimirPalabrasCortasAux(palabra, k, 0, subarboles(palabras));
  }
}

static TPalabras buscarLetra(char aBuscar, TPalabras palabras){
  // Si esta en la raiz del arbol
  if(letra(palabras) == aBuscar)
    return palabras;
  //Puede estar en el primer hijo o en la lista de siguiente hermano del mismo
  else  
  {
    //Busco en la lista de siguiente hermano
    TPalabras aux = subarboles(palabras);
    while(aux != NULL && letra(aux) != aBuscar)
      aux = siguientes(aux);

    return aux;
  }
}

TPalabras buscarFinPrefijo(ArregloChars prefijo, TPalabras palabras) {
  TPalabras resultado = palabras;
  nat i = 0;
  while(prefijo[i] != '\0' && resultado != NULL)
  {
    resultado = buscarLetra(prefijo[i], resultado);
    i++;
  }
  return resultado;
}

static void reversoDeIteradorAux(TIterador iter, TIterador copia) { 
  if(estaDefinidaActual(iter))
  {
    nat natAux = actualEnIterador(iter);
    avanzarIterador(iter);
    reversoDeIteradorAux(iter, copia);
    agregarAIterador(natAux, copia);
  }  
  
}

TIterador reversoDeIterador(TIterador iter) { 
  //recorro el iterador y agrego al inicio con recursividad
  TIterador newIterador = crearIterador();
  reiniciarIterador(iter);
  reversoDeIteradorAux(iter, newIterador);
  return newIterador;
}

