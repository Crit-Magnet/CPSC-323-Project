# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Wpedantic -Werror -Wshadow -Wconversion

# Formatting and Linting
FORMATTER = clang-format
LINTER = cpplint

# Source files
SRCS = main.cpp lexer.cpp fsm_id.cpp fsm_number.cpp

# Header files (for dependency tracking)
HEADERS = lexer.h fsm_id.h fsm_number.h keywords.h separators.h operators.h token.h

# Object files (generated from source files)
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = lexer

# Default rule to compile the program
all: $(TARGET)

# Linking step: generate the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compilation rule: compile each .cpp file into a .o file
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule: remove object files and executable
clean:
	rm -f $(OBJS) $(TARGET)

# Format code using clang-format (Google style, 80-column limit)
format:
	$(FORMATTER) -i --style=Google $(SRCS) $(HEADERS)

# Run the program after compilation
run: all
	./$(TARGET)
