# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall -g -MMD

# Directories
SRC_DIR = .
OUT_DIR = out
EXECUTABLE = cc3k

# Find all .cc files in the current directory and subdirectories
SRC_FILES = $(shell find $(SRC_DIR) -name '*.cc')
OBJ_FILES = $(SRC_FILES:.cc=.o)

# Target to create the executable
$(OUT_DIR)/$(EXECUTABLE): $(OBJ_FILES)
	mkdir -p $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/$(EXECUTABLE) $(OBJ_FILES)

# Rule to compile .cc files into .o files
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and executable
clean:
	rm -f $(OBJ_FILES)
	rm -f $(OUT_DIR)/$(EXECUTABLE)

.PHONY: clean
