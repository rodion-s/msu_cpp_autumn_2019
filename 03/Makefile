all: matrix run
matrix: %: %.cpp %.hpp
	g++ -Wall -Werror -std=gnu++14 -O2 $< -o $@
run: matrix
	./matrix "1"
test: matrix
	python3 check.py
