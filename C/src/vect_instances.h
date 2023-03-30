// This header can be included anywhere.

#ifndef VECT_INST_H
#define VECT_INST_H

#include <stdlib.h>

typedef double KeyType;
typedef size_t ItemType;

typedef struct
{
	KeyType key;
	ItemType item;
} __attribute__ ((packed, aligned(4))) PQnode;


// Exposing the 3 vector instanciations API to each file including this public header:

#undef T
#define T uint8_t
// #define T_EQUALITY(a, b) ((a) == (b))
#include "Vectors.h"

#undef T
#define T uint32_t
// #define T_EQUALITY(a, b) ((a) == (b))
#include "Vectors.h"

#undef T
#define T PQnode
// #define T_EQUALITY(a, b) ((a).key == (b).key && (a).item == (b).item)
#include "Vectors.h"

#endif // VECT_INST_H
