CC = gcc
OD = objdump
LD = ld

SRC_PATH = ../src
PRE_COMPILATION_FLAGS = -Wall -O3 -g -Xlinker
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
FLAGS += $(INCLUDE) $(PRE_COMPILATION_FLAGS)

fft:	clean
	$(CC) $(FLAGS) -Map=$(OUTPUT1).map $(SRC1) -o $(OUTPUT1).out $(POST_COMPILATION_FLAGS)
	$(OD) -S $(OUTPUT1).out > $(OUTPUT1).asm

sin_wave:	clean
	$(CC) $(FLAGS) -Map=$(OUTPUT1).map $(SRC2) -o $(OUTPUT2).out $(POST_COMPILATION_FLAGS)
	$(OD) -S $(OUTPUT2).out > $(OUTPUT2).asm

clean:
	rm -f *.map
	rm -f *.out
	rm -f *.asm
