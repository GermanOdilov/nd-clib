#pragma once

#include "env.h"
#include "log.h"
#include "types.h"

#define ND_RES_EXEC(X)                                               \
    {                                                                \
        NdResult res = X;                                            \
                                                                     \
        if (res != ND_SUCCESS) {                                     \
            ND_WARN(ND_FILE_MSG("NdResult != ND_SUCCESS: %d"), res); \
                                                                     \
            return res;                                              \
        }                                                            \
    }

#define ND_RES_EXEC_TERM(X)                                           \
    {                                                                 \
        NdResult res = X;                                             \
                                                                      \
        if (res != ND_SUCCESS) {                                      \
            ND_ERROR(ND_FILE_MSG("NdResult != ND_SUCCESS: $d"), res); \
                                                                      \
            exit(EXIT_FAILURE);                                       \
        }                                                             \
    }
