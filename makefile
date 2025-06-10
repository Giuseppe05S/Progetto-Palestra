main.exe: main.o iscritto.o data.o liste.o hash.o corso.o prenotazione.o listaPrenotazione.o utils.o test.o
	gcc main.o iscritto.o data.o liste.o hash.o corso.o prenotazione.o listaPrenotazione.o utils.o test.o -o main.exe -lm
main.o: main.c utils.h iscritto.h data.h liste.h hash.h corso.h prenotazione.h listaPrenotazione.h test.h
	gcc -c main.c
iscritto.o: iscritto.c iscritto.h data.h utils.h
	gcc -c iscritto.c
corso.o: corso.c corso.h data.h utils.h
	gcc -c corso.c
prenotazione.o: prenotazione.c prenotazione.h iscritto.h corso.h data.h
	gcc -c prenotazione.c
test.o: test.c utils.h hash.h liste.h prenotazione.h listaPrenotazione.h
	gcc -c test.c
data.o: data.c data.h
	gcc -c data.c
liste.o: liste.c liste.h corso.h
	gcc -c liste.c
hash.o: hash.c hash.h iscritto.h
	gcc -c hash.c
listaPrenotazione.o: listaPrenotazione.c listaPrenotazione.h prenotazione.h
	gcc -c listaPrenotazione.c
utils.o:utils.c utils.h iscritto.h data.h liste.h hash.h
	gcc -c utils.c
clean:
	rm -f *.o main.exe
run: main.exe
	./main.exe
