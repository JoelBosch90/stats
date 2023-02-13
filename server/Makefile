# Name the executable.
OUTPUT_FILENAME = read_logs

# Name the directory for the output binary.
OUTPUT_DIRECTORY = ./bin

# Name the directory where we can find the files to compile.
SOURCE_DIRECTORY = ./source

# Compiler settings.
COMPILER = g++
COMPILER_FLAGS = -Wall -std=c++17

# Included external libraries that need to be included.
LIBRARIES = sqlite3

# Find all (nested) subdirectories.
SUBDIRECTORIES = $(shell find $(SOURCE_DIRECTORY) -type d)

# List all of the files in the subdirectories.
SOURCE_FILES += $(foreach subdirectory,$(SUBDIRECTORIES),$(wildcard $(subdirectory)/*.cpp))

# We assume that each C++ file is accompanied by a header file by the same name.
HEADER_FILES = $(SOURCE_FILES:.cpp=.h)

# We store the compiled object in the same directory as the C++ file, by the
# same name.
OBJECT_FILES = $(SOURCE_FILES:.cpp=.o)

# Generate include flags for each subdirectory, and add them to the compiler
# flags.
INCLUDE_FLAGS = $(foreach subdirectory,$(SUBDIRECTORIES),-I$(subdirectory))
COMPILER_FLAGS += $(INCLUDE_FLAGS)

# Create the target flag.
TARGET = $(OUTPUT_DIRECTORY)/$(OUTPUT_FILENAME)

# Create the target executable.
$(TARGET): $(OBJECT_FILES)
	$(COMPILER) $(COMPILER_FLAGS) $(OBJECT_FILES) -o $@ -l $(LIBRARIES)

# Compile all dependencies.
%.o: %.cpp $(HEADER_FILES)
	$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@

# Run 'make clean' to remove all compiled objects, including the executable.
.PHONY: clean
clean:
	rm -f $(OBJECT_FILES) $(TARGET)