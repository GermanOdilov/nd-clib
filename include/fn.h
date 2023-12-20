#pragma once

#include "env.h"
#include "log.h"
#include "opt.h"
#include "res.h"

#define ND_FN_NAME(NAME)      NAME
#define ND_FN_NAME_IMPL(NAME) NAME##__impl

#define ND_FN_TYPENAME(TYPE, NAME)      TYPE ND_FN_NAME(NAME)
#define ND_FN_TYPENAME_IMPL(TYPE, NAME) TYPE ND_FN_NAME_IMPL(NAME)

#define ND_FN_DECL(NAME, ARGS, TYPE) ND_FN_TYPENAME(TYPE, NAME) ARGS
#define ND_FN_DECL_VOID(NAME, ARGS)  ND_FN_TYPENAME(void, NAME) ARGS

#define ND_FN(NAME, ARGS_CALL, ARGS, TYPE, BODY)          \
    ND_FN_TYPENAME_IMPL(TYPE, NAME) ARGS {                \
        BODY;                                             \
    }                                                     \
                                                          \
    ND_FN_TYPENAME(TYPE, NAME) ARGS {                     \
        ND_SCOPE("> " ND_FN_MSG_EMPTY(NAME, ARGS, TYPE)); \
                                                          \
        TYPE val = ND_FN_NAME_IMPL(NAME) ARGS_CALL;       \
                                                          \
        ND_SCOPE("< " ND_FN_MSG_EMPTY(NAME, ARGS, TYPE)); \
                                                          \
        return val;                                       \
    }

#define ND_FN_VOID(NAME, ARGS_CALL, ARGS, BODY)           \
    ND_FN_TYPENAME_IMPL(void, NAME) ARGS {                \
        BODY;                                             \
    }                                                     \
                                                          \
    ND_FN_TYPENAME(void, NAME) ARGS {                     \
        ND_SCOPE("> " ND_FN_MSG_EMPTY(NAME, ARGS, TYPE)); \
                                                          \
        ND_FN_NAME_IMPL(NAME) ARGS_CALL;                  \
                                                          \
        ND_SCOPE("< " ND_FN_MSG_EMPTY(NAME, ARGS, TYPE)); \
    }

#define ND_FN_RES(NAME, ARGS_CALL, ARGS, TYPE_OK, TYPE_ERR, BODY) \
    ND_RES(TYPE_OK, TYPE_ERR);                                    \
                                                                  \
    ND_FN(NAME, ARGS_CALL, ARGS, ND_RES_NAME(TYPE_OK), BODY);

#define ND_FN_OPT(NAME, ARGS_CALL, ARGS, TYPE, BODY) \
    ND_OPT(TYPE);                                    \
                                                     \
    ND_FN(NAME, ARGS_CALL, ARGS, ND_OPT_NAME(TYPE), BODY);
