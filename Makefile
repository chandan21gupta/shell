CC = gcc
TARGET = shell
all : $(TARGET)
$(TARGET): $(TARGET).c
	$(CC) -o $(TARGET) $(TARGET).c
clean:
	$(RM) $(TARGET)

