#pragma once

#include <stdio.h>

#define ND_LOG_SCOPE 0
#define ND_LOG_TRACE 1
#define ND_LOG_DEBUG 2
#define ND_LOG_INFO 3
#define ND_LOG_WARN 4
#define ND_LOG_ERROR 5

#define ND_LOG(LEVEL, MSG, ...) printf(MSG)
#define ND_SCOPE(MSG, ...) ND_LOG(ND_LOG_SCOPE, MSG, __VA_ARGS__)
#define ND_TRACE(MSG, ...) ND_LOG(ND_LOG_TRACE, MSG, __VA_ARGS__)
#define ND_DEBUG(MSG, ...) ND_LOG(ND_LOG_DEBUG, MSG, __VA_ARGS__)
#define ND_INFO(MSG, ...) ND_LOG(ND_LOG_INFO, MSG, __VA_ARGS__)
#define ND_WARN(MSG, ...) ND_LOG(ND_LOG_WARN, MSG, __VA_ARGS__)
#define ND_ERROR(MSG, ...) ND_LOG(ND_LOG_ERROR, MSG, __VA_ARGS__)
