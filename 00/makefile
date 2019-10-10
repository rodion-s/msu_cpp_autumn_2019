sum_by_row sum_by_col: %: %.cpp
	g++ -Wall -Werror -std=gnu++14 -O2 $< -o $@

sum_by_row_valgrind sum_by_col_valgrind: %_valgrind: %
	valgrind --tool=cachegrind --log-file=$*_vg.out ./$<
	rm -f cachegrind*
run: sum_by_row sum_by_col
	./sum_by_row
	./sum_by_col
clean:
	rm -f *_vg.out 