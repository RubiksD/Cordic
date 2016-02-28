CC = gcc
OD = objdump
LD = ld
NM = nm
AR = ar
RANLIB = ranlib

AR_FLAGS = rc

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
FLAGS += $(INCLUDE) $(PRE_COMPILATION_FLAGS)

fft:	clean
	$(CC) $(FLAGS) $(SRC1) -o $(OUTPUT1).out $(POST_COMPILATION_FLAGS)
	$(NM) -n $(OUTPUT1).out > $(OUTPUT1).map
	$(OD) -S $(OUTPUT1).out > $(OUTPUT1).asm

sin_wave:	clean
	$(CC) $(FLAGS) $(SRC2) -o $(OUTPUT2).out $(POST_COMPILATION_FLAGS)
	$(NM) -n $(OUTPUT2).out > $(OUTPUT2).map
	$(OD) -S $(OUTPUT2).out > $(OUTPUT2).asm

library:	clean
	$(CC) $(SRC_COMMON) -c $(FLAGS)
	$(AR) $(AR_FLAGS) libcordic_fft.a *.o
	$(RANLIB) libcordic_fft.a
	cp -f libcordic_fft.a ../lib

clean:
	rm -f *.map
	rm -f *.out
	rm -f *.asm
	rm -f *.a
	rm -f *.o
