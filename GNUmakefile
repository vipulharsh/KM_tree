# Configuration ################################################################

CC = gcc
CFLAGS = -Wall
INCLUDES = -I.

SRCS = main.c marking.c
EXE = kmt

# Main #########################################################################

OBJS = $(SRCS:%.c=%.o)
DEPS = $(SRCS:%.c=%.d)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

%.d: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -MM $< > $@

clean:
	rm -f $(EXE) $(OBJS) $(DEPS)

-include $(DEPS)
