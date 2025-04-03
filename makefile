CC = gcc
ARCH = 64
SRC = ./src/SimpleOffsetExplorer.c
OUT = SimpleOffsetExplorer.o 
TARGET = SimpleOffsetExplorerX$(ARCH)


$(shell mkdir -p bin)


dynamic :
	$(CC) -Wall -shared -o ./bin/$(TARGET).dll $(SRC) -m$(ARCH) -luser32 -lkernel32


static : $(OUT)
	ar rcs ./bin/$(TARGET).a ./bin/$(OUT)

$(OUT) : $(SRC)
	$(CC) -Wall -m$(ARCH) -c $(SRC) -o ./bin/$(OUT)


clean :
	rm -f ./bin/*