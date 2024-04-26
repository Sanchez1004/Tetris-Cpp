# VARIABLES
CC = g++
CFLAGS = -Wall -std=c++11
LIBS = -lraylib -lglfw3 -lopenal32 -lgdi32 -lwinmm

# DIRECTORIES
SOURCE_DIR = source
INCLUDE_DIR = include
LIB_DIR = lib

# FILES
MAIN_FILE = $(SOURCE_DIR)/main.cpp
OBJ_FILES := $(wildcard $(SOURCE_DIR)/*.cpp)

# RULES
all: tetris

tetris: $(OBJ_FILES)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -L$(LIB_DIR) -o $@ $^ $(LIBS)

clean:
	rm -f tetris $(OBJ_FILES)

# Target to remove object files
cleanobj:
	rm -f $(OBJ_FILES)

.PHONY: clean cleanobj
