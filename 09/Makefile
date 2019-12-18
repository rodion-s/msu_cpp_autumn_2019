all: external_sort_final

gen: gen_inp.cpp
	g++ -std=gnu++14 -O2 gen_inp.cpp -o gen_inp
	./gen_inp
external_sort_final: %: %.cpp
	g++ -std=gnu++14 -O2 $< -o $@ -pthread
run: external_sort_final
	./external_sort_final
test: gen external_sort_final
	g++ -std=gnu++14 -O2 test.cpp -o test
	./external_sort_final
	./test