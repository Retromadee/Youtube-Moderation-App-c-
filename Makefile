# Compiler
CXX := g++
# Compiler flags
CXXFLAGS := -std=c++11 -Wall -Wextra
# Source files
SRCS := Person.cpp VideoDatabase.cpp Video.cpp User.cpp Creator.cpp main.cpp
# Object files
OBJS := $(SRCS:.cpp=.o)
# Target executable
TARGET := YouTubeModerator

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)
