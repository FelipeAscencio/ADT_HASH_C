<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TDA HASH

## Repositorio de Felipe Santino Ascencio - 110675 - felipesantinoascencio@gmail.com

- Para compilar y ver pruebas_alumno:

```bash
make
```

- Para ejecutar pruebas de la cátedra con valgrind:

```bash
make valgrind-chanutron
```

---

##  Funcionamiento

##  Explicación de "Implementación y diseño"

Para la implementación de mi "TABLA HASH" elegí utilizar nodos, con el par "CLAVE/VALOR" dentro del nodo y un puntero al siguiente nodo.

Utilicé una estructura "HASH" que contiene el vector dinámico para insertar los nodos, una variable con la capacidad actual de la tabla y un contador de la cantidad de nodos insertados para poder saber cuando hay que hacer "REHASH".

Las colisiones, como tenemos que hacer un "HASH ABIERTO", es decir "DIRECCINAMIENTO CERRADO", las vamos a concatenar.

Y esto lo realizamos uniendo los nodos entre si cuando colisionan en la misma posición del vector dinámico de la tabla.

##  Función HASH utilizada

La función "HASH" que utilicé en mis pruebas es "DJB2".

```c

unsigned long funcion_hash(unsigned char *str)
{
    unsigned long hash = 5381;
    unsigned char c = *str;
    while (c != 0){
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
		c = *str++;
	}

    return hash;
}

```

Lo que esta función hace es pasar el string recibido (en este caso, la clave de mi par "CLAVE/VALOR") a un numero sin signo entero, para luego hacer el resto y obtener la posición que necesito en la tabla de "HASH".

---

## Ejemplos gráficos de funciones

A continuación tenemos unos esquemas gráficos acerca de como funcionan las operaciones de insertar, quitar y rehash de nuestra tabla "HASH".

## INSERTAR

<div align="center">
<img width="70%" src="img/insertar1.png">
</div>

<div align="center">
<img width="70%" src="img/insertar2.png">
</div>

<div align="center">
<img width="70%" src="img/insertar3.png">
</div>


## QUITAR

<div align="center">
<img width="70%" src="img/quitar1.png">
</div>

<div align="center">
<img width="70%" src="img/quitar2.png">
</div>

## REHASH

<div align="center">
<img width="70%" src="img/rehash1.png">
</div>

<div align="center">
<img width="70%" src="img/rehash2.png">
</div>

---

## Testing


El "TDA" implementado está testeado de 2 maneras distintas.

Primero: Por las "pruebas_alumno" implementadas.

Segundo: Por las "pruebas_chanutron" brindadas por la cátedra.

---

## Funciones

Primero que nada es importante aclarar algo, a fin de reducir la cantidad de información en las explicaciones de abajo, respectivas a cada función, se contempla el mejor caso de ejecución de la misma.

Pero, cada función tiene todas sus validaciones respectivas para, en caso de error, finalizar su ejecución.

---

hash_crear(O(1)): Esta función crea el "HASH" con la capacidad recibida por parámetro, o capacidad igual a "3" si la recibida es menor.

La complejidad es O(1) porque: La función simplemente reserva el "HASH" e inicializa el mismo.

hash_insertar(O(1)): Esta función inserta un par "CLAVE/VALOR" en la tabla "HASH", esto lo hace aplicando la función "HASH" a la clave recibida y asignandole, en relación al resto entre el valor obtenido y la capacidad de la tabla "HASH", una posición particular.

Es importante destacar que en esta función se puede dar el caso de "REHASH", este caso se da cuando tenemos el "70%" o mas de la tabla "HASH" ocupada y necesitamos mas espacio, esta función se explica mas adelante.

La complejidad es O(1) porque: Tomamos el caso óptimo de implementación del "HASH", en donde la cantidad de pares "CLAVE/VALOR" guardados es mucho mas grande que todos los elementos que puedan llegar a concatenarse en una misma posición de la tabla, haciendo que la complejidad de esto sea O(1).

