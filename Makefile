target := testsim
SRCS := testsim.c
objs := $(SRCS:.c=.o)

target2 := runsim
SRCS2 := runsim.c
objs2 := $(SRCS2:.c=.o)

CC := gcc
CFLAGS := -Wall

all: $(target2) $(target)

deps := $(patsubst %.o, %.d, $(objs2), $(objs))
-include $(deps)
DEPFLAGS = -MMD -MF $(@:.o=.d)

target2: $(objs2)
	$(CC) $(CFLAGS) -o $@ $^

target: $(objs)
	$(CC) $(CFLAGS) -o $@ $^

%o: %.c 
	$(CC) $(CFLAGS) -c $< $(DEPFLAGS)

clean:
	rm -f $(target2) $(objs2) $(target) $(objs) $(deps)

.PHONY: all clean
