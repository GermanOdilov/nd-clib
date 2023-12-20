#pragma once

#include "arr.h"
#include "types.h"

typedef enum NdLogLevel: u8 {
    ND_LOG_SCOPE,
    ND_LOG_TRACE,
    ND_LOG_DEBUG,
    ND_LOG_INFO,
    ND_LOG_WARN,
    ND_LOG_ERROR,
} NdLogLevel;

typedef struct NdLogConfig {
} NdLogConfig;

ND_ARR(NdLogConfig);

void
nd_log_init(NdLogConfigArr configs);

void
nd_log(NdLogLevel level, str message, ...);

inline void
nd_scope(str message, ...) {}

inline void
nd_trace(str message, ...) {}

inline void
nd_debug(str message, ...) {}

inline void
nd_info(str message, ...) {}

inline void
nd_warn(str message, ...) {}

inline void
nd_error(str message, ...) {}

#define ND_LOG(LEVEL, MSG, ...)
#define ND_SCOPE(MSG, ...) ND_LOG(ND_LOG_SCOPE, MSG, __VA_ARGS__)
#define ND_TRACE(MSG, ...) ND_LOG(ND_LOG_TRACE, MSG, __VA_ARGS__)
#define ND_DEBUG(MSG, ...) ND_LOG(ND_LOG_DEBUG, MSG, __VA_ARGS__)
#define ND_INFO(MSG, ...)  ND_LOG(ND_LOG_INFO, MSG, __VA_ARGS__)
#define ND_WARN(MSG, ...)  ND_LOG(ND_LOG_WARN, MSG, __VA_ARGS__)
#define ND_ERROR(MSG, ...) ND_LOG(ND_LOG_ERROR, MSG, __VA_ARGS__)

// #define ND_STACKTRACE
