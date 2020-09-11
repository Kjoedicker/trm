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
	$(CC) -c $^

object: data_initializers.o file_manipulation.o program_flow.o str_manipulation.o path_manipulation.o main.c
	$(CC) -g -o $(PROG_NAME) $^

val: object
	valgrind --leak-check=full ./$(PROG_NAME)

gdb: object
	grdb ./$(PROG_NAME)


BRANCH := $(shell eval 'git branch --show-current')

git:
	git add .
	git commit -F commit.txt
	git push origin $(shell eval 'git branch --show-current')
	echo > commit.txt

clean:
	rm *.o








	
		 



	


	
	