Pero si es importante recordar que, por ejemplo, si se ponen todas clave que al pasar por la función "HASH" van a parar a la misma posición de la tabla, se concatenen entre si dando lugar a una lista, y en cuyo caso esta operación pasaría de tener una complejidad de O(1) a O(n), por lo que si existe el caso donde esta función pueda ser O(n), pero consideramos que el caso óptimo que manejamos y vamos a tomar es O(1).

rehash(O(n)): Esta función lo que hace es redimensionar al doble el tamanio de la tabla de "HASH" previa para reducir el porcentaje de ocupación de la misma (FACTOR DE CARGA). Lo que hace esta función es crear una tabla de "HASH" nueva con la capacidad nueva, y va añadiendo todos los pares "CLAVE/VALOR" ya asignados en la tabla vieja a la nueva.

Pero para esto es importante marcar que vuelve a hacer la función "HASH" en las claves, para luego hacer el nuevo resto entre el valor obtenido y la nueva capacidad, y asi asegurar que se esté utilizando de manera óptima todas las nuevas posiciones disponibles de la nueva tabla de "HASH".

La complejidad es O(n) porque: Tiene que reposicionar todos los "n" pares "CLAVE/VALOR" ya asignados en la tabla vieja, a la nueva.

hash_quitar es O(1): Esta función lo que hace es buscar el par "CLAVE/VALOR" mediante a la "CLAVE" recibida por parámetro y eliminarlo de la tabla "HASH" si existe.

La complejidad es O(1) porque: Tomamos el caso óptimo de implementación del "HASH", en donde la cantidad de pares "CLAVE/VALOR" guardados es mucho mas grande que todos los elementos que puedan llegar a concatenarse en una misma posición de la tabla, haciendo que la complejidad de esto sea O(1).

Pero si es importante recordar que, por ejemplo, si se ponen todas clave que al pasar por la función "HASH" van a parar a la misma posición de la tabla, se concatenen entre si dando lugar a una lista, y en cuyo caso esta operación pasaría de tener una complejidad de O(1) a O(n), por lo que si existe el caso donde esta función pueda ser O(n), pero consideramos que el caso óptimo que manejamos y vamos a tomar es O(1).

hash_obtener es O(1): Esta función lo que hace es devolver el elemento guardado, en un respectivo par "CLAVE/VALOR", buscandólo con la clave recibida por parámetro.

La complejidad es O(1) porque: Tomamos el caso óptimo de implementación del "HASH", en donde la cantidad de pares "CLAVE/VALOR" guardados es mucho mas grande que todos los elementos que puedan llegar a concatenarse en una misma posición de la tabla, haciendo que la complejidad de esto sea O(1).

Pero si es importante recordar que, por ejemplo, si se ponen todas clave que al pasar por la función "HASH" van a parar a la misma posición de la tabla, se concatenen entre si dando lugar a una lista, y en cuyo caso esta operación pasaría de tener una complejidad de O(1) a O(n), por lo que si existe el caso donde esta función pueda ser O(n), pero consideramos que el caso óptimo que manejamos y vamos a tomar es O(1).

hash_contiene es O(1): Esta función lo que hace es devolver true si existe el par "CLAVE/VALOR" con la misma clave, a la recibida por parámetro.

La complejidad es O(1) porque: Tomamos el caso óptimo de implementación del "HASH", en donde la cantidad de pares "CLAVE/VALOR" guardados es mucho mas grande que todos los elementos que puedan llegar a concatenarse en una misma posición de la tabla, haciendo que la complejidad de esto sea O(1).

Pero si es importante recordar que, por ejemplo, si se ponen todas clave que al pasar por la función "HASH" van a parar a la misma posición de la tabla, se concatenen entre si dando lugar a una lista, y en cuyo caso esta operación pasaría de tener una complejidad de O(1) a O(n), por lo que si existe el caso donde esta función pueda ser O(n), pero consideramos que el caso óptimo que manejamos y vamos a tomar es O(1).

hash_cantidad es O(1): Esta función lo que hace es devolver la cantidad de pares "CLAVE/VALOR" que hay guardados en el "HASH".

