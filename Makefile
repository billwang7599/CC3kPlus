# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++14 -Wall -g -Wextra -Icomponents -Ientities -Isystems -Iconstants

# Directories
SRC_DIRS = components entities systems constants
OUT_DIR = out

# Source files
SRCS = $(shell find $(SRC_DIRS) -name '*.cc') main.cc

# Object files
OBJS = $(SRCS:.cc=.o)

# Output executable
TARGET = $(OUT_DIR)/main

# Default target
all: $(TARGET)

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