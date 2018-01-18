CC = gcc
CFLAGS = -std=c99 -O3
LDFLAGS = 
DEBUG_FLAGS = -W -Wall -g
SRC = 
OBJS = 
DEBUG = 
GPROF = 

# Command line arguments
ifeq ($(DEBUG),ON)
	CFLAGS +=  $(DEBUG_FLAGS)
endif

ifeq ($(GPROF),ON)
	CFLAGS += -pg
endif

all : product product_avx

product : product.o 
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

product_avx : CFLAGS += -mfma -mavx 
product_avx : product_avx.o 
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)


%.o : %.c %.h
	$(CC) $(CFLAGS) -c $<

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	@rm -f product product_avx *.o *~ gmon.out
