all: alloc run
alloc: %: %.cpp
	g++ -Wall -Werror -std=gnu++14 -O2 $< -o $@
run: alloc
	./alloc "16" "alloc:12" "alloc:1" "alloc:2" "alloc:10"
test: alloc
	python3 check.py
