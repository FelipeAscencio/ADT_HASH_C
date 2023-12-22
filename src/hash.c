#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

#define FACTOR_CARGA_MAXIMO 0.7
#define MINIMO_CAPACIDAD 3
#define MULTIPLICADOR 2
#define IGUALES 0

typedef struct par {
	char *clave;
	void *valor;
	struct par *siguiente;
} par_t;

struct hash {
	par_t **tabla;
	size_t capacidad;
	size_t cantidad;
};

//PRE: El string recibido debe ser valido.
//POST: Devuelve un numero positivo en base al string recibido.
unsigned long funcion_hash(unsigned char *str);

//PRE: El string recibido debe ser valido.
//POST: Devuelve una copia del string recibido por parámetro reservada en el heap.
char *strdup(const char *str);

//PRE: La clave recibida debe ser valida.
//POST: Devuelve, en caso de no haber error, un nuevo par clave/valor.
par_t *crear_par(const char *clave, void *elemento);

//PRE: El hash, el nuevo par y el indice recibidos deben ser validos.
//POST: Inserta el par clave/valor en la tabla hash.
hash_t *hash_insertar_par(hash_t *hash, par_t *nuevo_par, size_t indice);

//PRE: El hash recibido debe ser valido.
//POST: Devuelve, en caso de no haber errores, un nuevo hash con mas capacidad y los pares previos.
hash_t *rehash(hash_t *hash);

//PRE: El hash recibido debe ser valido.
//POST: Si el factor de carga es mayor rehashea el hash, sino no lo modifica.
hash_t *verificar_factor_carga(hash_t *hash);

unsigned long funcion_hash(unsigned char *str)
{
	unsigned long hash = 5381;
	unsigned char c = *str;
	while (c != 0) {
		hash = ((hash << 5) + hash) + c;
		c = *str++;
	}

	return hash;
}

char *strdup(const char *str)
{
	size_t len = strlen(str) + 1;
	char *dup = (char *)malloc(len);
	if (dup == NULL) {
		return NULL;
	}
	strcpy(dup, str);
	return dup;
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	if (hash == NULL) {
		return;
	}
	if (hash->tabla == NULL) {
		free(hash);
		return;
	}

	for (size_t i = 0; i < hash->capacidad; i++) {
		if (hash->tabla[i] != NULL) {
			par_t *par_actual = hash->tabla[i];
			while (par_actual != NULL) {
				par_t *par_auxiliar = par_actual;
				par_actual = par_actual->siguiente;
				if (destructor != NULL) {
					destructor(par_auxiliar->valor);
				}
				free(par_auxiliar->clave);
				free(par_auxiliar);
			}
		}
	}

	free(hash->tabla);
	free(hash);
}

void hash_destruir(hash_t *hash)
{
	hash_destruir_todo(hash, NULL);
}

par_t *crear_par(const char *clave, void *elemento)
{
	par_t *nuevo_par = calloc(1, sizeof(par_t));
	if (nuevo_par == NULL) {
		return NULL;
	}

	nuevo_par->clave = strdup(clave);
	if (nuevo_par->clave == NULL) {
		free(nuevo_par);
		return NULL;
	}

	nuevo_par->valor = elemento;
	return nuevo_par;
}

hash_t *hash_insertar_par(hash_t *hash, par_t *nuevo_par, size_t indice)
{
	nuevo_par->siguiente = hash->tabla[indice];
	hash->tabla[indice] = nuevo_par;
	hash->cantidad++;
	return hash;
}

hash_t *rehash(hash_t *hash)
{
	size_t nueva_capacidad = (hash->capacidad) * MULTIPLICADOR;
	hash_t *nuevo_hash = hash_crear(nueva_capacidad);
	if (nuevo_hash == NULL) {
		return NULL;
	}

	for (size_t i = 0; i < hash->capacidad; i++) {
		if (hash->tabla[i] != NULL) {
			par_t *par_actual = hash->tabla[i];
			while (par_actual != NULL) {
				par_t *par_auxiliar = par_actual;
				par_actual = par_actual->siguiente;
				size_t indice =
					(funcion_hash(
						(unsigned char *)
							par_auxiliar->clave)) %
					nuevo_hash->capacidad;
				hash_insertar_par(nuevo_hash, par_auxiliar,
						  indice);
			}
		}
	}

	hash_t auxiliar = *hash;
	*hash = *nuevo_hash;
	*nuevo_hash = auxiliar;
	free(nuevo_hash->tabla);
	free(nuevo_hash);
	return hash;
}

