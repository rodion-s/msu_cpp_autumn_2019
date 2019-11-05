all: main run
my_big_int: %: %.cpp %.hpp
	g++ -Wall -Werror -std=gnu++14 -O2 $< -o $@
run: my_big_int
	./my_big_int
test: my_big_int
	g++ -Wall -Werror -std=gnu++14 -O2 test.cpp -o test
	./test
