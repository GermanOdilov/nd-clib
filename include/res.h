#pragma once

typedef enum NdResult {
    ND_OK,
    ND_ERR,
} NdOption;

#define ND_RES_NAME(TYPE) TYPE##Res
#define ND_RES(TYPE_OK, TYPE_ERR)         \
    typedef struct ND_RES_NAME(TYPE_OK) { \
        union {                           \
            TYPE_OK  ok;                  \
            TYPE_ERR err;                 \
        } val;                            \
        NdResult res;                     \
    } ND_RES_NAME(TYPE_OK)
