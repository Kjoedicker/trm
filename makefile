qCC=clang
CFLAGS=-I.
                                                                                          
HEADER_DIR = src/header/%.h
SOURCE_DIR = src/source/%.c 

OBJ_DIR = $(OBJ_DIR)/%.c
OBJ_PWD = src/obc/

PROG_NAME = trm

all: object clean

%.o: $(SOURCE_DIR)
	$(CC) -g -c $^

object: initlib.o filelib.o flowcontrol.o toollib.o parselib.o main.c
	$(CC) -g -o $(PROG_NAME) $^

clean:
	-rm *.o

clean-all:
	-rm *.o
	-rm *vgcore*


	
		 



	


	
	
