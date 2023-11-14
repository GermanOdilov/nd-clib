#pragma once

#include "types.h"

#define ND_ARR(TYPE, NAME)       \
    typedef struct NdArr##NAME { \
        TYPE* data;              \
        usize size;              \
        usize capacity;          \
    } NdArr##NAME;

typedef struct NdMemSpan {
} NdMemSpan;

typedef struct NdMemStack {
} NdMemStack;

typedef struct NdMemPtrArr {
} NdMemPtrArr;

NdResult
ndMalloc(usize size, void** ptr);

NdResult
ndCalloc(usize size, usize num, void** ptr);

NdResult
ndRealloc(usize size, void** ptr);

NdResult
ndFree(void** ptr);
