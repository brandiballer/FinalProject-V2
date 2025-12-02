CC	:= gcc
CFLAGS	:= -Wall -Wextra -Wpedantic -std=c11

TARGET	:= employee_management
SRC	:= employee_management.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET) *.o