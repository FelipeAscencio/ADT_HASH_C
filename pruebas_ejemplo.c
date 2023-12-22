#include "pruebas.h"
#include "src/hash.h"

#define CAPACIDAD_MAYOR 5
#define CAPACIDAD_MENOR 2
#define VACIO 0
#define NINGUNA 0
#define UN_PAR 1
#define DOS_PARES 2
#define TRES_PARES 3
#define CUATRO_PARES 4
#define VALOR_PUNTERO 0
#define VALOR_PRUEBA_1 1
#define VALOR_PRUEBA_2 2
#define VALOR_PRUEBA_3 3
#define VALOR_PRUEBA_4 4

// PRE: - .
// POST: Devuelve true si el valor en el par es no nulo, o false en caso
// contrario.
bool funcion_pruebas_iterador(const char *clave, void *valor, void *aux);

bool funcion_pruebas_iterador(const char *clave, void *valor, void *aux) {
  if (valor != NULL) {
    return true;
  }
  return false;
}

void crear_hash_capacidad_mayor() {
  size_t capacidad = CAPACIDAD_MAYOR;
  hash_t *hash_prueba = hash_crear(capacidad);
  pruebas_afirmar(hash_prueba != NULL,
                  "Hash con capacidad mayor se creo exitosamente.");
  hash_destruir(hash_prueba);
}

void crear_hash_capacidad_menor() {
  size_t capacidad = CAPACIDAD_MENOR;
  hash_t *hash_prueba = hash_crear(capacidad);
  pruebas_afirmar(hash_prueba != NULL,
                  "Hash con capacidad menor se creo exitosamente.");
  hash_destruir(hash_prueba);
}

void insertar_hash_nulo() {
  hash_t *hash_prueba = NULL;
  const char *clave_prueba = "Felipe";
  int valor_prueba = VALOR_PRUEBA_1;
  void *elemento_prueba = &valor_prueba;
  int puntero = VALOR_PUNTERO;
  void *anterior = &puntero;
  hash_prueba =
      hash_insertar(hash_prueba, clave_prueba, elemento_prueba, &anterior);
  size_t tamanio_hash = hash_cantidad(hash_prueba);
  pruebas_afirmar(tamanio_hash == VACIO,
                  "No se puede insertar en un hash nulo.");
}

void insertar_hash_clave_nula() {
  hash_t *hash_prueba = hash_crear(CAPACIDAD_MAYOR);
  const char *clave_prueba = NULL;
  int valor_prueba = VALOR_PRUEBA_1;
  void *elemento_prueba = &valor_prueba;
  int puntero = VALOR_PUNTERO;
  void *anterior = &puntero;
  hash_t *hash_insertado =
      hash_insertar(hash_prueba, clave_prueba, elemento_prueba, &anterior);
  size_t tamanio_hash = hash_cantidad(hash_insertado);
  pruebas_afirmar(tamanio_hash == VACIO,
                  "No se puede insertar una clave nula.");
  hash_destruir(hash_prueba);
}

void insertar_hash_elemento_nulo() {
  hash_t *hash_prueba = hash_crear(CAPACIDAD_MAYOR);
  const char *clave_prueba = "Felipe";
  void *elemento_prueba = NULL;
  int puntero = VALOR_PUNTERO;
  void *anterior = &puntero;
  hash_prueba =
      hash_insertar(hash_prueba, clave_prueba, elemento_prueba, &anterior);
  size_t tamanio_hash = hash_cantidad(hash_prueba);
  pruebas_afirmar(tamanio_hash == UN_PAR,
                  "Se puede insertar un elemento nulo.");
  hash_destruir(hash_prueba);
}

