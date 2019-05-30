Circular Buffer
===============

A simple implementation of a circular buffer.
It comes with unit test.

Default element is int. To change it, define the CBUFFER_ELEMENTTYPE during
compilation. For example, ```-DCBUFFER_ELEMENTTYPE=float```

The are two implementations. One uses indexes and other uses pointers (faster).
To choose one, define the symbol ```CBUFFER_USEINDEXES``` ou ```CBUFFER_USEPOINTERS``` during compilation. Default is to use pointers.

It is a simple implementation. It uses a size parameter to determine if the buffer is empty or full. There are implementations, that uses a clever system of rear and front values to set this, but they are longer and complicated. 


#Usage
```
#include "cbuffer.h"

int main() {
cbuffer cb;

    // Creates a circular buffer for 10 elements
    cb = cb_create(10);

    while(1) {
        x = getvalue();
        cb_insert(cb,x);

        if( cond ) {
            if( !cb_empty(cb) )
                cb_remove(cb,&x);
        }

    }

    ...
}
```         
