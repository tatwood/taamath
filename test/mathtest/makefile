EXE=../bin/mathtest
EXED=../bin/mathtestd
OBJS=obj/make.o
OBJSD=objd/make.o
INCLUDES=-I../../include -I../../../taasdk/include
LIBS=-lm
CC=gcc
CCFLAGS=-Wall -msse3 -O3 -fno-exceptions $(INCLUDES)
CCFLAGSD=-Wall -msse3 -O0 -ggdb2 -fno-exceptions -D_DEBUG $(INCLUDES)
LD=gcc
LDFLAGS=$(LIBS)

$(EXE): obj ../bin $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXE)

$(EXED): objd ../bin $(OBJSD)
	$(LD) $(OBJSD) $(LDFLAGS) -o $(EXED)

obj:
	mkdir obj

objd:
	mkdir objd

../bin:
	mkdir ../bin

obj/make.o : make.c
	$(CC) $(CCFLAGS) -c $< -o $@

objd/make.o : make.c
	$(CC) $(CCFLAGSD) -c $< -o $@

all: $(EXE) $(EXED)

clean:
	rm -rf $(EXE) $(EXED) obj objd

debug: $(EXED)

release: $(EXE)
