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
    usize bufSize;

    enum NdLogLevel level;
} NdLogConfig;

ND_ARR(NdLogConfig, LogConfig);

NdResult
ndLogInit(enum NdLogLevel level, NdArrLogConfig configs) {
    return ND_TRUE;
}

NdResult
ndLog(enum NdLogLevel level, str message, ...) {
    return ND_TRUE;
}

#define ND_SCOPE(MSG, ...) ndLog(ND_LOG_SCOPE, MSG, __VA_ARGS__)
#define ND_TRACE(MSG, ...) ndLog(ND_LOG_TRACE, MSG, __VA_ARGS__)
#define ND_DEBUG(MSG, ...) ndLog(ND_LOG_DEBUG, MSG, __VA_ARGS__)
#define ND_INFO(MSG, ...)  ndLog(ND_LOG_INFO, MSG, __VA_ARGS__)
#define ND_WARN(MSG, ...)  ndLog(ND_LOG_WARN, MSG, __VA_ARGS__)
#define ND_ERROR(MSG, ...) ndLog(ND_LOG_ERROR, MSG, __VA_ARGS__)

// #define ND_STACKTRACE
