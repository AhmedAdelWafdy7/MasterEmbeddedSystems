# perbared by Ahmed Adel Wafdy
CC=arm-none-eabi-
CFLAGS= -mcpu=cortex-m4 -gdwarf-2 -g
INCS=-I .
LIBS=
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
As = $(wildcard *.s)
AsOBJ = $(As:.s=.o)
Project_name=Pressure_Controller
all: $(Project_name).hex
	@echo "=============Build is Done============"


%.o: %.c
	$(CC)gcc.exe -c $(CFLAGS) $(INCS)  $< -o $@

$(Project_name).elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(AsOBJ) -o $@ -Map=map_file.map
	cp $(Project_name).elf $(Project_name).axf
$(Project_name).hex: $(Project_name).elf
	$(CC)objcopy.exe -O binary $< $@
clean:
	rm -rf *.o *~ *.elf *.hex
	@echo "Everything is clean"	