La complejidad es O(1) porque: Simplemente devuelve la cantidad de elementos cargados, y este valor es una variable dentro de la estructura del "HASH".

hash_destuir es O(n): Esta función libera toda la memoria almacenada por el "HASH".

La complejidad es O(n) porque: Debe liberar la memoria de cada par "CLAVE/VALOR" almacenado en el "HASH" y del "HASH" mismo.

hash_destuir_todo es O(n): Esta función libera toda la memoria almacenada por el "HASH" y la memoria particular de cada "ELEMENTO" del "HASH".

La complejidad es O(n) porque: Debe liberar la memoria de cada par "CLAVE/VALOR" almacenado en el "HASH", de cada "ELEMENTO", y del "HASH" mismo.

hash_con_cada_clave es O(n): Esta función lo que hace es aplicarle una función "f" al par clave valor mandado por parámetro.

La complejidad es O(n) porque: En el peor caso le aplica la función "f" a cada par "CLAVE/VALOR" del "HASH".

---

## Respuestas a las preguntas teóricas

## ¿Qué es un diccionario? [IMAGEN 1]

Un diccionario, en el contexto de estructuras de datos y programación, se refiere a una estructura que almacena pares clave-valor, donde cada clave se asocia con un valor específico. Es una abstracción que permite la búsqueda, inserción y eliminación eficientes de elementos basados en claves.

Clave: Es un identificador único asociado a cada valor en el diccionario. La clave actúa como un índice que permite acceder rápidamente al valor correspondiente.

Valor: Es la información o dato asociado a una clave específica. Cada clave en el diccionario tiene un valor único asociado.

En términos simples, podrías pensar en un diccionario como una lista de definiciones, donde la palabra clave sería la palabra que buscas en el diccionario y el valor sería la definición correspondiente.

En nuestro caso vamos a implementarlo con una "TABLA HASH", igualmente la implementación subyacente puede variar según el lenguaje de programación, pero la idea central es proporcionar un acceso eficiente a los valores a través de las claves.

Para dar un ejemplo bien gráfico, como se ve en la "IMAGEN 1" podemos interpretar un diccionario común y corriente (en este caso de la RAE), como pares "CLAVE/VALOR".

## ¿Qué es una función de hash y qué características debe tener? [IMAGEN 2]

Una función de hash es una función matemática que toma una entrada (o 'mensaje') y produce una salida de longitud fija, que generalmente es un valor numérico (como es en nuestro caso) o una cadena de caracteres. La principal característica de una buena función de hash es que debe ser determinista, es decir, para una entrada dada, siempre debe producir la misma salida.

Las características que una función de hash debe tener dependen de su aplicación, pero en general, las funciones de hash efectivas comparten ciertas propiedades clave:

Determinismo: Como se mencionó, la función debe ser determinista, es decir, producir el mismo resultado para la misma entrada en cualquier momento.

Eficiencia: La función de hash debe ser eficiente en términos de tiempo de cálculo, especialmente porque se utiliza en operaciones como búsqueda en tablas hash. La función debe calcularse rápidamente.

Distribución uniforme: La función de hash ideal distribuirá las entradas de manera uniforme en el espacio de salida. Esto ayuda a minimizar las colisiones (casos en los que dos entradas diferentes producen el mismo valor hash).

Avalancha: Un cambio pequeño en la entrada debería provocar un cambio significativo en el valor de hash. Esto es importante para garantizar que pequeñas variaciones en la entrada no generen colisiones frecuentes.

Irreversibilidad (o preimagen resistente): Dada la salida de la función de hash, debería ser computacionalmente difícil (preferiblemente imposible) obtener la entrada original. Esto ayuda a garantizar la seguridad en contextos criptográficos.

Eficiencia en el uso de memoria: En algunas aplicaciones, especialmente en entornos con recursos limitados, es importante que la función de hash no utilice una cantidad desproporcionada de memoria.