void inserciones_hash_todo_valido() {
  hash_t *hash_prueba = hash_crear(CAPACIDAD_MAYOR);
  const char *clave_prueba_1 = "Felipe";
  const char *clave_prueba_2 = "Santino";
  const char *clave_prueba_3 = "Ascencio";
  int valor_prueba_1 = VALOR_PRUEBA_1;
  void *elemento_prueba_1 = &valor_prueba_1;
  int valor_prueba_2 = VALOR_PRUEBA_2;
  void *elemento_prueba_2 = &valor_prueba_2;
  int valor_prueba_3 = VALOR_PRUEBA_3;
  void *elemento_prueba_3 = &valor_prueba_3;
  int puntero = VALOR_PUNTERO;
  void *anterior = &puntero;
  hash_prueba =
      hash_insertar(hash_prueba, clave_prueba_1, elemento_prueba_1, &anterior);
  hash_prueba =
      hash_insertar(hash_prueba, clave_prueba_2, elemento_prueba_2, &anterior);
  hash_prueba =
      hash_insertar(hash_prueba, clave_prueba_3, elemento_prueba_3, &anterior);
  size_t tamanio_hash = hash_cantidad(hash_prueba);
  pruebas_afirmar(tamanio_hash == TRES_PARES,
                  "Se puede insertar pares con todo valido.");
  hash_destruir(hash_prueba);
}

void inserciones_hash_que_causan_rehash() {
  hash_t *hash_prueba = hash_crear(CAPACIDAD_MENOR);
  const char *clave_prueba_1 = "Felipe";
  const char *clave_prueba_2 = "Santino";
  const char *clave_prueba_3 = "Ascencio";
  const char *clave_prueba_4 = "Fiuba";
  int valor_prueba_1 = VALOR_PRUEBA_1;
  void *elemento_prueba_1 = &valor_prueba_1;
  int valor_prueba_2 = VALOR_PRUEBA_2;
  void *elemento_prueba_2 = &valor_prueba_2;
  int valor_prueba_3 = VALOR_PRUEBA_3;
  void *elemento_prueba_3 = &valor_prueba_3;
  int valor_prueba_4 = VALOR_PRUEBA_4;
  void *elemento_prueba_4 = &valor_prueba_4;
  int puntero = VALOR_PUNTERO;
  void *anterior = &puntero;
  hash_prueba =
      hash_insertar(hash_prueba, clave_prueba_1, elemento_prueba_1, &anterior);
  hash_prueba =
      hash_insertar(hash_prueba, clave_prueba_2, elemento_prueba_2, &anterior);
  hash_prueba =
      hash_insertar(hash_prueba, clave_prueba_3, elemento_prueba_3, &anterior);
  hash_prueba =
      hash_insertar(hash_prueba, clave_prueba_4, elemento_prueba_4, &anterior);
  size_t tamanio_hash = hash_cantidad(hash_prueba);
  pruebas_afirmar(
      tamanio_hash == CUATRO_PARES,
      "Se puede insertar pares con todo valido y se hace el rehash.");
  hash_destruir(hash_prueba);
}

void actualizar_elemento_hash() {
  hash_t *hash_prueba = hash_crear(CAPACIDAD_MAYOR);
  const char *clave_prueba_1 = "Felipe";
  int valor_prueba_1 = VALOR_PRUEBA_1;
  void *elemento_prueba_1 = &valor_prueba_1;
  int valor_prueba_2 = VALOR_PRUEBA_2;
  void *elemento_prueba_2 = &valor_prueba_2;
  int puntero = VALOR_PUNTERO;
  void *anterior = &puntero;
  hash_prueba =
      hash_insertar(hash_prueba, clave_prueba_1, elemento_prueba_1, &anterior);
  hash_prueba =
      hash_insertar(hash_prueba, clave_prueba_1, elemento_prueba_2, &anterior);
  size_t tamanio_hash = hash_cantidad(hash_prueba);
  pruebas_afirmar(tamanio_hash == UN_PAR,
                  "Se actualiza el elemento con clave igual.");
  hash_destruir(hash_prueba);
}

void quitar_hash_nulo() {
  hash_t *hash_prueba = NULL;
  const char *clave_prueba = "Felipe";
  void *elemento_prueba = hash_quitar(hash_prueba, clave_prueba);
  pruebas_afirmar(elemento_prueba == NULL,
                  "No se puede borrar en un hash nulo.");
}

void quitar_clave_nula() {
  hash_t *hash_prueba = hash_crear(CAPACIDAD_MENOR);
  const char *clave_prueba = NULL;
  void *elemento_borrado = hash_quitar(hash_prueba, clave_prueba);
  pruebas_afirmar(elemento_borrado == NULL,
                  "No se puede borrar con una clave nula.");
  hash_destruir(hash_prueba);
}

