# Define the C++ compiler and the flags
CXX = g++
CFLAGS = -Wall -Wextra -std=c++11 -g
CXXFLAGS = -Wall -Wextra -std=c++11 -fprofile-arcs -ftest-coverage -pg -g
LDFLAGS = -lgcov

# Define the C compiler for hello.c, fixed_hello.c, race.c, and fixed_race.c
CC = gcc
CCFLAGS = -Wall -Wextra -g

# Define the target executables
TARGET = graph
VALGRIND_TARGET = hello
FIXED_HELLO_TARGET = fixed_hello
RACE_TARGET = race
FIXED_RACE_TARGET = fixed_race

# Define the source files and object files
SRCS = main.cpp graph.cpp
OBJS = $(SRCS:.cpp=.o)
VALGRIND_SRC = hello.c
VALGRIND_OBJ = hello.o
FIXED_HELLO_SRC = fixed_hello.c
FIXED_HELLO_OBJ = fixed_hello.o
RACE_SRC = race.c
RACE_OBJ = race.o
FIXED_RACE_SRC = fixed_race.c
FIXED_RACE_OBJ = fixed_race.o

# Default target
all: $(TARGET) $(VALGRIND_TARGET) $(FIXED_HELLO_TARGET) $(RACE_TARGET) $(FIXED_RACE_TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to compile the Valgrind target
$(VALGRIND_TARGET): $(VALGRIND_OBJ)
	$(CC) $(CCFLAGS) -o $(VALGRIND_TARGET) $(VALGRIND_OBJ)

# Rule to compile fixed_hello.c into executable
$(FIXED_HELLO_TARGET): $(FIXED_HELLO_OBJ)
	$(CC) $(CCFLAGS) -o $(FIXED_HELLO_TARGET) $(FIXED_HELLO_OBJ)

# Rule to compile race.c into executable
$(RACE_TARGET): $(RACE_OBJ)
	$(CC) $(CCFLAGS) -o $(RACE_TARGET) $(RACE_OBJ)

# Rule to compile fixed_race.c into executable
$(FIXED_RACE_TARGET): $(FIXED_RACE_OBJ)
	$(CC) $(CCFLAGS) -o $(FIXED_RACE_TARGET) $(FIXED_RACE_OBJ)

# Rule to compile C files into object files
%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

# Generate code coverage report
coverage: all
	./$(TARGET) -e 1000 -v 100 -s 42
	gcov $(SRCS)
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory out

# Clean intermediate coverage files
coverage_clean:
	rm -f *.gcno *.gcda *.gcov

# Generate profiling report
profile: all
	./$(TARGET) -e 1000 -v 100 -s 42
	gprof $(TARGET) gmon.out > gprof_report.txt

# Run Valgrind memory check with larger input
valgrind: all
	valgrind --leak-check=full --log-file=valgrind_report.txt ./$(TARGET) -e 1000 -v 100 -s 42

# Run Valgrind memory check on hello.c
valgrind_hello: $(VALGRIND_TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(VALGRIND_TARGET) argument1 argument2 > valgrind_hello_report.txt 2>&1

# Run Valgrind memory check on fixed_hello.c
valgrind_fixed_hello: $(FIXED_HELLO_TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(FIXED_HELLO_TARGET) argument1 argument2 > valgrind_fixed_hello_report.txt 2>&1

# Run Valgrind memory check on race.c
valgrind_race: $(RACE_TARGET)
	valgrind --tool=helgrind ./$(RACE_TARGET) > valgrind_race_report.txt 2>&1

# Run Valgrind memory check on fixed_race.c
valgrind_fixed_race: $(FIXED_RACE_TARGET)
	valgrind --tool=helgrind ./$(FIXED_RACE_TARGET) > valgrind_fixed_race_report.txt 2>&1

# Generate Valgrind call graph with larger input
callgraph: all
	valgrind --tool=callgrind --callgrind-out-file=callgrind.out ./$(TARGET) -e 1000 -v 100 -s 42
	kcachegrind callgrind.out

# Clean up all build files, intermediate files, and coverage files
clean: coverage_clean
	rm -f $(OBJS) $(VALGRIND_OBJ) $(FIXED_HELLO_OBJ) $(RACE_OBJ) $(FIXED_RACE_OBJ) $(TARGET) $(VALGRIND_TARGET) $(FIXED_HELLO_TARGET) $(RACE_TARGET) $(FIXED_RACE_TARGET) gmon.out callgrind.out coverage.info
	rm -rf out

# Phony targets
.PHONY: all clean coverage profile valgrind callgraph coverage_clean valgrind_hello valgrind_fixed_hello valgrind_race valgrind_fixed_race
