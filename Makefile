CXX = g++
CXXFLAGS = -O3 -std=c++17 -Wall

TARGET = program
TARGET_STRUCT = test_struct
TARGET_CLASS = test_class

SRC = main.cpp benchmark.cpp
HEADERS = benchmark.h student.h

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

$(TARGET_STRUCT): main_struct.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET_STRUCT) main_struct.cpp

$(TARGET_CLASS): main_class.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET_CLASS) main_class.cpp

clean:
	rm -f $(TARGET) $(TARGET_STRUCT) $(TARGET_CLASS) *.txt rezultatai.csv palyginimas*.csv

run: $(TARGET)
	./$(TARGET)

test: $(TARGET_STRUCT) $(TARGET_CLASS)
	@echo "=== STRUCT versija ==="
	./$(TARGET_STRUCT)
	@echo "=== CLASS versija ==="
	./$(TARGET_CLASS)

test_v1.2: test_v1.2.cpp student.h
	$(CXX) $(CXXFLAGS) -o test_v1.2 test_v1.2.cpp

run_test_v1.2: test_v1.2
	./test_v1.2

test_v1.5: test_v1.5.cpp student.h zmogus.h
	$(CXX) $(CXXFLAGS) -o test_v1.5 test_v1.5.cpp

run_test_v1.5: test_v1.5
	./test_v1.5

test_all: test test_v1.2 test_v1.5

# Unit testai su Catch2
CATCH_INCLUDE = -Itests
UNIT_TEST_SRC = tests/unit_tests.cpp
UNIT_TEST_BIN = tests/unit_tests

tests: $(UNIT_TEST_BIN) test_vector

test_vector: tests/test_vector.cpp Vector.h tests/catch.hpp
	$(CXX) $(CXXFLAGS) $(CATCH_INCLUDE) -o tests/test_vector tests/test_vector.cpp

run_tests: tests
	./$(UNIT_TEST_BIN)
	./tests/test_vector

# Vector benchmark
benchmark_vector: benchmark_vector.cpp Vector.h
	$(CXX) $(CXXFLAGS) -o benchmark_vector benchmark_vector.cpp

run_benchmark: benchmark_vector
	./benchmark_vector

# Vector version of student program
main_vector: main_vector.cpp Vector.h student.h
	$(CXX) $(CXXFLAGS) -o main_vector main_vector.cpp

run_vector: main_vector
	./main_vector

# Doxygen dokumentacija
doxygen:
	doxygen Doxyfile

doxygen_pdf: doxygen
	@echo "PDF generavimui reikalingas TeXLive. Naudokite Overleaf jei neturite."

# Valymas
clean:
	rm -f $(TARGET) $(TARGET_STRUCT) $(TARGET_CLASS) *.txt rezultatai.csv palyginimas*.csv
	rm -rf docs/
	rm -f tests/unit_tests

.PHONY: all clean run test tests run_tests doxygen doxygen_pdf O1 O2 O3 debug

O1: clean $(TARGET_STRUCT) $(TARGET_CLASS)

O2: CXXFLAGS = -O2 -std=c++17 -Wall
O2: clean $(TARGET_STRUCT) $(TARGET_CLASS)

O3: CXXFLAGS = -O3 -std=c++17 -Wall
O3: clean $(TARGET_STRUCT) $(TARGET_CLASS)

debug: CXXFLAGS = -g -std=c++17 -Wall
debug: $(TARGET)

.PHONY: all clean run test O1 O2 O3 debug
