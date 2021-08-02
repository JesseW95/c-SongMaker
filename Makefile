#all to have multiple executables
all: playsong
CC=gcc
CFLAGS=-I.
LIBS=-lm
DEPS = gensnd.h process.h iosnd.h sound.h

%.o: %.c $(DEPS)
	$(CC) $(LIBS) -c -o $@ $< $(CFLAGS)
	
playsong: main.o gensnd.o
	$(CC) $(LIBS) -o $@ $^ $(CFLAGS)
	rm -f *.o
	
clean:
	rm -f *.o output playsong