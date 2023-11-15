#pragma once

#include "res.h"
#include "types.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef enum NdMemCpyDir {
    ND_MEM_COPY_FORWARD,
    ND_MEM_COPY_REVERSE,
} NdMemCpyDir;

#define ND_ARR(TYPE)               \
    typedef struct Nd##NAME##Arr { \
        usize cap;                 \
        usize len;                 \
        TYPE* ptr;                 \
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
    usize         size;
    usize         len;
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
nd_mem_cpy(const void* src, void* dst, usize size);

NdResult
nd_mem_cpy_blocks(const void* src, void* dst, usize len, usize size, NdMemCpyDir dir);

NdResult
nd_mem_cpy_blocks_fwd(const void* src, void* dst, usize len, usize size);

NdResult
nd_mem_cpy_blocks_rev(const void* src, void* dst, usize len, usize size);

NdResult
nd_mem_range_arr_create(NdMemRangeArr* arr, usize cap);

NdResult
nd_mem_range_arr_destroy(NdMemRangeArr* arr);

NdResult
nd_mem_range_arr_get(const NdMemRangeArr* arr, usize index, NdMemRange* item);

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
