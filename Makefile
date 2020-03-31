all: server client

server: server.o verify.o tands.o
	gcc -Wall -pthread -o server server.o verify.o tands.o -lm

server.o: server.c verify.h tands.h
	gcc -Wall -c server.c

client: client.o verify.o tands.o
	gcc -Wall -o client client.o verify.o tands.o -lm

client.o: client.c verify.h tands.h
	gcc -Wall -c client.c

verify.o: verify.c verify.h
	gcc -Wall -c verify.c

tands.o: tands.c 
	gcc -Wall -c tands.c

clean:
	rm -f client *.o
	rm -f server *.o

remake: clean
	make
