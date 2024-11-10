
CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = machine
SRC = main.cpp Machine.cpp InstructionDecoder.cpp AssemblyParser.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

run: all
	./${TARGET}
