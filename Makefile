CC = g++
FLAGS = -O3 -Wall -Werror
LIBS = $(shell pkg-config --cflags --libs python3)

all: airy
	$(CC) $(FLAGS) -o airy.out main.cc $(LIBS) airy.o

airy:
	$(CC) $(FLAGS) -c airy.cc $(LIBS)
