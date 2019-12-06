all: threadpool
threadpool: %: %.cpp %.h
	g++ -std=gnu++14 -O2 $< -o $@ -pthread
run: threadpool
	./threadpool
test: threadpool
	./threadpool