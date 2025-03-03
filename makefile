CC = gcc
ARCH = 64
SRC = ./src/SimpleOffsetExplorer.c
OUT = SimpleOffsetExplorer.o


ifeq ($(ARCH), 64)
    TARGET = SimpleOffsetExplorerx64.a
else ifeq ($(ARCH), 32)
    TARGET = SimpleOffsetExplorerx32.a
else
    $(error Unknown architecture use ARCH=64 or ARCH=32: $(ARCH))
endif


$(shell mkdir -p bin)


$(TARGET) : $(OUT)
	ar rcs ./bin/$(TARGET) ./bin/$(OUT)


$(OUT) : $(SRC)
	$(CC) -m$(ARCH) -c $(SRC) -o ./bin/$(OUT)


all : $(TARGET)


clean:
	rm -f ./bin/*