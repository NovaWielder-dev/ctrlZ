# The Compiler
CXX = g++

# Compiler Flags: Use C++17 standard and show all warnings
CXXFLAGS = -std=c++17 -Wall

# The name of your final application
TARGET = race_sim

# Every .cpp file that contains code (Do NOT include .h files here)
SRCS = main.cpp io.cpp optimizer.cpp physics.cpp

# The build rule: How to combine them
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# A handy rule to delete the old application if you want a fresh start
clean:
	rm -f $(TARGET)