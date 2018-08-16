###########################################
#Makefile for simple programs
###########################################
INC=
LIB=
#-lpthread
CC_FLAG=-Wall -std=c++11
PRG=test
OBJ=main.o test_orderidentifier.o ../types.o
CC=clang++

$(PRG):$(OBJ)
	$(CC) $(INC) $(LIB) -o $@ $(OBJ)

.SUFFIXES: .o .cpp

.cpp.o:
	$(CC) $(CC_FLAG) $(INC) -c $*.cpp -o $*.o

.PRONY:clean
clean:
	@echo "Removing linked and compiled files......"
	rm -f $(OBJ) $(PRG)
