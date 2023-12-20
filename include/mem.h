#pragma once

#include "arr.h"
#include "types.h"

#include <string.h>

typedef struct NdMemRange {
    usize start;
    usize end;
} NdMemRange;

ND_ARR(NdMemRange);

typedef struct NdMemSpan {
    NdMemRangeArr allocs;
    usize         size;
    void*         ptr;
} NdMemSpan;

typedef struct NdMemSpanBlocks {
    NdMemRangeArr allocs;
    usize         size;
    usize         len;
    void*         ptr;
} NdMemASpanBlocks;

typedef struct NdMemStack {
    usize size;
    void* ptr;
    void* top;
} NdMemStack;
