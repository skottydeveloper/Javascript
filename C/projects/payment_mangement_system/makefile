#makefile for the Payment System, run SecurePayroll to use

CC = gcc 
CFLAGS  = -Wall -Werror -ansi -lm

SecurePayroll.out: menu.o linkedListSource.o compression.o encryption.o
	$(CC) $(CFLAGS) -o SecurePayroll.out menu.o linkedListSource.o compression.o encryption.o

compression.o: compression.c
	$(CC) $(CFLAGS) -c -o compression.o compression.c 

encryption.o: encryption.c linkedListSource.h compression.h
	$(CC) $(CFLAGS) -c -o encryption.o encryption.c 

linkedlistSource.o: linkedListSource.c linkedListSource.h compression.h
	$(CC) $(CFLAGS) -c -o linkedListSource.o linkedListSource.c 

menu.o: menu.c linkedListSource.h encryption.h
	$(CC) $(CFLAGS) -c -o menu.o menu.c 

clean:
	rm linkedListSource.o menu.o encryption.o compression.o SecurePayroll.out