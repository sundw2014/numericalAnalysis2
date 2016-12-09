CC = gcc
CXX = g++

# Target file name (without extension).
TARGET = main
TEST = test

#source file path
SRC_DIR = ./
INC_DIR = ./

CFLAGS = -std=c++11 -g
CFLAGS += $(patsubst %,-I%,$(EXTRAINCDIRS))
CFLAGS += -I$(INC_DIR)

LDFLAGS = -lgmpxx -lgmp

# SRC files
CSRC = $(wildcard $(SRC_DIR)/*.c)
CPPSRC += $(wildcard $(SRC_DIR)/*.cpp)

INC = $(wildcard $(INC_DIR)/*.h)

# Define all object files.
COBJ = $(CSRC:.c=.o)
CPPOBJ = $(CPPSRC:.cpp=.o)

# Default target.
$(TARGET) : $(COBJ) $(CPPOBJ)
	$(CXX) -o $(TARGET) $(COBJ) $(CPPOBJ) $(LDFLAGS)

$(COBJ) : %.o : %.c $(INC)
	$(CC) -c $< -o $@ $(CFLAGS)

$(CPPOBJ) : %.o : %.cpp $(INC)
	$(CXX) -c $< -o $@ $(CFLAGS)

.PHONY:clean
clean:
	@rm $(COBJ) $(CPPOBJ) $(TARGET)

.PHONY:test
test:
	rm main.o
	$(CXX) -c test/test.cpp -o /test/test.o $(CFLAGS)
	$(CXX) -o test/test /test/test.o *.o $(LDFLAGS)
	test/test
