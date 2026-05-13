.PHONY: main bench gen test docs clean 
FLAG=-O3

main: main.cpp
	g++ $(FLAG) main.cpp -o main && ./main

bench: benchmark.cpp
	g++ $(FLAG) benchmark.cpp -o benchmark && ./benchmark

gen: generator.cpp
	g++ $(FLAG) generator.cpp -o generator && ./generator

test: test.cpp
	g++ $(FLAG) test.cpp -o test && ./test

docs: Doxyfile
	mkdir -p docs/pdf
	doxygen Doxyfile
	for f in docs/html/*.html; do \
		base=$$(basename "$$f" .html); \
		wkhtmltopdf --enable-local-file-access "$$f" "docs/pdf/$$base.pdf"; \
	done
	mutool merge -o docs/pdf/docs.pdf docs/pdf/*.pdf
	find docs/pdf -name "*.pdf" ! -name "docs.pdf" -delete

clean:
	rm -f main benchmark generator test *.txt
	rm -rf docs/
