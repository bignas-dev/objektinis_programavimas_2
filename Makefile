.PHONY: main bench gen clean
FLAG=-O3

main: main.cpp
	g++ $(FLAG) main.cpp -o main && ./main

bench: benchmark.cpp
	g++ $(FLAG) benchmark.cpp -o benchmark && ./benchmark

gen: generator.cpp
	g++ $(FLAG) generator.cpp -o generator && ./generator

clean:
	rm -f main benchmark generator *.txt


