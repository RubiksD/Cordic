CC = gcc
OD = objdump
LD = ld

SRC_PATH = ../src
PRE_COMPILATION_FLAGS = -Wall -O3 -g
POST_COMPILATION_FLAGS = -lm
OUTPUT1 = cordic_fft
OUTPUT2 = cordic_sin_wave
INCLUDE = -I ../include

SRC_COMMON = 	$(SRC_PATH)/fft.c\
							$(SRC_PATH)/cordic.c
SRC1	=	$(SRC_PATH)/main.c\
				$(SRC_COMMON)

SRC2	=	$(SRC_PATH)/sin_wave.c\
				$(SRC_COMMON)

#FLAGS += -DMEASURE_TIME
FLAGS += -DDISPLAY_OUTPUT
#FLAGS += -DDOUBLE_CALCULATIONS

fft:	clean
	$(CC) $(PRE_COMPILATION_FLAGS) $(INCLUDE) $(SRC1) $(FLAGS) -o $(OUTPUT1).out $(POST_COMPILATION_FLAGS)
	$(OD) -S $(OUTPUT1).out > $(OUTPUT1).asm

sin_wave:	clean
	$(CC) $(PRE_COMPILATION_FLAGS) $(INCLUDE) $(SRC2) $(FLAGS) -o $(OUTPUT2).out $(POST_COMPILATION_FLAGS)
	$(OD) -S $(OUTPUT2).out > $(OUTPUT2).asm

clean:
	rm -f *.out
	rm -f *.asm
