#pragma once

#include "arr.h"
#include "types.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ND_MALLOC(s)     nd_malloc(s, ND_FILE, ND_FN, ND_LINE)
#define ND_CALLOC(s, n)  nd_calloc(s, n, ND_FILE, ND_FN, ND_LINE)
#define ND_REALLOC(p, s) nd_realloc(p, s, ND_FILE, ND_FN, ND_LINE)
#define ND_FREE(p)       nd_free(p, ND_FILE, ND_FN, ND_LINE)

static inline void*
nd_malloc(usize size, const str file, const str fn, const u64 line) {
    void* ptr = malloc(size);

    if (!ptr) {
        fprintf(stderr, "nd_malloc error: %s - %s::%s: %lu\n", strerror(errno), file, fn, line);

        return NULL;
    }

    return ptr;
}

static inline void*
nd_calloc(usize size, usize num, const str file, const str fn, const u64 line) {
    void* ptr = calloc(size, num);

    if (!ptr) {
        fprintf(stderr, "nd_calloc error: %s - %s::%s: %lu\n", strerror(errno), file, fn, line);

        return NULL;
    }

    return ptr;
}

static inline void*
nd_realloc(void* ptr, usize size, const str file, const str fn, const u64 line) {
    void* ptr_ = realloc(ptr, size);

    if (!ptr_) {
        fprintf(stderr, "nd_realloc error: %s - %s::%s: %lu\n", strerror(errno), file, fn, line);

        return NULL;
    }

    return ptr_;
}

static inline void
nd_free(void* ptr, const str file, const str fn, const u64 line) {
    if (!ptr) {
        fprintf(stderr, "nd_free error: ptr is null - %s::%s: %lu\n", file, fn, line);

        return;
    }

    free(ptr);
}

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
