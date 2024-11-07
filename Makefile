
PROJECT = Labwork1


IDIR = .
CXX=g++

CXXFLAGS = -I$(IDIR)

ODIR = OBJ

LDIR = ../lib

LIBS = -lm

DEPS = BMPHeader.h BMPImage.h BMPInfoHeader.h BMPReader.h BMPService.h BMPWriter.h

OBJ = main.o BMPImage.o BMPReader.o BMPService.o BMPWriter.o

.PHONY: default
default: all

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(PROJECT): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)


all: $(PROJECT)

.PHONY: clean
clean:
	rm -f *.o *~ core

cleanall: clean
	rm -f $(PROJECT)
