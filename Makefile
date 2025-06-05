PROJECT = Labwork1
TEST_PROJECT = test-Labwork1

CXX = g++
CXXFLAGS = -std=c++20 -O3 -pthread -I. -Imodel -Iio -Iservice -Iutils -Itest
LDFLAGS = -pthread -lm

SRC = main.cpp \
      $(wildcard model/*.cpp) \
      $(wildcard io/*.cpp) \
      $(wildcard service/*.cpp) \
      $(wildcard utils/*.cpp)

OBJ = $(SRC:.cpp=.o)
OBJ_NO_MAIN = $(filter-out main.o,$(OBJ))

TEST_SRC = tests/test.cpp
TEST_OBJ = tests/test.o

.PHONY: all clean cleanall test run_tests

all: $(PROJECT)

$(PROJECT): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

test: $(OBJ_NO_MAIN) $(TEST_OBJ)
	$(CXX) -o $(TEST_PROJECT) $^ $(LDFLAGS) -lgtest -lgtest_main

run_tests: $(TEST_PROJECT)
	./$(TEST_PROJECT)

clean:
	rm -f *.o model/*.o io/*.o service/*.o utils/*.o tests/*.o *~ core

cleanall: clean
	rm -f $(PROJECT) $(TEST_PROJECT)
