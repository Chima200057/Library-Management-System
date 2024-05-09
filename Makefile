# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Target executable
TARGET = library

# Source files
SOURCES = main.cpp book.cpp member.cpp librarian.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Clean up object files and executable
clean:
	rm -f $(OBJECTS) $(TARGET)

# Compile each .cpp file into a .o file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
