CC = gcc
CXX = g++
CFLAGS = --std=c++17 -fpermissive -g
CSOURCES = mailbox.c ws2811.c pwm.c pcm.c dma.c rpihw.c other.c
CPPSOURCES = Color.cpp main.cpp
OBJSC = $(subst .c,.o,$(CSOURCES))
OBJSCXX = $(subst .cpp,.o,$(CPPSOURCES))

%.o : %.c
	$(CC) -c $<
	
%.o : %.cpp
	$(CXX) -c $(CFLAGS) $<


run: $(OBJSC) $(OBJSCXX) 
	${CXX} -o $@ $^ -pthread -ldl
	

clean:
	rm *.o
	rm run
