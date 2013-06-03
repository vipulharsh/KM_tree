# Configuration ################################################################

CC = gcc
CFLAGS = -Wall
INCLUDES = -I.

SRCS = main.c marking.c tree.c
EXE = kmt



# Project Paths
PROJECT_ROOT=$(HOME)/Desktop/KM_tree
EXTERNAL_ROOT=$(PROJECT_ROOT)/external
SRCDIR = $(PROJECT_ROOT)/src
OBJDIR = $(PROJECT_ROOT)/myobjs



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
