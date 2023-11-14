#pragma once

#include "types.h"

#include <math.h>
#include <stdlib.h>

#define ND_ARR(TYPE)               \
    typedef struct Nd##NAME##Arr { \
        usize len;                 \
        usize capacity;            \
        TYPE* data;                \
    } TYPE##Arr;

#define ND_ARR_DECL(TYPE, NAME)
#define ND_ARR_DEF(TYPE, NAME)

typedef struct NdMemRange {
    usize start;
    usize end;
} NdMemRange;

ND_ARR(NdMemRange);

typedef struct NdMemSpan {
    NdMemRangeArr allocArr;
    usize         size;
    void*         ptr;
} NdMemSpan;

typedef struct NdMemSpanBlocks {
    NdMemRangeArr allocArr;
    usize         len;
    usize         size;
    usize         capacity;
    void*         ptr;
} NdMemASpanBlocks;

typedef struct NdMemStack {
    usize size;
    void* ptr;
    void* top;
} NdMemStack;

NdResult
nd_mem_alloc(void** ptr, usize size);

NdResult
nd_mem_nalloc(void** ptr, usize size, usize num);

NdResult
nd_mem_ralloc(void** ptr, usize size);

NdResult
nd_mem_free(void** ptr);

NdResult
nd_mem_range_arr_create(NdMemRangeArr* arr, usize capacity);

NdResult
nd_mem_range_arr_destroy(NdMemRangeArr* arr);

NdResult
nd_mem_range_arr_get(NdMemRangeArr* arr, usize index, NdMemRange* item);

NdResult
nd_mem_range_arr_set(NdMemRangeArr* arr, usize index, NdMemRange item);

NdResult
nd_mem_range_arr_add(NdMemRangeArr* arr, usize index, NdMemRange item);

NdResult
nd_mem_range_arr_remove(NdMemRangeArr* arr, usize index);

NdResult
nd_mem_span_create();

NdResult
nd_mem_span_destroy();

NdResult
nd_mem_span_alloc();

NdResult
nd_mem_span_free();