hash_t *verificar_factor_carga(hash_t *hash)
{
	float factor_carga_actual =
		(float)(hash->cantidad + 1) / (float)(hash->capacidad);
	if (factor_carga_actual >= (float)FACTOR_CARGA_MAXIMO) {
		hash = rehash(hash);
	}
	return hash;
}

hash_t *hash_crear(size_t capacidad)
{
	hash_t *hash = calloc(1, sizeof(hash_t));
	if (hash == NULL) {
		return NULL;
	}

	if (capacidad < MINIMO_CAPACIDAD) {
		capacidad = MINIMO_CAPACIDAD;
	}
	hash->capacidad = capacidad;

	hash->tabla = calloc(hash->capacidad, sizeof(par_t *));
	if (hash->tabla == NULL) {
		free(hash);
		return NULL;
	}

	return hash;
}

hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{
	if (hash == NULL) {
		return NULL;
	}
	if (clave == NULL) {
		return NULL;
	}
	if (anterior != NULL) {
		void *elemento_nulo = NULL;
		*anterior = elemento_nulo;
	}

	hash = verificar_factor_carga(hash);
	if (hash == NULL) {
		return NULL;
	}

	size_t indice =
		(funcion_hash((unsigned char *)clave)) % hash->capacidad;
	if (hash->tabla[indice] != NULL) {
		par_t *actual = hash->tabla[indice];
		while (actual != NULL) {
			if (strcmp(actual->clave, clave) == IGUALES) {
				if (anterior != NULL) {
					*anterior = actual->valor;
				}
				actual->valor = elemento;
				return hash;
			}
			actual = actual->siguiente;
		}
	}

	par_t *nuevo_par = crear_par(clave, elemento);
	if (nuevo_par == NULL) {
		return NULL;
	}
	hash = hash_insertar_par(hash, nuevo_par, indice);
	return hash;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
	if (hash == NULL) {
		return NULL;
	}
	if (clave == NULL) {
		return NULL;
	}

	size_t indice =
		(funcion_hash((unsigned char *)clave)) % hash->capacidad;
	if (hash->tabla[indice] == NULL) {
		return NULL;
	}

	par_t *actual = hash->tabla[indice];
	par_t *anterior = NULL;
	while (actual != NULL) {
		if (strcmp(actual->clave, clave) == IGUALES) {
			void *elemento = actual->valor;
			if (anterior == NULL) {
				hash->tabla[indice] = actual->siguiente;
			} else {
				anterior->siguiente = actual->siguiente;
			}
			free(actual->clave);
			free(actual);
			hash->cantidad--;
			return elemento;
		}
		anterior = actual;
		actual = actual->siguiente;
	}
	return NULL;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
	if (hash == NULL) {
		return NULL;
	}
	if (clave == NULL) {
		return NULL;
	}

	size_t indice =
		(funcion_hash((unsigned char *)clave)) % hash->capacidad;
	if (hash->tabla[indice] == NULL) {
		return NULL;
	}

	par_t *actual = hash->tabla[indice];
	while (actual != NULL) {
		if (strcmp(actual->clave, clave) == IGUALES) {
			return actual->valor;
		}
		actual = actual->siguiente;
	}

	return NULL;
}

bool hash_contiene(hash_t *hash, const char *clave)
{
	if (hash == NULL) {
		return false;
	}
	if (clave == NULL) {
		return false;
	}

	size_t indice =
		(funcion_hash((unsigned char *)clave)) % hash->capacidad;
	if (hash->tabla[indice] == NULL) {
		return false;
	}

	par_t *actual = hash->tabla[indice];
	while (actual != NULL) {
		if (strcmp(actual->clave, clave) == IGUALES) {
			return true;
		}
		actual = actual->siguiente;
	}

	return false;
}

size_t hash_cantidad(hash_t *hash)
{
	if (hash == NULL) {
		return 0;
	}

	return hash->cantidad;
}

size_t hash_con_cada_clave(hash_t *hash,
			   bool (*f)(const char *clave, void *valor, void *aux),
			   void *aux)
{
	if (hash == NULL) {
		return 0;
	}
	if (f == NULL) {
		return 0;
	}

	size_t cantidad_iteraciones = 0;

	for (size_t i = 0; i < hash->capacidad; i++) {
		if (hash->tabla[i] != NULL) {
			par_t *actual = hash->tabla[i];
			while (actual != NULL) {
				cantidad_iteraciones++;
				if (f(actual->clave, actual->valor, aux) ==
				    false) {
					return cantidad_iteraciones;
				} else {
					actual = actual->siguiente;
				}
			}
		}
	}

	return cantidad_iteraciones;
}