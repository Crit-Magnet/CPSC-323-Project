# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Wpedantic -Werror -Wshadow -Wconversion -ILexicalAnalyzer -ISyntaxAnalyzer

# Formatting and Linting
FORMATTER = clang-format
LINTER = cpplint

# Directories
LEX_DIR = LexicalAnalyzer
SYN_DIR = SyntaxAnalyzer

# Sources and headers
SRCS = $(wildcard $(LEX_DIR)/*.cpp) $(wildcard $(SYN_DIR)/*.cpp) main.cpp
HEADERS = $(wildcard $(LEX_DIR)/*.h) $(wildcard $(SYN_DIR)/*.h)

# Object file output location — .o files go in LexicalAnalyzer/
OBJS = $(SRCS:.cpp=.o)
OBJS := $(patsubst main.o,$(LEX_DIR)/main.o,$(OBJS))  # place main.o in LexicalAnalyzer too

# Executable name
TARGET = main.exe

# Default target
all: $(TARGET)

# Linking step
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile each source file to an object file in LexicalAnalyzer
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(LEX_DIR)/main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule: remove object files and executable
clean:
	rm -f $(LEX_DIR)/*.o $(SYN_DIR)/*.o $(LEX_DIR)/main.o $(TARGET)

# Format all code
format:
	$(FORMATTER) -i --style=Google $(SRCS) $(HEADERS)

# Run program
run: all
	./$(TARGET)

.PHONY: all clean format run
