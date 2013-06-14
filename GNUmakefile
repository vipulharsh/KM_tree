# Configuration ################################################################

CC = gcc
CFLAGS = -Wall
INCLUDES = -I.

# Project Paths
PROJECT_ROOT ?= $(CURDIR)
SRCDIR = $(PROJECT_ROOT)
OBJDIR = $(PROJECT_ROOT)/objs



# Main #########################################################################

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)
DEPS = $(SRCS:%.c=$(OBJDIR)/%.d)
SRCS = main.c marking.c tree.c petrinet.c covtree.c list_nodes.c
EXE = kmt

.PHONY: all clean

all: $(OBJDIR)/$(EXE)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/$(EXE): $(OBJS) $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(OBJDIR)/%.d: $(SRCDIR)/%.c $(OBJDIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -MM $< > $@

clean:
	@rm -rf $(OBJDIR)

-include $(DEPS)
