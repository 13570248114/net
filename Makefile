all:libnet.a

%.o:%.cc %.c
	g++ -c *.cc -std=c++17
	g++ -c *.c

libnet.a:*.o
	ar cr libnet.a *.o

test:libnet.a *.cpp
	g++ *.cpp libnet.a -std=c++17 -o test -lpthread

.PHONY:clean
clean:
	rm *.o
