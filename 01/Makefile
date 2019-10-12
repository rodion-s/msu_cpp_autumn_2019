all: calc run
calc: %: %.cpp
	g++ -Wall -Werror -std=gnu++14 -O2 $< -o $@
run: calc
	./calc "42"
test: calc
	python3 check.py
clean:
	rm -f calc
