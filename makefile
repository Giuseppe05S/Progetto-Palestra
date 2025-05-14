main.exe: main.o iscritto.o data.o liste.o hash.o corso.o prenotazione.o
	gcc main.o iscritto.o data.o liste.o hash.o corso.o prenotazione.o -o main.exe -lm
iscritto.o: iscritto.c iscritto.h utils.h data.h
	gcc -c iscritto.c
corso.o: corso.c corso.h utils.h data.h
	gcc -c corso.c
prenotazione.o: prenotazione.c corso.h iscritto.h utils.h data.h
	gcc -c prenotazione.c
data.o: data.c data.h
	gcc -c data.c
liste.o: liste.c liste.h corso.h
	gcc -c liste.c
hash.o: hash.c hash.h iscritto.h utils.h
	gcc -c hash.c
main.o: main.c iscritto.h liste.h data.h utils.h
	gcc -c	main.c
clean:
	rm -f *.o main.exe