
CC = gcc
CFLAGS  = -g -Wall

default: server.o

# To create the executable file count we need the object files
# countwords.o, counter.o, and scanner.o:

server.o:  client.o
	$(CC) $(CFLAGS) -o client client.c

# To create the object file countwords.o, we need the source
# files countwords.c, scanner.h, and counter.h:
#
client.o:
	$(CC) $(CFLAGS) -o server server.c

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	rm server client
