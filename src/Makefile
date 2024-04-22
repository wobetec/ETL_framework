MAKEFILE_DIR = $(dir $(lastword $(MAKEFILE_LIST)))

# Compiler
CC := g++

# Compiler flags
CFLAGS := -Wall -Wextra -std=c++11

# Directories
SRC_DIR := $(MAKEFILE_DIR)/w
OBJ_DIR := $(MAKEFILE_DIR)/obj
LIB_DIR := $(MAKEFILE_DIR)/lib

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Library
LIB := $(LIB_DIR)/framework.a

# Targets
build: $(LIB)

$(LIB): $(OBJS) | $(LIB_DIR)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR)

test:
	g++ test.cpp datetime.cpp -o test.out

.PHONY: all clean
