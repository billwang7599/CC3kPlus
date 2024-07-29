# Compiler
CXX = g++

# Directories
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Flags
CXXFLAGS = -I$(INCLUDE_DIR) -Wall -std=c++11

# Sources and Objects
SOURCES = $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# Target executable
TARGET = $(BIN_DIR)/my_program

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compiling
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR) $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -Icomponents -Ientities -Isystems

# Directories
SRC_DIRS = components entities systems
OUT_DIR = out

# Find all .cc files in the source directories
SRCS = $(shell find $(SRC_DIRS) -name '*.cc') main.cc

# Object files
OBJS = $(SRCS:.cc=.o)

# Output executable
TARGET = $(OUT_DIR)/main

# Default target
all: $(TARGET)


#endif
# Link object files to create the final executable
$(TARGET): $(OBJS) | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Compile .cc files to .o files
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create the output directory if it doesn't exist
$(OUT_DIR):
	mkdir -p $(OUT_DIR)

# Clean up object files and the executable
clean:
	rm -rf $(OBJS) $(TARGET) $(OUT_DIR)

.PHONY: all clean
