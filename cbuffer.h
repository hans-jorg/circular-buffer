#ifndef CBUFFER_H
#define CBUFFER_H
/**
 *  @file   cbuffer.h
 *  @note   Interface to the cbuffer.c routines
 *
 *  @author Hans
 *  @date   11/10/2019
 */

/**
 *  Default element is int
 */
#ifndef CBUFFER_ELEMENTTYPE
#define CBUFFER_ELEMENTTYPE int
#endif

/**
 *  Default is the use of pointers
 */
#if !defined(CBUFFER_USEINTEGERS) && !defined(CBUFFER_USEPOINTERS)
#define CBUFFER_USEPOINTERS
#endif

typedef struct cbuffer_s {

#if defined(CBUFFER_USEINTEGERS)
    int                     front;
    int                     rear;
#elif defined(CBUFFER_USEPOINTERS)
    CBUFFER_ELEMENTTYPE    *front;
    CBUFFER_ELEMENTTYPE    *rear;
#endif
    int                     size;
    int                     capacity;
    CBUFFER_ELEMENTTYPE     area[1]; // place holder
} *cbuffer;

cbuffer cbuffer_create(int n);
void cbuffer_destroy(cbuffer f);
int cbuffer_insert(cbuffer f, CBUFFER_ELEMENTTYPE x);
int cbuffer_remove(cbuffer f, CBUFFER_ELEMENTTYPE *px);

static inline int cbuffer_capacity(cbuffer f) {
    return f->capacity;
}

static inline int cbuffer_size(cbuffer f) {
    return f->size;
}

static inline int cbuffer_empty(cbuffer f) {
    return f->size == 0;
}

static inline int cbuffer_full(cbuffer f) {
    return f->size == f->capacity;
}
#endif

