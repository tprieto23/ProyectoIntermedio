main: main.x input.txt input4.txt
	./$<

main.x: main.o include.o
	g++ -std=c++20 -O3 -g -Wall -fsanitize=address,undefined,leak $^ -o $@

main.o: main.cpp include.cpp
	g++ -c $^

1: 1.gp 1.txt
	gnuplot 1.gp

2: 2.gp 2.txt
	gnuplot 2.gp

4: 4.gp 4.txt
	gnuplot 4.gp

test_gprof.x: main.cpp include.cpp
	g++ -O3 -Wall -pg -g $^ -o $@
	./$@

gprof: test_gprof.x gmon.out
	gprof $^ > gprof.txt

test_val_cache.x: main.cpp include.cpp
	g++ -O3 -g $^ -o $@

cacheg.out: test_val_cache.x
	valgrind --tool=cachegrind ./$<

cachegrind: cachegrind.out.*
	cg_annotate --auto=yes $<

memcheck.x: main.cpp include.cpp
	g++ -g -O3 $^ -o $@

memcheck: memcheck.x
	valgrind --tool=memcheck --leak-check=yes ./$<

clean:
	rm *.x 1.txt *~ *.o 2.txt 4.txt *.png *.log *.pdf test.txt cachegrind.out.* gprof.txt *.out
