#ifndef CBUFFER_H
#define CBUFFER_H
/**
 *  @file   cbuffer.h
 *
 *  @author Hans
 *  @date   11/4/2019
 */

#ifndef ELEMENT_TYPE
#define ELEMENT_TYPE int
#endif


typedef struct cbuffer_s *cbuffer;

cbuffer cbuffer_create(int n);
void cbuffer_destroy(cbuffer f);
int cbuffer_insert(cbuffer f, ELEMENT_TYPE x);
int cbuffer_remove(cbuffer f, ELEMENT_TYPE *px);

int cbuffer_capacity(cbuffer f);
int cbuffer_size(cbuffer f);
int cbuffer_empty(cbuffer f);
int cbuffer_full(cbuffer f);

#endif

