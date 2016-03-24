# makefile for Computer_Architecture_Project_1

CC := g++
CFLAGS := -std=c++11 -O3 -Wall -fmessage-length=0
OBJS := InstDataBin.o InstDataStr.o InstDecode.o InstErrorDetector.o \
        InstImageReader.o InstLookUp.o InstMemory.o InstSimulator.o \
        InstUtility.o main.o

.SUFFIXS:
.SUFFIXS: .cpp .o

.PHONY: clean

all: ${OBJS}
	${CC} ${CFLAGS} -o main ${OBJS}

.cpp.o:
	${CC} ${CFLAGS} -c $<

clean:
	-rm -f *.o main
