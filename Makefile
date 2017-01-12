CC = gcc
CXX = g++
CCFLAGS = -pthread -O2 -g
LIBS = -lc -lmysqlclient  -lgadu -lcrypto
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
