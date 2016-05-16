main:main.o lab5.o
	g++ -o lab5 main.o lab5.o

lab5.o:lab5.cpp lab5.h
	g++ -c lab5.cpp

main.o:main.cpp lab5.h
	g++ -c main.cpp

clean:
	rm lab5.o main.o
