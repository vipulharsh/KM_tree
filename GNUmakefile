# Configuration ################################################################

CC = gcc
CFLAGS = -Wall
INCLUDES = -I.




# Project Paths
PROJECT_ROOT=$(HOME)/Desktop/KM_tree
EXTERNAL_ROOT=$(PROJECT_ROOT)
SRCDIR = $(PROJECT_ROOT)
OBJDIR = $(PROJECT_ROOT)/objs






# Main #########################################################################

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)
DEPS = $(SRCS:%.c=%.d)
SRCS = main.c marking.c tree.c petrinet.c covtree.c list_nodes.c
EXE = kmt



.PHONY: all clean setup

all: setup $(OBJDIR)/$(EXE)



setup:
	@mkdir -p $(OBJDIR)



$(OBJDIR)/$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

%.d: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -MM $< > $@

clean:
	@rm -rf $(EXE) $(OBJDIR) $(DEPS) *.o

-include $(DEPS)
