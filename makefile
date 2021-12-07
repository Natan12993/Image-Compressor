#VPATH= src include bin
CC=gcc
CFLAGS=-ansi -Wall -pedantic
LIB=-lMLV -lm
BINP=bin/
SRCP=src/
EXEC=qdc

vpath %.c src
vpath %.o bin
vpath %.h include

OBJS= $(subst .c,.o,$(notdir $(wildcard $(SRCP)*)))
#$(info    OBJS is $(OBJS))

$(EXEC): $(OBJS)
	gcc $(CFLAGS) -o $@ $(addprefix $(BINP),$(OBJS)) $(LIB)

main.o: main.c interface.h option.h

option.o: option.c option.h

comp.o: comp.c comp.h quadtree.h

graphic.o: graphic.c graphic.h quadtree.h

interface.o: interface.c interface.h quadtree.h comp.h save.h open.h

quadtree.o: quadtree.c quadtree.h

save.o: save.c save.h quadtree.h comp.h

open.o: open.c open.h quadtree.h comp.h

%.o: %.c
	$(CC) -o $(BINP)$@ -c $< $(CFLAGS)



clean:
	rm -f $(BINP)*.o
	rm -f $(EXEC)

