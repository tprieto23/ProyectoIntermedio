1: 1.gp 1.txt
	gnuplot 1.gp

1.txt: 1.x
	./1.x > 1.txt

2: 2.gp 2.txt
	gnuplot 2.gp

2.txt: 2.x
	./2.x > 2.txt

1.x: 1.o include.o
	g++ -fsanitize=address -fsanitize=undefined -fsanitize=leak -O3 $^ -o $@

2.x: 2.o include.o
	g++ -fsanitize=address -fsanitize=undefined -fsanitize=leak -O3 $^ -o $@

%.o: %.cpp
	g++ -O3 -c $<
clean:
	rm *.x 1.txt *~ *.o 2.txt *.png *.log *.pdf

test: test.txt
	gnuplot | plot "test.txt" pt 7

test.txt: test.x
	./test.x > test.txt

test.x: test.o include.o
	g++ -O3 -fsanitize=address -fsanitize=undefined -fsanitize=leak test.o include.o -o test.x
