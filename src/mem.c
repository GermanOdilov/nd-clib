#include "mem.h"

NdResult
nd_mem_alloc(void** ptr, usize size) {
    if (size == 0) {
        *ptr = NULL;

        return ND_MEM_ZERO_ALLOC;
    }

    *ptr = malloc(size);

    return *ptr != NULL ? ND_SUCCESS : ND_FAILURE;
}

NdResult
nd_mem_nalloc(void** ptr, usize size, usize num) {
    if (size == 0 || num == 0) {
        *ptr = NULL;

        return ND_MEM_ZERO_ALLOC;
    }

    *ptr = calloc(num, size);

    return *ptr != NULL ? ND_SUCCESS : ND_FAILURE;
}

NdResult
nd_mem_ralloc(void** ptr, usize size) {
    if (size == 0) {
        free(*ptr);

        *ptr = NULL;

        return ND_MEM_ZERO_ALLOC;
    }

    *ptr = realloc(*ptr, size);

    return *ptr != NULL ? ND_SUCCESS : ND_FAILURE;
}

NdResult
nd_mem_free(void** ptr) {
    free(*ptr);

    *ptr = NULL;

    return ND_SUCCESS;
}

NdResult
nd_mem_cpy(const void* restrict src, void* restrict dst, usize size) {
    memcpy(dst, src, size);

    return ND_SUCCESS;
}

NdResult
nd_mem_cpy_blocks(const void* src, void* dst, usize len, usize size, NdMemCpyDir dir) {
    return dir == ND_MEM_COPY_FORWARD ? nd_mem_cpy_blocks_fwd(src, dst, len, size)
         : dir == ND_MEM_COPY_REVERSE ? nd_mem_cpy_blocks_rev(src, dst, len, size)
                                      : ND_UNKNOWN_OP;
}

NdResult
nd_mem_cpy_blocks_fwd(const void* src, void* dst, usize len, usize size) {
    for (usize i = 0; i < len; ++i) {
        ND_RES_EXEC(nd_mem_cpy(src + i * size, dst + i * size, size));
    }

    return ND_SUCCESS;
}

NdResult
nd_mem_cpy_blocks_rev(const void* src, void* dst, usize len, usize size) {
    for (usize i = len - 1; i >= 0; --i) {
        ND_RES_EXEC(nd_mem_cpy(src + i * size, dst + i * size, size));
    }

    return ND_SUCCESS;
}

NdResult
nd_mem_range_arr_create(NdMemRangeArr* arr, usize cap) {
    arr->cap = cap > 0 ? cap : 1;
    arr->len = 0;

    return nd_mem_alloc((void**)&arr->ptr, ND_SIZEOF(NdMemRange) * cap);
}

NdResult
nd_mem_range_arr_destroy(NdMemRangeArr* arr) {
    arr->cap = 0;
    arr->len = 0;

    return nd_mem_free((void**)&arr->ptr);
}

NdResult
nd_mem_range_arr_get(const NdMemRangeArr* arr, usize index, NdMemRange* item) {
    if (index >= arr->len) {
        return ND_ARR_INDEX_OUT_OF_LEN;
    }

    *item = arr->ptr[index];

    return ND_SUCCESS;
}

NdResult
nd_mem_range_arr_set(NdMemRangeArr* arr, usize index, NdMemRange item) {
    if (index >= arr->len) {
        return ND_ARR_INDEX_OUT_OF_LEN;
    }

    arr->ptr[index] = item;

    return ND_SUCCESS;
}

NdResult
nd_mem_range_arr_add(NdMemRangeArr* arr, usize index, NdMemRange item) {
    if (arr->len == arr->cap) {
        ND_RES_EXEC(nd_mem_ralloc((void**)&arr->ptr, 2 * ND_SIZEOF(NdMemRange) * arr->cap));

        arr->cap = 2 * ND_SIZEOF(NdMemRange) * arr->cap;
    }

    if (index < arr->len) {
        nd_mem_cpy_blocks_rev(arr->ptr + index, arr->ptr + index + 1, arr->len - index, ND_SIZEOF(NdMemRangeArr));

        arr->ptr[index] = item;
    } else {
        arr->ptr[arr->len] = item;
    }

    arr->len += 1;

    return ND_SUCCESS;
}

NdResult
nd_mem_range_arr_remove(NdMemRangeArr* arr, usize index) {
    if (arr->len == 0) {
        return ND_ARR_EMPTY;
    }

    arr->len -= 1;

    nd_mem_cpy_blocks_fwd(arr->ptr + index + 1, arr->ptr + index, arr->len - index, ND_SIZEOF(NdMemRangeArr));

    if (2 * arr->len < arr->cap) {
        usize cap_    = ND_SIZEOF(NdMemRange) * arr->cap / 2;
        usize cap_res = cap_ > 0 ? cap_ : 1;

        ND_RES_EXEC(nd_mem_ralloc((void**)&arr->ptr, cap_res));

        arr->cap = cap_res;
    }

    return ND_SUCCESS;
}
