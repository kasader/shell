CC = gcc
CFLAGS = -g -Wall -Wvla -Werror -Wno-error=unused-variable
TARGET = shell

all: $(TARGET) 

$(TARGET) : $(TARGET).c  parse.o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c parse.o

test: test.c parse.o
	$(CC) $(CFLAGS) -o test test.c parsecmd.o

parse.o: parse.c
	$(CC) $(CFLAGS) -c parse.c

clean:
	$(RM) $(TARGET) parse.o test
