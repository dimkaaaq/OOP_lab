CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Iinclude
SRCS = $(wildcard src/*.cpp)
TARGET = build/game

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET) src/*.o

run: all
	./$(TARGET)

.PHONY: all clean run