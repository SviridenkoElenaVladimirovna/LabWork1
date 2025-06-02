PROJECT = Labwork1

CXX = g++
CXXFLAGS = -std=c++20 -O3 -pthread -I. -Imodel -Iio -Iservice -Iutils
LDFLAGS = -pthread -lm

SRC = main.cpp \
      $(wildcard model/*.cpp) \
      $(wildcard io/*.cpp) \
      $(wildcard service/*.cpp) \
      $(wildcard utils/*.cpp)

OBJ = $(SRC:.cpp=.o)

.PHONY: default all clean cleanall

default: all

all: $(PROJECT)

$(PROJECT): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -f *.o model/*.o io/*.o service/*.o utils/*.o *~ core

cleanall: clean
	rm -f $(PROJECT)
