NAME = nd

VER_MAJOR = 0
VER_MINOR = 1
VER_PATCH = 0

CC = gcc
AR = ar

SRC = src
SRCS = $(wildcard $(SRC)/*.c)

BIN = bin/release
BIN_DEBUG = bin/debug

OBJ_STATIC = $(BIN)/obj/static
OBJS_STATIC = $(SRCS:$(SRC)/%.c=$(OBJ_STATIC)/%.o)

OBJ_STATIC_DEBUG = $(BIN_DEBUG)/obj/static
OBJS_STATIC_DEBUG = $(SRCS:$(SRC)/%.c=$(OBJ_STATIC_DEBUG)/%.o)

OBJ_SHARED = $(BIN)/obj/shared
OBJS_SHARED = $(SRCS:$(SRC)/%.c=$(OBJ_SHARED)/%.o)

OBJ_SHARED_DEBUG = $(BIN_DEBUG)/obj/shared
OBJS_SHARED_DEBUG = $(SRCS:$(SRC)/%.c=$(OBJ_SHARED_DEBUG)/%.o)

LIB_STATIC = $(BIN)/lib$(NAME).a
LIB_SHARED = $(BIN)/lib$(NAME).so
LIB_STATIC_DEBUG = $(BIN_DEBUG)/lib$(NAME).a
LIB_SHARED_DEBUG = $(BIN_DEBUG)/lib$(NAME).so

INCS = -Iinclude
LIBS = -pthread
FLAGS = -std=c17 -O3 -Wall -save-temps -DND_IS_RELEASE
FLAGS_DEBUG = -std=c17 -Og -g3 -Wall -save-temps -DND_IS_DEBUG

.PHONY: all release debug check clean install uninstall info

all: release debug

release: $(OBJS_STATIC) $(OBJS_SHARED)
	mkdir -p $(BIN)
	$(AR) rcs $(LIB_STATIC) $(OBJS_STATIC)
	$(CC) -shared -o $(LIB_SHARED) $(OBJS_SHARED)

debug: $(OBJS_STATIC_DEBUG) $(OBJS_SHARED_DEBUG)
	mkdir -p $(BIN_DEBUG)
	$(AR) rcs $(LIB_STATIC_DEBUG) $(OBJS_STATIC_DEBUG)
	$(CC) -shared -o $(LIB_SHARED_DEBUG) $(OBJS_SHARED_DEBUG)

clean:
	rm -rf $(BIN) $(BIN_DEBUG)
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
