PROJECT = Labwork1

IDIR = .
CXX = g++
CXXFLAGS = -I$(IDIR) -std=c++20 -O3 -pthread
LDFLAGS = -pthread -lm

DEPS = BMPHeader.h BMPImage.h BMPInfoHeader.h BMPReader.h BMPService.h ThreadPool.h BMPWriter.h BMPMultiThreadService.h
OBJ = main.o BMPImage.o BMPReader.o BMPService.o BMPWriter.o BMPMultiThreadService.o

.PHONY: default all clean cleanall

default: all

%.o: %.cpp $(DEPS)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(PROJECT): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

all: $(PROJECT)

clean:
	rm -f *.o *~ core

cleanall: clean
	rm -f $(PROJECT)
