# Makefile for compiling C++ files in the src folder

CXX := g++
CXXFLAGS := -std=c++11 -Wall
SRC_DIR := src
BIN_DIR := bin
EXEC_NAME := fil_rouge.out

# Get a list of all .cpp files in the src folder
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)

# Generate corresponding object file names in the bin folder
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SRC_FILES))

# Target for the final executable
TARGET := $(BIN_DIR)/$(EXEC_NAME)

# Default target
all: $(TARGET)

# Rule for linking object files to create the executable
$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule for compiling each source file into an object file
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f $(OBJ_FILES) $(TARGET)

.PHONY: all clean

