1: 1.gp 1.txt
	gnuplot 1.gp

1.txt: 1.x
	./1.x > 1.txt

2: 2.gp 2.txt
	gnuplot 2.gp

2.txt: 2.x
	./2.x > 2.txt

1.x: 1.o include.o
	g++ $^ -o $@

2.x: 2.o include.o
	g++ $^ -o $@

%.o: %.cpp
	g++ -c $<
clean:
	rm *.x 1.txt *~ *.o 2.txt *.png *.log
