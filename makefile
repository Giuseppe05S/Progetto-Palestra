main.exe: iscritto.o data.o liste.o main.o
	gcc iscritto.o data.o liste.o main.o -o main.exe -lm
iscritto.o: iscritto.c iscritto.h utils.h data.h
	gcc -c iscritto.c
data.o: data.c data.h
	gcc -c data.c
liste.o: liste.c liste.h iscritto.h
	gcc -c liste.c
main.o: main.c iscritto.h liste.h data.h utils.h
	gcc -c	main.c
clean:
	rm -f *.o main.exe