#pragma once

#include "env.h"
#include "log.h"

#define ND_SCOPE_MSG(TYPE, NAME, ARGS) ND_FILE "::" ND_STR(NAME) ":" ND_STRD(ND_LINE) ": " ND_STR(ARGS) " -> " ND_STR(TYPE)

#define ND_FN_NAME(NAME)      NAME
#define ND_FN_NAME_IMPL(NAME) NAME##__impl

#define ND_FN_TYPENAME(TYPE, NAME)      TYPE ND_FN_NAME(NAME)
#define ND_FN_TYPENAME_IMPL(TYPE, NAME) TYPE ND_FN_NAME_IMPL(NAME)

#define ND_FN_DECL(NAME, ARGS, TYPE) ND_FN_TYPENAME(TYPE, NAME) ARGS
#define ND_FN_DECL_VOID(NAME, ARGS)  ND_FN_TYPENAME(void, NAME) ARGS

#define ND_FN(NAME, ARGS_CALL, ARGS, TYPE, BODY)       \
    ND_FN_TYPENAME_IMPL(TYPE, NAME) ARGS {             \
        BODY;                                          \
    }                                                  \
                                                       \
    ND_FN_TYPENAME(TYPE, NAME) ARGS {                  \
        ND_SCOPE("> " ND_SCOPE_MSG(TYPE, NAME, ARGS)); \
                                                       \
        TYPE val = ND_FN_NAME_IMPL(NAME) ARGS_CALL;    \
                                                       \
        ND_SCOPE("< " ND_SCOPE_MSG(TYPE, NAME, ARGS)); \
                                                       \
        return val;                                    \
    }

#define ND_FN_VOID(NAME, ARGS_CALL, ARGS, BODY)        \
    ND_FN_TYPENAME_IMPL(void, NAME) ARGS {             \
        BODY;                                          \
    }                                                  \
                                                       \
    ND_FN_TYPENAME(void, NAME) ARGS {                  \
        ND_SCOPE("> " ND_SCOPE_MSG(TYPE, NAME, ARGS)); \
                                                       \
        ND_FN_NAME_IMPL(NAME) ARGS_CALL;               \
                                                       \
        ND_SCOPE("< " ND_SCOPE_MSG(TYPE, NAME, ARGS)); \
    }
