#pragma once

#include "env.h"
#include "log.h"

#define ND_INLINE inline
#define ND_INLINE_FORCED inline

#define ND_SCOPE_MSG(TYPE, NAME, ARGS) ND_FILE "::" ND_STR(NAME) ":" ND_STRD(ND_LINE) ": " ND_STR(ARGS) " -> " ND_STR(TYPE)

#define ND_FN_NAME_(NAME) __##NAME##__
#define ND_FN_DECL_(TYPE, NAME) ND_INLINE_FORCED TYPE ND_FN_NAME_(NAME)
#define ND_FN_DECL(TYPE, NAME) TYPE NAME

#define ND_FN(NAME, ARGS, TYPE, CALL, BODY)             \
  ND_FN_DECL_(TYPE, NAME)                               \
  ARGS{BODY} ND_FN_DECL(TYPE, NAME) ARGS {              \
    ND_SCOPE(">" ND_SCOPE_MSG(TYPE, NAME, ARGS), ARGS); \
                                                        \
    TYPE val = ND_FN_NAME_(NAME) CALL;                  \
                                                        \
    ND_SCOPE("<" ND_SCOPE_MSG(TYPE, NAME, ARGS), ARGS); \
                                                        \
    return val;                                         \
  }

#define ND_FN_VOID(NAME, ARGS, CALL, BODY)              \
  ND_FN_DECL_(void, NAME)                               \
  ARGS{BODY} ND_FN_DECL(void, NAME) ARGS {              \
    ND_SCOPE(">" ND_SCOPE_MSG(TYPE, NAME, ARGS), ARGS); \
                                                        \
    ND_FN_NAME_(NAME)                                   \
    CALL;                                               \
                                                        \
    ND_SCOPE("<" ND_SCOPE_MSG(TYPE, NAME, ARGS), ARGS); \
  }
