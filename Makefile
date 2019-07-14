CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c99
ifeq ($(debug), 1)
	CFLAGS = -Iinclude -Wall -std=c99 -g --debug
endif
HENC = hencode 
HENC_OBJS = hencode.o huffman.o 
HDEC = hdecode
HDEC_OBJS = hdecode.o huffman.o 
HASH = htable
HASH_OBJS = htable.o huffman.o 

all : $(HENC) $(HDEC) $(HASH)

$(HENC) : $(HENC_OBJS) huffman.h 
	$(CC) $(CFLAGS) -o $(HENC) $(HENC_OBJS) -lm

$(HASH) : $(HASH_OBJS) huffman.h 
	$(CC) $(CFLAGS) -o $(HASH) $(HASH_OBJS) -lm	

hencode.o : hencode.c huffman.c 
	$(CC) $(CFLAGS) -c hencode.c

huffman.o : huffman.c huffman.h 
	$(CC) $(CFLAGS) -c huffman.c


$(HDEC) : $(HDEC_OBJS) huffman.h 
	$(CC) $(CFLAGS) -o $(HDEC) $(HDEC_OBJS) -lm

hdecode.o : hdecode.c huffman.c
	$(CC) $(CFLAGS) -c hdecode.c

htable.o : htable.c huffman.c
	$(CC) $(CFLAGS) -c htable.c	

clean :
	rm *.o $(HENC) $(HDEC) $(HASH)
