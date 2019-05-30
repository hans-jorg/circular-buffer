/**
 *  @file   cbuffer.c
 *
 *  @mainpage Circular Buffer
 *
 *  @brief  An implementation of a circular buffer
 *
 *  @note   The elements stored in it are defined by the ELEMENT_TYPE symbol.
 *          Default is int
 *
 *  @note   There are two implementation options. One uses indexes and
 *          other uses pointers (faster).
 *
 *  @note   The structure could be smaller. But code would be bigger and slower.
 *
 *  @author Hans
 *  @date   11/4/2019
 */

#include <stdlib.h>
#include <assert.h>

#include "cbuffer.h"

/**
 * Default is to use indexes
 */
///@{
#if !defined(CBUFFER_USEPOINTERS) && !defined(CBUFFER_USEINDEXES)
#define CBUFFER_USEINDEXES
#endif
///@}



/**
 * Main data structure
 */
struct cbuffer_s {
    ELEMENT_TYPE    *area;          /// Contiguous area to store the information
#ifdef CBUFFER_USEPOINTERS
    ELEMENT_TYPE    *front;         /// Pointer to first element
    ELEMENT_TYPE    *rear;          /// Pointer to last element
#elif defined(CBUFFER_USEINDEXES)
    int             front;          /// Index of first element
    int             rear;           /// Index of last element
#endif
    int             size;           /// Number of elements in buffer
    int             capacity;       /// Maximal number of elements in buffer
};

/**
 *  Hack!
 *  Enables use of MACRO in the then clause of an if-then-else without
 *  semicolon problem
 */
///@{

/// Begin
#define _BEGIN      do {
/// End
#define _END           } while(0)
///@}

/**
 *  @brief  Macro to adjust limits
 */
///@{
#if defined(CBUFFER_USEPOINTERS)
#define ADJUST_LIMITS(X,F) \
    _BEGIN \
        if( F->X >= F->area+F->capacity ) \
            F->X = F->area; \
    _END
#elif defined(CBUFFER_USEINDEXES)
#define ADJUST_LIMITS(X,F) \
    _BEGIN \
        if( F->X >= F->capacity ) \
            F->X = 0;\
    _END
#endif
///@}

/**
 *  @brief  creates a circular buffer of size n
 */
cbuffer
cbuffer_create(int n) {
cbuffer p;
ELEMENT_TYPE *q;

    assert(n>0);

    p = malloc(sizeof(struct cbuffer_s));
    if( !p ) return NULL;
    q = malloc(n*sizeof(ELEMENT_TYPE));
    if( !q ) {
        free(p);
        return NULL;
    }
    p->area = q;
#ifdef CBUFFER_USEPOINTERS
    p->front = p->rear = q;
#elif defined(CBUFFER_USEINDEXES)
    p->front = p->rear = 0;
#endif
    p->size = 0;
    p->capacity = n;
    return p;
}

/**
 *  @brief  destroys a circular buffer
 *
 *  @param  f: pointer to cbuffer_s structure created by cbuffer_create
 */
void
cbuffer_destroy(cbuffer f) {
    assert(f);
    free(f->area);
    f->area = NULL;
    free(f);
}

/**
 *  @brief  inserts an element in a circular
 *
 *  @param  f: pointer to cbuffer_s structure created by cbuffer_create
 *  @param  x: element to store in circular buffer
 */
int
cbuffer_insert(cbuffer f, ELEMENT_TYPE x) {

    assert(f);
    assert(f->area);

#ifdef CBUFFER_USEPOINTERS
    *(f->rear++) = x;
#elif defined(CBUFFER_USEINDEXES)
    assert(f->rear < f->capacity);
    f->area[f->rear++] = x;
#endif
    ADJUST_LIMITS(rear,f);
    if( cbuffer_full(f) ) {
        f->front++;
        ADJUST_LIMITS(front,f);
/*
#ifdef CBUFFER_USEPOINTERS
        if( f->front >= f->area+f->capacity )
            f->front = f->area;
#elif defined(CBUFFER_USEINDEXES)
        if( f->front >= f->capacity )
            f->front = 0;
#endif
*/
    } else {
        f->size++;
    }
    assert(f->size <= f->capacity);
#ifdef CBUFFER_USERPOINTERS
    assert(f->front >= f->area && f->front < f->area+f->capacity);
    assert(f->rear  >= f->area && f->rear  < f->area+f->capacity);
#elif defined(CBUFFER_USEINDEXES)
    assert(f->front<f->capacity);
    assert(f->rear <f->capacity);
#endif
    return 0;
}

/**
 *  @brief  removes an element from a circular buffer
 *
 *  @param  f: pointer to cbuffer_s structure created by cbuffer_create
 *  @param px: pointer to an area where the element will be stored
 *
 *  @return    -1 if buffer empty, 0 otherwise
 */
