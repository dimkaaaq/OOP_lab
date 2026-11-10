CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Iinclude -Iinclude/abilities -Iinclude/statuses
SRCS = $(wildcard src/*.cpp) $(wildcard src/abilities/*.cpp) $(wildcard src/statuses/*.cpp)
TARGET = build/game

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET) src/*.o

run: all
	./$(TARGET)

.PHONY: all clean run