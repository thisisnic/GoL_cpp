build:
	g++ main.cpp -lncurses -o main.out
  
clean:
	rm *.out

run:
	./main.out
	
go:
	g++ main.cpp -lncurses -o main.out
	./main.out
