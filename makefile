LIBS = -lXext -lXft -lfontconfig -lXinerama -lpthread -ldl -lm -lX11 -L$(IBASE)/lib -Wl,--start-group -lapr -laprutil -lasl -lgsl3 -lgsl -licl -lipr -lopf -lpcre -lsfl -lsmt3 -lsmt -lzip -lrt -lcrypt -lpthread -lm  -Wl,--end-group -L/opt/OpenAMQ/lib
LDPATH = -L/usr/local/lib 
CPP = gcc
INC = -I. -I/usr/local/include -I$(IBASE)/include
CFLAGS = -c -Wno-write-strings


all: 			main


main:	 		double_buffer.o
			$(CPP) -o main double_buffer.o $(LDPATH) $(LIBS)

double_buffer.o:	double_buffer.c double_buffer.h
			$(CPP) $(CFLAGS) $(INC) double_buffer.c double_buffer.h

clean:	
			rm -f *.o main *.h.gch
