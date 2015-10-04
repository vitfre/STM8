CC=sdcc
CFLAGS=-mstm8 
INCLUDEPATH=STM8S_StdPeriph_Lib_V2.1.0/Libraries/STM8S_StdPeriph_Driver/inc/
DEFINES= STM8S003
SOURCE=leds
OUTPUT_DIR=build/
all: flash

compile:
	mkdir -p $(OUTPUT_DIR)
	$(CC) $(CFLAGS) -I $(INCLUDEPATH) -D $(DEFINES) -o $(OUTPUT_DIR) $(SOURCE).c 

prepare:
	packihx $(OUTPUT_DIR)/$(SOURCE).ihx > $(OUTPUT_DIR)/$(SOURCE).hex	

clean:
	rm -Rrf $(OUTPUT_DIR)

erase:
	vsprog -cstm8s103f3 -ms -oe -V"tvcc.set 3300"
	vsprog -V"tvcc.set 0" -V"tvcc.set 3300"

flash: compile prepare erase
	vsprog -cstm8s103f3 -ms -owf -I $(OUTPUT_DIR)/$(SOURCE).hex -V"tvcc.set 3300"
	vsprog -V"tvcc.set 0" -V"tvcc.set 3300"
