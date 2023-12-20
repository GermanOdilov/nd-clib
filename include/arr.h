#pragma once

#define ND_ARR_NAME(TYPE) TYPE##Arr
#define ND_ARR(TYPE)                   \
    typedef struct ND_ARR_NAME(TYPE) { \
        usize cap;                     \
        usize len;                     \
        TYPE* ptr;                     \
    } ND_ARR_NAME(TYPE);

#define ND_ARR_DEF(TYPE)
