# ADT HASH

- To compile and run the tests in your own console:

```bash
bash .tests/test.sh
```

---

## Functioning

##  Explanation of "Implementation and design"

First of all, this was a project for the university, so the code is written in spanish.

With that clarified, we move on to the explanation.

For the implementación of the dictionary, i used a open "HASH TABLE" (closed addressing).

For my "HASH TABLE" implementation I chose to use nodes, with the "KEY/VALUE" pair inside the node and a pointer to the next node.

I used a "HASH" structure that contains the dynamic vector to insert the nodes, a variable with the current capacity of the table and a counter of the number of nodes inserted to know when to do "REHASH".

The collisions, since we have to do an "OPEN HASH TABLE", that is, "CLOSED ADDRESSING", we are going to concatenate them.

And we do this by joining the nodes together when they collide in the same position of the dynamic vector of the table.

##  HASH function used

The "HASH" function I used in my tests is "DJB2".

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

What this function does is pass the received string (in this case, the key of my "KEY/VALUE" pair) to an unsigned integer number, and then do the rest and obtain the position I need in the "HASH TABLE".

---

## Testing

For test the code, i implemented my own tests.

In the repository actions you can see the status of the executed tests.

Also add the analysis with valgrind to see if you have memory leaks, since the program uses dynamic memory.

---

## Functions

First of all, it is important to clarify something, in order to reduce the amount of information in the explanations below, corresponding to each function, the best case of its execution is contemplated.

But, each function has all its respective validations to, in case of error, terminate its execution.

The pre and post conditions of each function are specified in the corresponding ".h" file.

### Computational complexity

I am going to make a list of the computational complexities in "BIG O" notation of each implemented function.

- hash_crear = O(1).

- hash_insertar = O(1).

- rehash = O(n).

- hash_quitar = O(1).

- hash_obtener = O(1).

- hash_contiene = O(1).

- hash_cantidad = O(1).

- hash_destruir = O(n).

- hash_destruir_todo = O(n).

- hash_con_cada_clave = O(n).

For the "hash_insertar", "hash_eliminar", "hash_buscar" and "hash_contiene" functions:

We take the optimal case of "HASH" implementation, where the number of "KEY/VALUE" pairs saved is much larger than all the elements that can be concatenated in the same position of the table, making the complexity of this be O(1).

But it is important to remember that, for example, if all keys are entered that when passed through the "HASH" function end up in the same position in the table, they are concatenated together giving rise to a list, and in which case this operation would go from having a complexity of O(1) to O(n), so if there is a case where this function could be O(n), but we consider that the optimal case that we handle and are going to take is O(1 ).

---