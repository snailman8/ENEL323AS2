LIBS = -lfltk -lXext -lXft -lfontconfig -lXinerama -lpthread -ldl -lm -lX11 -L$(IBASE)/lib -Wl,--start-group -lapr -laprutil -lasl -lgsl3 -lgsl -licl -lipr -lopf -lpcre -lsfl -lsmt3 -lsmt -lzip -lrt -lcrypt -lpthread -lm  -Wl,--end-group -L/opt/OpenAMQ/lib
LDPATH = -L/usr/local/lib 
CPP = gcc
INC = -I. -I/usr/local/include -I$(IBASE)/include -I/opt/OpenAMQ/include
CFLAGS = -c -Wno-write-strings


all: 			circ_buffer_tester


circ_buffer_tester:	double_buffer.o main.o
			$(CPP) -o main double_buffer.o main.o $(LDPATH) $(LIBS)
double_buffer.o:	double_buffer.c double_buffer.h
			$(CPP) $(CFLAGS) $(INC) double_buffer.c double_buffer.h

main.o:			main.c double_buffer.h
			$(CPP) $(CFLAGS) $(INC) main.c double_buffer.h

clean:	
			rm -f *.o main *.h.gch
