# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all:pong.elf

#additional rules for files
pong.elf: ${COMMON_OBJECTS} main.o wdt_handler.o buzzer.o led.o stateMachines.o play.o ballAdvance.o colorAdvance.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd -lp2sw

load: pong.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf
