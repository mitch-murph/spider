all: spider

spider: main.o
	g++ main.o -o spider -lsfml-graphics -lsfml-window -lsfml-system


main.o:
	g++ -c Main.cpp -o main.o

clean:
	rm spider main.o