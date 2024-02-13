# Define C++ compiler
CXX := g++

# Compiler and linker flags
CXXFLAGS = -Wall -std=c++17
LDFLAGS =

# Source and object directories
SRC_DIR = src
OBJ_DIR = _obj
BIN_DIR = _bin

# Header directory
INC_DIR = include

# Target executable name
TARGET = myapp

# Source and object files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Dependency files for tracking headers
DEPS = $(OBJECTS:.o=.d)

# Default 'all' target
all: $(TARGET)

# Link object files to create the target executable
$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@

# Include dependency files
-include $(DEPS)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# 'clean' target for removing build artifacts
clean:
	rm -f $(OBJECTS) $(DEPS) $(TARGET)

# 'rebuild' target for a clean build
rebuild: clean all

# Phony targets
.PHONY: all clean rebuild
