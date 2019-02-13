CC = gcc
CFLAGS = -c -Wall
LIBDIR = lib
BINDIR = dist
OBJECTS = dist/solutions.o\
					dist/my-functions.o

default: link

link: $(OBJECTS)
	$(CC) $? -o $(BINDIR)/solutions

$(BINDIR)/solutions.o: solutions.c
	$(CC) $(CFLAGS) solutions.c -o $(BINDIR)/solutions.o

$(BINDIR)/my-functions.o: $(LIBDIR)/my-functions.c
	$(CC) $(CFLAGS) $(LIBDIR)/my-functions.c -o $(BINDIR)/my-functions.o

clean:
	rm -rf ./$(BINDIR) && mkdir $(BINDIR)