void quitar_elemento_inexistente() {
  hash_t *hash_prueba = hash_crear(CAPACIDAD_MENOR);
  const char *clave_prueba_1 = "Felipe";
  void *elemento_prueba = NULL;
  int puntero = VALOR_PUNTERO;
  void *anterior = &puntero;
  hash_prueba =
      hash_insertar(hash_prueba, clave_prueba_1, elemento_prueba, &anterior);
  const char *clave_prueba_2 = "Santino";
  void *elemento_borrado = hash_quitar(hash_prueba, clave_prueba_2);
  pruebas_afirmar(elemento_borrado == NULL,
                  "No se puede borrar un par que no esta en el hash.");
  hash_destruir(hash_prueba);
}

void quitar_elemento_existente() {
  hash_t *hash_prueba = hash_crear(CAPACIDAD_MENOR);
  const char *clave_prueba = "Felipe";
  int valor_prueba = VALOR_PRUEBA_1;
  void *elemento_prueba = &valor_prueba;
  int puntero = VALOR_PUNTERO;
  void *anterior = &puntero;
  hash_prueba =
      hash_insertar(hash_prueba, clave_prueba, elemento_prueba, &anterior);
  void *elemento_borrado = hash_quitar(hash_prueba, clave_prueba);
  pruebas_afirmar(elemento_borrado != NULL,
                  "Se borra exitosamente un par existente en el hash.");
  hash_destruir(hash_prueba);
}

void quitar_elemento_dos_veces() {
  hash_t *hash_prueba = hash_crear(CAPACIDAD_MENOR);
  const char *clave_prueba = "Felipe";
  int valor_prueba = VALOR_PRUEBA_1;
  void *elemento_prueba = &valor_prueba;
  int puntero = VALOR_PUNTERO;
  void *anterior = &puntero;
  hash_prueba =
      hash_insertar(hash_prueba, clave_prueba, elemento_prueba, &anterior);
  void *elemento_borrado = hash_quitar(hash_prueba, clave_prueba);
  elemento_borrado = hash_quitar(hash_prueba, clave_prueba);
  pruebas_afirmar(elemento_borrado == NULL,
                  "No se puede borrar 2 veces un par clave/valor.");
  hash_destruir(hash_prueba);
}

void obtener_hash_nulo() {
  hash_t *hash_prueba = NULL;
  const char *clave_prueba = "Felipe";
  void *elemento_obtenido = hash_obtener(hash_prueba, clave_prueba);
  pruebas_afirmar(elemento_obtenido == NULL,
                  "No se puede obtener en un hash nulo.");
}

void obtener_clave_nula() {
  hash_t *hash_prueba = hash_crear(CAPACIDAD_MENOR);
  const char *clave_prueba = NULL;
  void *elemento_obtenido = hash_obtener(hash_prueba, clave_prueba);
  pruebas_afirmar(elemento_obtenido == NULL,
                  "No se puede obtener con una clave nula.");
  hash_destruir(hash_prueba);
}

void obtener_clave_inexistente() {
  hash_t *hash_prueba = hash_crear(CAPACIDAD_MENOR);
  const char *clave_prueba = "Felipe";
  void *elemento_obtenido = hash_obtener(hash_prueba, clave_prueba);
  pruebas_afirmar(elemento_obtenido == NULL,
                  "No se puede obtener con una clave inexistente.");
  hash_destruir(hash_prueba);
}

void obtener_clave_existente() {
  hash_t *hash_prueba = hash_crear(CAPACIDAD_MENOR);
  const char *clave_prueba = "Felipe";
  int valor_prueba = VALOR_PRUEBA_1;
  void *elemento_prueba = &valor_prueba;
  int puntero = VALOR_PUNTERO;
  void *anterior = &puntero;
  hash_prueba =
      hash_insertar(hash_prueba, clave_prueba, elemento_prueba, &anterior);
  void *elemento_obtenido = hash_obtener(hash_prueba, clave_prueba);
  pruebas_afirmar(elemento_obtenido != NULL,
                  "Se obtuvo el valor de la clave existente.");
  hash_destruir(hash_prueba);
}

