all: vector
vector: %: %.cpp %.h
	g++ -std=gnu++14 -O2 $< -o $@
run: vector
	./vector
test: vector
	./vector