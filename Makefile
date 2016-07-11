
CC := g++
DEBUG :=

ifdef DEBUG
DEBUGFLAG := -DDSDEBUG
endif


main : main.o FileLock.o FileRemoveDetect.o
	$(CC) $(DEBUGFLAG) -o main main.o FileLock.o FileRemoveDetect.o

FileLock.o : FileLock/FileLock.cpp
	$(CC) $(DEBUGFLAG) -c FileLock/FileLock.cpp

FileRemoveDetect.o : FileRemoveDetect/FileRemoveDetect.cpp
	$(CC) $(DEBUGFLAG) -c FileRemoveDetect/FileRemoveDetect.cpp


clean:
	rm *.o main