void obtener_clave_eliminada() {
  hash_t *hash_prueba = hash_crear(CAPACIDAD_MENOR);
  const char *clave_prueba = "Felipe";
  int valor_prueba = VALOR_PRUEBA_1;
  void *elemento_prueba = &valor_prueba;
  int puntero = VALOR_PUNTERO;
  void *anterior = &puntero;
  hash_prueba =
      hash_insertar(hash_prueba, clave_prueba, elemento_prueba, &anterior);
  void *elemento_obtenido = hash_quitar(hash_prueba, clave_prueba);
  elemento_obtenido = hash_obtener(hash_prueba, clave_prueba);
  pruebas_afirmar(elemento_obtenido == NULL,
                  "No se puede obtener una clave eliminada.");
  hash_destruir(hash_prueba);
}

void contiene_hash_nulo() {
  hash_t *hash_prueba = NULL;
  const char *clave_prueba = "Felipe";
  bool elemento_obtenido = hash_contiene(hash_prueba, clave_prueba);
  pruebas_afirmar(elemento_obtenido == false,
                  "No se puede ver si contiene en un hash nulo.");
}

void contiene_clave_nula() {
  hash_t *hash_prueba = hash_crear(CAPACIDAD_MENOR);
  const char *clave_prueba = NULL;
  bool elemento_obtenido = hash_contiene(hash_prueba, clave_prueba);
  pruebas_afirmar(elemento_obtenido == false,
                  "No se puede ver si contiene con una clave nula.");
  hash_destruir(hash_prueba);
}

void contiene_clave_inexsistente() {
  hash_t *hash_prueba = hash_crear(CAPACIDAD_MENOR);
  const char *clave_prueba = "Felipe";
  bool elemento_obtenido = hash_contiene(hash_prueba, clave_prueba);
  pruebas_afirmar(elemento_obtenido == false,
                  "El hash no contiene un par con la clave recibida.");
  hash_destruir(hash_prueba);
}

void contiene_clave_existente() {
  hash_t *hash_prueba = hash_crear(CAPACIDAD_MENOR);
  const char *clave_prueba = "Felipe";
  int valor_prueba = VALOR_PRUEBA_1;
  void *elemento_prueba = &valor_prueba;
  int puntero = VALOR_PUNTERO;
  void *anterior = &puntero;
  hash_prueba =
      hash_insertar(hash_prueba, clave_prueba, elemento_prueba, &anterior);
  bool elemento_obtenido = hash_contiene(hash_prueba, clave_prueba);
  pruebas_afirmar(elemento_obtenido == true,
                  "El hash contiene un par con la clave recibida.");
  hash_destruir(hash_prueba);
}

void cantidad_hash_nulo() {
  hash_t *hash_prueba = NULL;
  size_t tamanio_hash = hash_cantidad(hash_prueba);
  pruebas_afirmar(tamanio_hash == VACIO,
                  "Un hash nulo no tiene pares guardados.");
}

void cantidad_hash_valido() {
  hash_t *hash_prueba = hash_crear(CAPACIDAD_MENOR);
  const char *clave_prueba = "Felipe";
  int valor_prueba = VALOR_PRUEBA_1;
  void *elemento_prueba = &valor_prueba;
  int puntero = VALOR_PUNTERO;
  void *anterior = &puntero;
  hash_prueba =
      hash_insertar(hash_prueba, clave_prueba, elemento_prueba, &anterior);
  size_t tamanio_hash = hash_cantidad(hash_prueba);
  pruebas_afirmar(tamanio_hash == UN_PAR,
                  "Se obtiene el valor correcto de pares en el hash.");
  hash_destruir(hash_prueba);
}

void iterar_hash_nulo() {
  hash_t *hash_prueba = NULL;
  void *auxiliar = NULL;
  size_t cantidad_iteraciones =
      hash_con_cada_clave(hash_prueba, funcion_pruebas_iterador, auxiliar);
  pruebas_afirmar(cantidad_iteraciones == NINGUNA,
                  "No se puede iterar en un hash nulo.");
}

