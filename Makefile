# Compiler
CXX = g++

# Directories
INCLUDE_DIR = include
SRC_DIR = src
BUILD_DIR = build

# Output executable
TARGET = cc3k

# Flags
CXXFLAGS = -I$(INCLUDE_DIR) -std=c++14 -Wall

# Find all source files recursively
SRCS = $(shell find $(SRC_DIR) -name '*.cc')
# Generate object files from source files
OBJS = $(SRCS:$(SRC_DIR)/%.cc=$(BUILD_DIR)/%.o)

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@

# Compile each source file to an object file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create the build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean up build files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean

