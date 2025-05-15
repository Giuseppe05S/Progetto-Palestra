main.exe: main.o iscritto.o data.o liste.o hash.o corso.o prenotazione.o utils.o
	gcc main.o iscritto.o data.o liste.o hash.o corso.o prenotazione.o utils.o -o main.exe -lm
iscritto.o: iscritto.c iscritto.h data.h utils.h
	gcc -c iscritto.c
corso.o: corso.c corso.h data.h utils.h
	gcc -c corso.c
prenotazione.o: prenotazione.c prenotazione.h iscritto.h corso.h data.h
	gcc -c prenotazione.c
data.o: data.c data.h
	gcc -c data.c
liste.o: liste.c liste.h corso.h
	gcc -c liste.c
hash.o: hash.c hash.h iscritto.h
	gcc -c hash.c
utils.o:utils.c utils.h iscritto.h data.h liste.h hash.h
	gcc -c utils.c
main.o: main.c utils.h iscritto.h data.h liste.h hash.h corso.h
	gcc -c	main.c
clean:
	rm -f *.o main.exe
run: main.exe
	./main.exe
