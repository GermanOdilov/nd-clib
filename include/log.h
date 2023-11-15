#pragma once

#include "env.h"
#include "mem.h"
#include "types.h"

#include <stdio.h>
#include <time.h>
#include <vulkan/vulkan.h>

typedef enum NdLogLevel: u8 {
    ND_LOG_SCOPE,
    ND_LOG_TRACE,
    ND_LOG_DEBUG,
    ND_LOG_INFO,
    ND_LOG_WARN,
    ND_LOG_ERROR,
} NdLogLevel;

typedef struct NdLogConfig {
    FILE* file;
    usize size;

    NdLogLevel level;
} NdLogConfig;

ND_ARR(NdLogConfig);

NdResult
nd_log_init(enum NdLogLevel level, NdLogConfigArr configArr);

NdResult
nd_log(enum NdLogLevel level, str message, ...);

// TODO: Make ND_LOG with optional variadic

#define ND_SCOPE(MSG, ...) nd_log(ND_LOG_SCOPE, MSG, __VA_ARGS__)
#define ND_TRACE(MSG, ...) nd_log(ND_LOG_TRACE, MSG, __VA_ARGS__)
#define ND_DEBUG(MSG, ...) nd_log(ND_LOG_DEBUG, MSG, __VA_ARGS__)
#define ND_INFO(MSG, ...)  nd_log(ND_LOG_INFO, MSG, __VA_ARGS__)
#define ND_WARN(MSG, ...)  nd_log(ND_LOG_WARN, MSG, __VA_ARGS__)
#define ND_ERROR(MSG, ...) nd_log(ND_LOG_ERROR, MSG, __VA_ARGS__)

// #define ND_STACKTRACE
