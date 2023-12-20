NAME = nd

VER_MAJOR = 0
VER_MINOR = 1
VER_PATCH = 0
VER = $(VER_MAJOR).$(VER_MINOR).$(VER_PATCH)

AR = ar
CC = gcc
CC_COMPILEDB = clang

SRC = src
SRCS = $(wildcard $(SRC)/*.c)

BIN = bin/release
BIN_DEBUG = bin/debug
BIN_COMPILEDB = bin/compiledb

OBJ_STATIC = $(BIN)/obj/static
OBJS_STATIC = $(SRCS:$(SRC)/%.c=$(OBJ_STATIC)/%.o)

OBJ_STATIC_DEBUG = $(BIN_DEBUG)/obj/static
OBJS_STATIC_DEBUG = $(SRCS:$(SRC)/%.c=$(OBJ_STATIC_DEBUG)/%.o)

OBJ_SHARED = $(BIN)/obj/shared
OBJS_SHARED = $(SRCS:$(SRC)/%.c=$(OBJ_SHARED)/%.o)

OBJ_SHARED_DEBUG = $(BIN_DEBUG)/obj/shared
OBJS_SHARED_DEBUG = $(SRCS:$(SRC)/%.c=$(OBJ_SHARED_DEBUG)/%.o)

OBJ_COMPILEDB = $(BIN_COMPILEDB)/obj
OBJS_COMPILEDB = $(SRCS:$(SRC)/%.c=$(OBJ_COMPILEDB)/%.o)

LIB_NAME = lib$(NAME)
LIB_STATIC = $(BIN)/$(LIB_NAME)
LIB_SHARED = $(BIN)/$(LIB_NAME)
LIB_STATIC_DEBUG = $(BIN_DEBUG)/$(LIB_NAME)
LIB_SHARED_DEBUG = $(BIN_DEBUG)/$(LIB_NAME)

INCS = -Iinclude
LIBS = -pthread
FLAGS = -std=c17 -O3 -Wall -save-temps -DND_IS_RELEASE
FLAGS_DEBUG = -std=c17 -Og -g3 -Wall -save-temps -DND_IS_DEBUG
FLAGS_COMPILEDB = -std=c17 -O3 -Wall -DND_IS_RELEASE

.PHONY: all release release-static release-shared debug debug-static debug-shared check clean install uninstall info

all: release debug

release: release-static release-shared
debug: debug-static debug-shared

release-static: $(OBJS_STATIC)
	$(AR) rcs $(LIB_STATIC).$(VER).a $(OBJS_STATIC)
	ln -s $(LIB_NAME).$(VER).a $(LIB_STATIC).a

release-shared: $(OBJS_SHARED)
	$(CC) -shared -o $(LIB_SHARED).$(VER).so $(OBJS_SHARED)
	ln -s $(LIB_NAME).$(VER).so $(LIB_SHARED).so

debug-static: $(OBJS_STATIC_DEBUG)
	$(AR) rcs $(LIB_STATIC_DEBUG).$(VER).a $(OBJS_STATIC_DEBUG)
	ln -s $(LIB_NAME).$(VER).a $(LIB_STATIC_DEBUG).a

debug-shared: $(OBJS_SHARED_DEBUG)
	$(CC) -shared -o $(LIB_SHARED_DEBUG).$(VER).so $(OBJS_SHARED_DEBUG)
	ln -s $(LIB_NAME).$(VER).so $(LIB_SHARED_DEBUG).so

compiledb: $(OBJS_COMPILEDB)
	rm -rf $(BIN_COMPILEDB)

clean:
	rm -rf $(BIN) $(BIN_DEBUG) $(BIN_COMPILEDB)
check:
install:
uninstall:
info:

$(OBJ_STATIC)/%.o: $(SRC)/%.c
	mkdir -p $(OBJ_STATIC)
	$(CC) $(INCS) $(LIBS) $(FLAGS) -c $< -o $@

$(OBJ_SHARED)/%.o: $(SRC)/%.c
	mkdir -p $(OBJ_SHARED)
	$(CC) -fPIC $(INCS) $(LIBS) $(FLAGS) -c $< -o $@

$(OBJ_STATIC_DEBUG)/%.o: $(SRC)/%.c
	mkdir -p $(OBJ_STATIC_DEBUG)
	$(CC) $(INCS) $(LIBS) $(FLAGS_DEBUG) -c $< -o $@

$(OBJ_SHARED_DEBUG)/%.o: $(SRC)/%.c
	mkdir -p $(OBJ_SHARED_DEBUG)
	$(CC) -fPIC $(INCS) $(LIBS) $(FLAGS_DEBUG) -c $< -o $@

$(OBJ_COMPILEDB)/%.o: $(SRC)/%.c
	mkdir -p $(OBJ_COMPILEDB)
	$(CC_COMPILEDB) $(INCS) $(LIBS) $(FLAGS_COMPILEDB) -c $< -o $@
