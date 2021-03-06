CC = gcc
LD = ld
C_FLAGS = -Wall -pthread -g

BUILD_DIR = build
SRC_DIR = src
TEST_SRC_DIR = test

LIB_NAME = cunittest

SRCS = $(shell find ${SRC_DIR} -name *.c)
OBJS = $(addprefix ${BUILD_DIR}/, $(SRCS:%.c=%.o))

TEST_SRCS = $(shell find ${TEST_SRC_DIR} -name *.c)
TEST_OUTPUTS = $(addprefix ${BUILD_DIR}/, $(TEST_SRCS:%.c=%.out))

SUB_DIRS = $(shell find ${SRC_DIR} -type d)
SUB_DIRS += test
BUILD_SUB_DIRS = $(addprefix ${BUILD_DIR}/,${SUB_DIRS})

INCLUDE_DIRS_PRIV = $(addprefix -I , $(shell find ${SRC_DIR} -type d))
INCLUDE_DIR_PUB = -I include

DOXYGEN_BIN_PATH := $(shell command -v doxygen 2> /dev/null)

.PHONY: build_directories all clean cleanall static_lib

# Default recipe
all: tests

# lib is a synonym for static lib
lib: static_lib

# Build a dynamic lib
dyn_lib:
	@echo "TBA"

# Static build
static_lib: build_directories ${OBJS}
	ar rcs lib${LIB_NAME}.a ${OBJS}

# Strip the produced libraries of debug symbols
stripped: static_lib dyn_lib
ifneq ("$(wildcard lib${LIB_NAME}.a)","")
	strip -g lib${LIB_NAME}.a
endif
ifneq ("$(wildcard lib${LIB_NAME}.so)","")
	strip -g lib${LIB_NAME}.so
endif

tests: build_directories ${TEST_OUTPUTS}
	@echo "TBA: automatically execute tests"

# Sub directories under build dir
build_directories: ${BUILD_SUB_DIRS}

# Cleaning
cleanall: clean

clean:
	rm -rf build/*
	rm -f lib${LIB_NAME}.a
	# This does not exist yet but included for future additions
	rm -f lib${LIB_NAME}.so

doc: doxygen

doxygen:
ifndef DOXYGEN_BIN_PATH
	$(error "Doxygen not present in the machine. Install doxygen")
endif
	# Force work dir to project root dir
	cd $(dir $(abspath $(MAKEFILE_LIST)))
	doxygen

${BUILD_SUB_DIRS}:
	mkdir -p $@

# Compile object files into build dir
${BUILD_DIR}/${SRC_DIR}/%.o: ${SRC_DIR}/%.c
	${CC} ${C_FLAGS} -c ${INCLUDE_DIRS_PRIV} $< -o $@

# Build all binaries under test/ as individual binaries.
# All headers are included even though not needed in every case
${BUILD_DIR}/${TEST_SRC_DIR}/%.out: ${TEST_SRC_DIR}/%.c static_lib
	gcc ${C_FLAGS} ${INCLUDE_DIRS_PRIV} ${INCLUDE_DIR_PUB} $< -L . -l:lib${LIB_NAME}.a -o $@
