CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall
TARGET = a
SRC = a.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)