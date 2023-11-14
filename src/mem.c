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
nd_mem_range_arr_create(NdMemRangeArr* arr, usize capacity) {
    arr->len      = 0;
    arr->capacity = capacity > 0 ? capacity : 1;

    return nd_mem_alloc((void**)&arr->data, ND_SIZEOF(NdMemRange) * capacity);
}

NdResult
nd_mem_range_arr_destroy(NdMemRangeArr* arr) {
    arr->len      = 0;
    arr->capacity = 0;

    return nd_mem_free((void**)&arr->data);
}

NdResult
nd_mem_range_arr_get(NdMemRangeArr* arr, usize index, NdMemRange* item) {
    if (index >= arr->len) {
        return ND_ARR_INDEX_OUT_OF_LEN;
    }

    *item = arr->data[index];

    return ND_SUCCESS;
}

NdResult
nd_mem_range_arr_set(NdMemRangeArr* arr, usize index, NdMemRange item) {
    if (index >= arr->len) {
        return ND_ARR_INDEX_OUT_OF_LEN;
    }

    arr->data[index] = item;

    return ND_SUCCESS;
}

NdResult
nd_mem_range_arr_add(NdMemRangeArr* arr, usize index, NdMemRange item) {
    usize len      = arr->len;
    usize capacity = arr->capacity;

    if (len == capacity) {
        // TODO: ND_EXEC
        nd_mem_ralloc((void**)&arr->data, 2 * ND_SIZEOF(NdMemRange) * capacity);
    }

    if (index < len) {
        for (usize i = len; i > index; --i) {
            arr->data[i] = arr->data[i - 1];
        }

        arr->data[index] = item;
    } else {
        arr->data[len] = item;
    }

    arr->len += 1;

    return ND_SUCCESS;
}

NdResult
nd_mem_range_arr_remove(NdMemRangeArr* arr, usize index) {
    usize len      = arr->len;
    usize capacity = arr->capacity;

    if (len == 0) {
        return ND_ARR_EMPTY;
    }

    arr->len -= 1;

    for (usize i = index; i < len; ++i) {
        arr->data[i] = arr->data[i + 1];
    }

    if (2 * len < capacity) {
        usize capacity_ = ND_SIZEOF(NdMemRange) * capacity / 2;

        // TODO: ND_EXEC
        nd_mem_ralloc((void**)&arr->data, capacity_ > 0 ? capacity_ : 1);
    }

    return ND_SUCCESS;
}
