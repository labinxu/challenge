###########################################
#Makefile for simple programs
###########################################
INC=
LIB=-lpthread
CC_FLAG=-Wall -std=c++11
EXCHANGE=exchange
EXCHANGEOBJ=../exchange_main.o

TRADER=trader
TRADEROBJ = ../trader_main.o
ROUTER=router
ROUTEROBJ = ../orderrouter_main.o
TESTER=test
TESTEROBJ=test_challenge.o

OBJ= ../orderrouter.o ../ordermanager.o  ../server.o

CC=g++
TARGETS = $(ROUTER) $(TRADER) $(EXCHANGE) $(TESTER)

all:$(ROUTER) $(TRADER) $(EXCHANGE) $(TESTER)
$(TESTER):$(TESTEROBJ)
	$(CC) $(INC) $(LIB) -g -o $@ $(TESTEROBJ) $(OBJ)

$(TRADER):$(OBJ) $(TRADEROBJ)
	$(CC) $(INC) $(LIB) -o $@ $(OBJ) $(TRADEROBJ)

$(ROUTER):$(ROUTEROBJ) $(OBJ)
	$(CC) $(INC) $(LIB) -o $@ $(OBJ) $(ROUTEROBJ)

$(EXCHANGE):$(EXCHANGEOBJ) $(OBJ)
	$(CC) $(INC) $(LIB) -o $@ $(OBJ) $(EXCHANGEOBJ)

.SUFFIXES: .o .cpp

.cpp.o:
	$(CC) $(CC_FLAG) $(INC) -g -c $*.cpp -o $*.o 

.PRONY:clean
clean:
	@echo "Removing linked and compiled files......"
	rm -f $(OBJ) $(TRADEROBJ) $(ROUTEROBJ) $(TARGETS)
