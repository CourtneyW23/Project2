target := testsim
SRCS := testsim.c
objs := $(SRCS:.c=.o)

target2 := shared
SRCS2 := shared.c
objs2 := $(SRCS2:.c=.o)

target3 := runsim
SRCS3 := runsim.c
objs3 := $(SRCS3:.c=.o)


CC := gcc
CFLAGS := -Wall

all: $(target) $(target2) $(target3)

deps := $(patsubst %.o, %.d, $(objs), $(objs2), $(objs3))
-include $(deps)
DEPFLAGS = -MMD -MF $(@:.o=.d)

target3: $(objs3)
	$(CC) $(CFLAGS) -o $@ $^

target2: $(objs2)
	$(CC) $(CFLAGS) -o $@ $^

target: $(objs)
	$(CC) $(CFLAGS) -o $@ $^

%o: %.c 
	$(CC) $(CFLAGS) -c $< $(DEPFLAGS)

clean:
	rm -f $(target) $(target2) $(target3) $(deps)

.PHONY: all clean
