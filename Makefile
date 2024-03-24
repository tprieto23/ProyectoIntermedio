main: 1.x
	./1.x > output.txt

1.x: 1.o include.o
	g++ $^ -o $@

%.o: %.cpp
	g++ -c $<
clean:
	rm *.x output.txt *~ *.o
