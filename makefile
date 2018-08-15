###########################################
#Makefile for simple programs
###########################################
INC=
LIB= -lpthread
 
CC=CC
CC_FLAG=-Wall -std=c++11
PRG=ordermanager
OBJ=main.o 
CC=g++

$(PRG):$(OBJ)
	$(CC) $(INC) $(LIB) -o $@ $(OBJ)

.SUFFIXES: .o .cpp

.cpp.o:
	$(CC) $(CC_FLAG) $(INC) -c $*.cpp -o $*.o

.PRONY:clean
clean:
	@echo "Removing linked and compiled files......"
	rm -f $(OBJ) $(PRG)
