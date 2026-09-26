CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic
TARGET = game
SRCS = $(wildcard *.cpp)

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX)	$(CXXFLAGS)	$(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o

run: all
	./$(TARGET)

.PHONY: all clean run