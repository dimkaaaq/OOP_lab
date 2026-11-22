CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Iinclude -Iinclude/core -Iinclude/abilities -Iinclude/statuses -Iinclude/items -Iinclude/levels -Iinclude/ui -Iinclude/input -finput-charset=UTF-8 -fexec-charset=UTF-8 

SRCS = $(wildcard src/*.cpp) \
       $(wildcard src/core/*.cpp) \
       $(wildcard src/abilities/*.cpp) \
       $(wildcard src/statuses/*.cpp) \
       $(wildcard src/items/*.cpp) \
       $(wildcard src/levels/*.cpp) \
       $(wildcard src/ui/*.cpp) \
       $(wildcard src/input/*.cpp)

TARGET = build/game

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o

run: all
	./$(TARGET)

.PHONY: all clean run