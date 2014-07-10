//
//  vector.h
//  Copyright (c) 2014 Grant Neubauer
//  Name: Grant Neubauer
//  Number: 1411339
//  Email: grantn2@uw.edu
//

#ifndef ex5_vector_h
#define ex5_vector_h

// An arbitrary pointer to represent an element in the vector.
typedef void* element_t;

// An expandable array of element_ts.
typedef struct vector_t {
    size_t length;
    element_t *arry;
} *vector_t;


// On success, return vector_t with an initial length of n.
// On failure, returns NULL.  Assumes v != NULL.
vector_t VectorCreate(size_t n);

// Frees the memory allocated for the vector_t.  Assumes v != NULL.
void VectorFree(vector_t v);

// Sets the nth element of v to be e.
// Returns the previous nth element_t in prev.
// Freeing e is the responsibility of the user, not the vector_t.
// Returns true if successful.  Assumes v != NULL.
bool VectorSet(vector_t v, uint32_t index, element_t e, element_t *prev);

// Returns the element at the given index within v.  Assumes v != NULL.
element_t VectorGet(vector_t v, uint32_t index);

// Returns the length of v.  Assumes v != NULL.
size_t VectorLength(vector_t v);


#endif
