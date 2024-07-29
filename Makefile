# Compiler
CXX = g++

# Directories
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = build
BIN_DIR = bin
CONSTANTS_DIR = constants

# Flags
CXXFLAGS = -I$(INCLUDE_DIR) -I$(CONSTANTS_DIR) -Wall -std=c++11

# Sources and Objects
SOURCES = $(wildcard $(SRC_DIR)/**/*.cc) $(wildcard $(SRC_DIR)/*.cc) $(CONSTANTS_DIR)/constants.cc
OBJECTS = $(patsubst $(SRC_DIR)/%.cc, $(OBJ_DIR)/%.o, $(SOURCES)) $(OBJ_DIR)/constants.o

# Target executable
TARGET = $(BIN_DIR)/my_program

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compiling
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	@mkdir -p $(OBJ_DIR) $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/constants.o: $(CONSTANTS_DIR)/constants.cc
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
