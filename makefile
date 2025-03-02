CC = gcc
SRC = ./src/SimpleOffsetExplorer.c
TARGET = SimpleOffsetExplorer.a
OUT = SimpleOffsetExplorer.o


$(TARGET) : $(OUT)
	ar rcs ./bin/$(TARGET) ./bin/$(OUT)


$(OUT) : $(SRC)
	$(CC) -c $(SRC) -o ./bin/$(OUT)

all : $(TARGET)


clean:
	rm -f ./bin/*