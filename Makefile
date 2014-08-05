P=bloom_example
OBJECTS=bloom.o
CFLAGS=`pkg-config --cflags glib-2.0` -g -Wall -std=gnu11 -O3
LDLIBS=`pkg-config --libs glib-2.0`
CC=cc

$(P): $(OBJECTS)


