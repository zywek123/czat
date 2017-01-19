CC = gcc
CXX = g++
CCFLAGS = -pthread -O2 -std=gnu99
LIBS = -lc -lmysqlclient  -lgadu -lcrypto -lglib-2.0
OBJS =\
cmd.o \
functions.o \
main.o \
minIni.o
all: main
clean:
	rm -f *.o
	rm -f czat
.c.o:
	$(CC) -c $(CCFLAGS) $<
.cpp.o:
	$(CXX) -c $(CCFLAGS) $<
main: $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o czat
