CC=sdcc
AR=sdar
CFLAGS=-c -mstm8 -DSTM8S105 -DSDCC -I ../inc --opt-code-size
LDFLAGS=-rc 
#SOURCES=stm8s_flash.c stm8s_uart2.c stm8s_tim4.c stm8s_clk.c stm8s_itc.c
SOURCES=stm8s_minilib.c
OBJECTS=$(SOURCES:.c=.o)
OBJECTS_LINK=$(SOURCES:.c=.rel)
EXECUTABLE=stm8s_minilib.lib

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(AR) $(LDFLAGS) $(EXECUTABLE) $(OBJECTS_LINK) 

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean: 
	rm *.lib
	rm *.rst
	rm *.rel
	rm *.lst
	rm *.ihx
	rm *.sym
	rm *.asm
	rm *.lk
	rm *.map
	rm $(EXECUTABLE)