Resistencia a colisiones: Aunque es imposible eliminar completamente las colisiones, una buena función de hash debería minimizar la probabilidad de colisiones, especialmente en aplicaciones donde las colisiones pueden tener consecuencias negativas.

Estas características son esenciales para varias aplicaciones, desde la construcción de tablas hash eficientes hasta la seguridad en algoritmos criptográficos. La elección de una función de hash adecuada depende de los requisitos específicos del contexto de uso.

En la "IMAGEN 2" tenemos un ejemplo gráfico de una función "HASH" que recibe strings, y devuelve otra clave de string con números.

En nuestro caso particular vamos a usar una función "HASH" que pasa de strings a números, pero existen varios tipos de retornos en las distintas funciones "HASH".

## ¿Qué es una tabla de Hash y los diferentes métodos de resolución de colisiones vistos? (encadenamiento, probing, zona de desborde). [IMAGEN 3]

Una tabla de hash es una estructura de datos que utiliza una función de hash para mapear claves a índices, permitiendo así un acceso rápido a los valores asociados con esas claves. La idea fundamental es calcular la función de hash para una clave dada y utilizar el resultado como índice para acceder al valor asociado en la tabla. Sin embargo, en la práctica, las colisiones pueden ocurrir cuando dos claves diferentes tienen la misma función de hash o cuando la función de hash produce el mismo índice para varias claves.

En la "IMAGEN 3" tenemos un esquema que muestra el proceso para guardar pares "CLAVE/VALOR" en una tabla "HASH".

Primero partimos de la claves, que en este caso son "Pedro Pérez / Ana Rojas / Olga Prato", con sus respectivos valores "521-1234 / 521-8976 / 521-9655".

Segundo, se aplica la función "HASH" a la clave, para luego hacer el resto con la capacidad y asignarle una posición en la tabla al par "CLAVE/VALOR", en este caso el resultado de eso nos da "02 / 01 / 14", siguiendo el orden previo.

Y una vez obtenido la posición, simplemente se inserta en el lugar correspondiente el par "CLAVE/VALOR".

Recordemos que por nuestra implementación, en caso de colisión lo que pasará es que se concatenarán las claves que nos den un resultado igual al aplicar la función "HASH".

Existen diferentes métodos para abordar las colisiones en una tabla de hash, y aquí se describen los vistos:

Encadenamiento (Chaining) - Este es el método que nosotros utilizamos para nuestra implementación:

Descripción: En este método, cada celda de la tabla de hash contiene una lista (o una estructura similar, como un árbol) de elementos que tienen la misma función de hash. Cuando ocurre una colisión, el nuevo elemento se agrega a la lista asociada con esa posición.

Ventajas: Fácil de implementar y eficiente en el uso de memoria.

Desventajas: Puede haber un ligero aumento en el tiempo de acceso debido a la necesidad de recorrer la lista en caso de colisión.

Sondeo Lineal (Linear Probing):

Descripción: Cuando se produce una colisión, se busca la siguiente celda disponible en la tabla de hash (en sentido lineal) hasta encontrar una posición libre.

Ventajas: Buena eficiencia de memoria, ya que no se necesita almacenar estructuras adicionales como en el encadenamiento.

Desventajas: Puede haber agrupamiento primario, lo que significa que las colisiones tienden a agruparse en ciertas áreas de la tabla.

Zona de Desborde (Overflow Area):

Descripción: Se reserva un área adicional de almacenamiento para manejar las colisiones. Si una celda está ocupada, el elemento se coloca en la zona de desbordamiento.

Ventajas: Puede ser útil cuando se desea mantener la tabla principal relativamente pequeña.

Desventajas: El acceso a elementos en la zona de desbordamiento puede ser menos eficiente.

---

## IMAGEN 1

<div align="center">
<img width="70%" src="img/diccionario.jpg">
</div>

## IMAGEN 2

<div align="center">
<img width="70%" src="img/funcion_hash.png">
</div>

## IMAGEN 3

<div align="center">
<img width="70%" src="img/tabla_hash.png">
</div>

---