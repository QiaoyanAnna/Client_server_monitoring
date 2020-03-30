all: server client

server: server.o
	gcc -Wall -std=c99 -o server server.o

server.o: server.c
	gcc -Wall -std=c99 -c server.c

client: client.o
	gcc -Wall -std=c99 -o client client.o

client.o: client.c
	gcc -Wall -std=c99 -c client.c

clean:
	rm -f client *.o
	rm -f server *.o

remake: clean
	make
