CC = gcc
COMPILATION_FLAGS = -Wall -O3 
OUTPUT1 = cordic_rotate

SRC = ../src/main.c\
			../src/fft.c\
			../src/cordic.c

FLAGS = -DMEASURE_TIME
FLAGS += -DDISPLAY_OUTPUT

rotate:	clean
	$(CC) $(COMPILATION_FLAGS) $(SRC) $(FLAGS) -o $(OUTPUT1) -lm

clean:
	rm -f $(OUTPUT1)
