CC = gcc

COMMON=../00_common
SQLITE_COMMON=../../02_common

TARGET=test

FILES=test.c  $(COMMON)/log/log.c
INC = -I$(SQLITE_COMMON)/include/ -I$(COMMON)/log/

LIB = -L$(SQLITE_COMMON)/lib  -lsqlite3

test:
	make clean
	$(CC)  $(FILES) -g  $(LIB) $(INC) -o $(TARGET)
	cp test.db_back test.db
	make exe

clean:
	rm -rf $(TARGET)
	rm -rf test.db

exe:
	LD_LIBRARY_PATH="$(SQLITE_COMMON)/lib" ./$(TARGET)


.PHONY:test
	
