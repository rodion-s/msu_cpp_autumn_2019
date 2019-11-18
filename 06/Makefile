all: format
format: %: %.cpp %.h
	g++ -Wall -Werror -std=gnu++14 -O2 $< -o $@
run: format
	./format
test: format
	./format