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

3: 3.gp 3.txt
	gnuplot 3.gp

4: 4.gp 4.txt
	gnuplot 4.gp

// Catch2
test.x: test.o include.o
	g++ -std=c++20 -O3 -Wall -fsanitize=address,undefined,leak $^ -o $@

test.o: test.cpp include.cpp
	g++ -c $^


// Profiling
test_gprof.x: main.cpp include.cpp
	g++ -O3 -Wall -pg -g $^ -o $@
	./$@

gprof: test_gprof.x gmon.out
	gprof $^ > gprof-report.txt


// Cachegrind sin optimización
test_val_cache.x: main.cpp include.cpp
	g++ -g $^ -o $@

cacheg.out: test_val_cache.x
	valgrind --tool=cachegrind ./$<

cachegrind: cachegrind.out.*
	cg_annotate --auto=yes $< > cachegrind-report.txt


// Cachegrind con optimización
test_val_cache.x: main.cpp include.cpp
	g++ -O3 -g $^ -o $@

cacheg.out: test_val_cache.x
	valgrind --tool=cachegrind ./$<

cachegrind: cachegrind.out.*
	cg_annotate --auto=yes $< > cachegrind-report-optimization.txt


// memcheck
memcheck.x: main.cpp include.cpp
	g++ -g -O3 $^ -o $@

memcheck: memcheck.x
	valgrind --tool=memcheck --leak-check=yes ./$<

clean:
	rm *.x 1.txt *~ *.o 2.txt 3.txt 4.txt *.png *.log *.pdf test.txt cachegrind.out.* gprof-report.txt *cachegrind-report.txt *cachegrind-report-optimization.txt *.out
