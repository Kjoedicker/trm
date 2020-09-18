qCC=clang
CFLAGS=-I.
                                                                                          
HEADER_DIR = src/header/%.h
SOURCE_DIR = src/source/%.c 

OBJ_DIR = $(OBJ_DIR)/%.c
OBJ_PWD = src/obc/

OBJS = 

test = $(shell ls src/header)

PROG_NAME = trm

all: object clean

%.o: $(SOURCE_DIR)
	$(CC) -g -c $^

object: initlib.o filelib.o flowcontrol.o toollib.o parselib.o main.c
	$(CC) -g -o $(PROG_NAME) $^

val: object
	valgrind --leak-check=full ./$(PROG_NAME) -V

gdb: object
	grdb ./$(PROG_NAME)

BRANCH := $(shell eval 'git branch --show-current')

git:
	git add .
	git commit -F commit.txt
	git push origin $(shell eval 'git branch --show-current')
	echo "" > commit.txt


ls:
	ls ~/.trash

vi:
	vim ~/.trash

test-rm:
	-rm 1 2 3 4 5
	touch 1 2 3 4 5
	./trm 1 2 3 4 5
	./trm -V

test-rm1:
	-rm 1
	touch 1
	./trm 1
	./trm -V

test-r:
	./trm -r 1 2 3 4 5

nav: 
	vim ~/.trash
	
clean:
	-rm *.o

clean-all:
	-rm *.o
	-rm *vgcore*

maker:
	make
	make test-rm
	make test-r


	
		 



	


	
	