# Define the C++ compiler and the flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -g

# Define the target executable
TARGET = main

# Define the source files and object files
SRCS = main.cpp MutexImpl.cpp
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
