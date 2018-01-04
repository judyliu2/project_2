forking: client fserver

basic: client bserver

fserver: server.o networking.o
	gcc -o server server.o networking.o

client: client.o networking.o
	gcc -o client client.o networking.o

bserver: server.o networking.o
	gcc -o server server.o networking.o

client.o: client.c methods.h
	gcc -c client.c

basic_server.o: server.c methods.h
	gcc -c server.c

forking_server.o: server.c methods.h
	gcc -c server.c

pipe_networking.o: networking.c methods.h
	gcc -c networking.c

clean:
	rm *.o
	rm *~
