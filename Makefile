CC = gcc
CFLAGS = -c

app: main.o numpad.o
	$(CC) -o calc -lncursesw main.o numpad.o -lm 

main.o: main.c
	$(CC) $(CFLAGS) main.c

numpad.o: numpad.h numpad.c
	$(CC) $(CFLAGS) numpad.c

clean:
	rm -rf *.o
