CC=gcc
LDIR=-L ../wiringPi/wiringPi/
LIBS=-lwiringPi
CFLAGS=-fPIC -Wall
OBJS=max7219.o
LIBNAME=libmax7219.so
%.c: %.h

max7219lib: $(OBJS)
	$(CC) -shared -Wall -Wl,-soname,$(LIBNAME) -o $(LIBNAME) $(LDIR) $(LIBS) $(OBJS)

clean:
	rm -f *.o $(LIBNAME)