void iterar_funcion_nula() {
  hash_t *hash_prueba = hash_crear(CAPACIDAD_MENOR);
  void *auxiliar = NULL;
  size_t cantidad_iteraciones =
      hash_con_cada_clave(hash_prueba, NULL, auxiliar);
  pruebas_afirmar(cantidad_iteraciones == NINGUNA,
                  "No se puede iterar con una funcion nula.");
  hash_destruir(hash_prueba);
}

void iterar_auxiliar_nulo() {
  hash_t *hash_prueba = hash_crear(CAPACIDAD_MENOR);
  const char *clave_prueba = "Felipe";
  int valor_prueba = VALOR_PRUEBA_1;
  void *elemento_prueba = &valor_prueba;
  int puntero = VALOR_PUNTERO;
  void *anterior = &puntero;
  hash_prueba =
      hash_insertar(hash_prueba, clave_prueba, elemento_prueba, &anterior);
  void *auxiliar = NULL;
  size_t cantidad_iteraciones =
      hash_con_cada_clave(hash_prueba, funcion_pruebas_iterador, auxiliar);
  pruebas_afirmar(cantidad_iteraciones != NINGUNA,
                  "Si se puede iterar con un auxiliar nulo.");
  hash_destruir(hash_prueba);
}

void iterar_hash_entero() {
  hash_t *hash_prueba = hash_crear(CAPACIDAD_MENOR);
  int puntero = VALOR_PUNTERO;
  void *anterior = &puntero;
  const char *clave_prueba_1 = "Felipe";
  int valor_prueba_1 = VALOR_PRUEBA_1;
  void *elemento_prueba_1 = &valor_prueba_1;
  hash_prueba =
      hash_insertar(hash_prueba, clave_prueba_1, elemento_prueba_1, &anterior);
  const char *clave_prueba_2 = "Santino";
  int valor_prueba_2 = VALOR_PRUEBA_2;
  void *elemento_prueba_2 = &valor_prueba_2;
  hash_prueba =
      hash_insertar(hash_prueba, clave_prueba_2, elemento_prueba_2, &anterior);
  void *auxiliar = NULL;
  size_t cantidad_iteraciones =
      hash_con_cada_clave(hash_prueba, funcion_pruebas_iterador, auxiliar);
  pruebas_afirmar(cantidad_iteraciones == DOS_PARES,
                  "Se puede iterar un hash completo.");
  hash_destruir(hash_prueba);
}

int main() {
  pruebas_nuevo_grupo(
      "\n======================== XXX ========================");
  pruebas_nuevo_grupo("\nCreación de HASH.");
  crear_hash_capacidad_mayor();
  crear_hash_capacidad_menor();
  pruebas_nuevo_grupo("\nInserción de HASH.");
  insertar_hash_nulo();
  insertar_hash_clave_nula();
  insertar_hash_elemento_nulo();
  inserciones_hash_todo_valido();
  inserciones_hash_que_causan_rehash();
  actualizar_elemento_hash();
  pruebas_nuevo_grupo("\nEliminación de HASH.");
  quitar_hash_nulo();
  quitar_clave_nula();
  quitar_elemento_inexistente();
  quitar_elemento_existente();
  quitar_elemento_dos_veces();
  pruebas_nuevo_grupo("\nObtener de HASH.");
  obtener_hash_nulo();
  obtener_clave_nula();
  obtener_clave_inexistente();
  obtener_clave_existente();
  obtener_clave_eliminada();
  pruebas_nuevo_grupo("\nVerificar existencia en el HASH.");
  contiene_hash_nulo();
  contiene_clave_nula();
  contiene_clave_inexsistente();
  contiene_clave_existente();
  pruebas_nuevo_grupo("\nTamaño de HASH.");
  cantidad_hash_nulo();
  cantidad_hash_valido();
  pruebas_nuevo_grupo("\nIteración de HASH.");
  iterar_hash_nulo();
  iterar_funcion_nula();
  iterar_auxiliar_nulo();
  iterar_hash_entero();
  pruebas_nuevo_grupo(
      "\n======================== XXX ========================");

  return pruebas_mostrar_reporte();
}