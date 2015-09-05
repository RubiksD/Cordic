CC = gcc
COMPILATION_FLAGS = -Wall -O3 
OUTPUT1 = cordic_rotate

SRC = ../src/main.c\
			../src/fft.c\
			../src/cordic.c

rotate:	clean
	$(CC) $(COMPILATION_FLAGS) $(SRC) -o $(OUTPUT1) -lm

clean:
	rm -f $(OUTPUT1)
