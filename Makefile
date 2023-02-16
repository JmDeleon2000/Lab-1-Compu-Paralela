.PHONY = all clean

CC = g++			

OMPFLAG = -fopenmp

SOURCES = $(wildcard *.c)
OBJECTS = $(patsubst %.c,%,$(SOURCES))


all: ${OBJECTS}

%: %.c
	${CC} ${OMPFLAG} -o $@.o $<


clean:
	@echo "Cleaning up..."
	rm -rvf *.o ${BINS}