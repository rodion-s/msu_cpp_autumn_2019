all: serializer
serializer: %: %.cpp %.hpp
	g++ -Wall -Werror -std=gnu++14 -O2 $< -o $@
run: serializer
	./serializer
test: serializer
	./serializer