CC=g++
CFLAGS=-I.
OBJ = server.cpp client.cpp
LIBS = httplib.h
main: $(OBJ)
	make server
	make client
server: server.cpp 
	$(CC) -std=c++11 -o $@ $< -lpthread $(CFLAGS)
client: client.cpp 
	$(CC) -std=c++11 -o $@ $< -lpthread $(CFLAGS)
%.o: %.cpp $(LIBS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm *.o 