int
cbuffer_remove(cbuffer f, ELEMENT_TYPE *px) {

    assert(f);
    assert(f->area);

    if( cbuffer_empty(f) )
        return -1;

    f->size--;
#ifdef CBUFFER_USEPOINTERS
    *px = *(f->front++);
#elif defined(CBUFFER_USEINDEXES)
    *px = f->area[f->front++];
#endif
    ADJUST_LIMITS(front,f);
    assert(f->size <= f->capacity);
#ifdef CBUFFER_USERPOINTERS
    assert(f->front >= f->area && f->front < f->area+f->capacity);
    assert(f->rear  >= f->area && f->rear  < f->area+f->capacity);
#elif defined(CBUFFER_USEINDEXES)
    assert(f->front<f->capacity);
    assert(f->rear <f->capacity);
#endif
    return 0;
}

/**
 *  @brief  returns the capacity
 *
 *  @param  f: pointer to cbuffer_s structure created by cbuffer_create
 *
 *  @return capacity of buffer, ie, maximal number of elements in circular buffer
 *          defined by the creation
 *
 */
int cbuffer_capacity(cbuffer f) {
    return f->capacity;
}

/**
 *  @brief  returns the size, i.e., how many elements in it
 *
 *  @param  f: pointer to cbuffer_s structure created by cbuffer_create
 *
 *  @return size of buffer, ie, number of elements in circular buffer
 */
int cbuffer_size(cbuffer f) {
    return f->size;
}

/**
 *  @brief  returns true if empty
 *
 *  @param  f: pointer to cbuffer_s structure created by cbuffer_create
 *
 *  @return 1 if empty, 0 otherwise
 *
 */
int cbuffer_empty(cbuffer f) {
    return f->size == 0;
}

/**
 *  @brief  returns true if full
 *
 *  @param  f: pointer to cbuffer_s structure created by cbuffer_create
 *
 *  @return 1 if full, 0 otherwise
 */
int cbuffer_full(cbuffer f) {
    return f->size == f->capacity;
}


/**
 *  @brief  test script
 */
#ifdef TEST
#include <stdio.h>
///@{
int
main (int argc, char *argv[]) {
cbuffer f;
int i;
int rc;

    f = cbuffer_create(4);
    printf("Apos criacao\n");
    printf("Tamanho    %d\n",cbuffer_size(f));
    printf("Capacidade %d\n",cbuffer_capacity(f));
    printf("Vazio      %s\n",(cbuffer_empty(f)?"Sim":"Nao"));
    printf("Cheio      %s\n",(cbuffer_full(f)?"Sim":"Nao"));

    printf("Inserindo\n");
    for(i=0;i<10;i++) {
        rc = cbuffer_insert(f,i);
        printf("Inserindo %d => %s\n",i,(rc==0)?"OK":"Erro");
    }
    printf("Apos insercoes\n");
    printf("Tamanho    %d\n",cbuffer_size(f));
    printf("Capacidade %d\n",cbuffer_capacity(f));
    printf("Vazio      %s\n",(cbuffer_empty(f)?"Sim":"Nao"));
    printf("Cheio      %s\n",(cbuffer_full(f)?"Sim":"Nao"));

    printf("Removendo 2\n");
    rc = cbuffer_remove(f,&i);
    printf("Removendo %d => %s\n",i,(rc==0)?"OK":"Erro");
    rc = cbuffer_remove(f,&i);
    printf("Removendo %d => %s\n",i,(rc==0)?"OK":"Erro");
    printf("Apos remocoes\n");
    printf("Tamanho    %d\n",cbuffer_size(f));
    printf("Capacidade %d\n",cbuffer_capacity(f));
    printf("Vazio      %s\n",(cbuffer_empty(f)?"Sim":"Nao"));
    printf("Cheio      %s\n",(cbuffer_full(f)?"Sim":"Nao"));

    printf("Inserindo mais\n");
    for(i=10;i<20;i++) {
        rc = cbuffer_insert(f,i);
        printf("Inserindo %d => %s\n",i,(rc==0)?"OK":"Erro");
    }
    printf("Apos mais insercoes\n");
    printf("Tamanho    %d\n",cbuffer_size(f));
    printf("Capacidade %d\n",cbuffer_capacity(f));
    printf("Vazio      %s\n",(cbuffer_empty(f)?"Sim":"Nao"));
    printf("Cheio      %s\n",(cbuffer_full(f)?"Sim":"Nao"));

    printf("Removendo tudo\n");
    while( !cbuffer_empty(f) ) {
        rc = cbuffer_remove(f,&i);
        printf("Removendo %d => %s\n",i,(rc==0)?"OK":"Erro");

    }
    printf("Apos remocoes\n");
    printf("Tamanho    %d\n",cbuffer_size(f));
    printf("Capacidade %d\n",cbuffer_capacity(f));
    printf("Vazio      %s\n",(cbuffer_empty(f)?"Sim":"Nao"));
    printf("Cheio      %s\n",(cbuffer_full(f)?"Sim":"Nao"));
    cbuffer_destroy(f);
    return 0;
}
///@}
#endif

