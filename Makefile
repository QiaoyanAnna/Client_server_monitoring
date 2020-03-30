all: server client

server: server.o verify.o
	gcc -Wall -o server server.o verify.o

server.o: server.c verify.h
	gcc -Wall -c server.c

client: client.o verify.o
	gcc -Wall -o client client.o verify.o

client.o: client.c verify.h
	gcc -Wall -c client.c

verify.o: verify.c verify.h
	gcc -Wall -c verify.c

clean:
	rm -f client *.o
	rm -f server *.o

remake: clean
	make
