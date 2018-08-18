###########################################
#Makefile for simple programs
###########################################
INC=
LIB=-lpthread
CC_FLAG=-Wall -std=c++11
TRADER=trader
TRADEROBJ = ../trader_main.o
ROUTER=router
ROUTEROBJ = ../orderrouter_main.o

OBJ= ../orderrouter.o ../ordermanager.o ../trader.o ../exchange.o ../server.o
CC=g++
all:$(ROUTER) $(TRADER)

$(TRADER):$(OBJ) $(TRADEROBJ)
	$(CC) $(INC) $(LIB) -o $@ $(OBJ) $(TRADEROBJ)

$(ROUTER):$(ROUTEROBJ) $(OBJ)
	$(CC) $(INC) $(LIB) -o $@ $(OBJ) $(ROUTEROBJ)

.SUFFIXES: .o .cpp

.cpp.o:
	$(CC) $(CC_FLAG) $(INC) -c $*.cpp -o $*.o 

.PRONY:clean
clean:
	@echo "Removing linked and compiled files......"
	rm -f $(OBJ) $(TRADEROBJ) $(ROUTEROBJ) $(all)
