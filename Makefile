TARGET = TextEditor
CC = gcc

$(TARGET) : main.o append_buffer.o file_io.o init.o input.o output.o row_operations.o terminal.o editor_operations.o
	$(CC) main.o append_buffer.o file_io.o init.o input.o output.o row_operations.o terminal.o editor_operations.o -o $(TARGET)

main.o : main.c
	$(CC) -c main.c -o main.o

append_buffer.o : append_buffer.c
	$(CC) -c append_buffer.c -o append_buffer.o

file_io.o : file_io.c
	$(CC) -c file_io.c -o file_io.o

init.o : init.c
	$(CC) -c init.c -o init.o

input.o : input.c
	$(CC) -c input.c -o input.o

output.o : output.c
	$(CC) -c output.c -o output.o

row_operations.o : row_operations.c
	$(CC) -c row_operations.c -o row_operations.o

terminal.o : terminal.c
	$(CC) -c terminal.c -o terminal.o

editor_operations : editor_operations.c
	$(CC) -c editor_operations.c -o editor_operations.o

clean : 
	rm $(TARGET) *.o 


