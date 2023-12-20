#pragma once

typedef enum NdOption {
    ND_SOME,
    ND_NONE,
} NdOption;

#define ND_OPT_NAME(TYPE) TYPE##Opt
#define ND_OPT(TYPE)                   \
    typedef struct ND_OPT_NAME(TYPE) { \
        TYPE     val;                  \
        NdOption opt;                  \
    } ND_OPT_NAME(TYPE)
