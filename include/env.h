#pragma once

#include <stdint.h>

#define ND_FILE __FILE__
#define ND_LINE __LINE__
#define ND_FUNC __func__

#define ND_SELF(X) X
#define ND_STR(X)  #X
#define ND_STRD(X) ND_STR(X)

#define ND_PREPROC_ERR(MSG) ND_FILE ":" ND_STRD(ND_LINE) ": " MSG

#if INTPTR_MAX == INT32_MAX
    #define ND_ARCH_BIT_X32
#elif INTPTR_MAX == INT64_MAX
    #define ND_ARCH_BIT_X64
#else
    #error ND_PREPROC_ERR("Unknown architecture bitness. Supported: x32, x64")
#endif

#if defined(__GNUC__)
    #define ND_GCC
#elif defined(__clang__)
    #define ND_CLANG
#elif defined(_MSC_VER)
    #define ND_MSVC
#else
    #error ND_PREPROC_ERR("Unknown compiler. Supported: GCC, Clang, MSVC")
#endif

#if defined(__unix__)
    #define ND_OS_UNIX
#endif

#if defined(__linux__)
    #define ND_OS_LINUX
#endif

#if defined(__APPLE__)
    #define ND_OS_MAC
#endif

#if defined(__ANDROID__)
    #define ND_OS_ANDROID
#endif

#if defined(_WIN32)
    #define ND_OS_WINDOWS
#endif

#if !defined(ND_OS_UNIX) && !defined(ND_OS_LINUX) && !defined(ND_OS_MAC) && !defined(ND_OS_ANDROID) && !defined(ND_OS_WINDOWS)
    #error ND_PREPROC_ERR("Unknown OS. Supported: Unix, Linux, Mac, Android, Windows")
#endif

#define ND_INLINE        inline
#define ND_INLINE_FORCED inline
