# Configuration ################################################################

CC = gcc -g
CFLAGS = -Wall -DDEBUG
INCLUDES = -I.

# Project Paths
PROJECT_ROOT ?= $(CURDIR)
SRCDIR = $(PROJECT_ROOT)
OBJDIR = $(PROJECT_ROOT)/objs
DOCDIR = $(PROJECT_ROOT)/doc
RESDIR = $(PROJECT_ROOT)/results

# Main #########################################################################

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)
DEPS = $(SRCS:%.c=$(OBJDIR)/%.d)
SRCS = main.c marking.c tree.c petrinet.c covtree.c list_nodes.c
EXE = kmt

.PHONY: all clean doc

all: $(OBJDIR)/$(EXE)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/$(EXE): $(OBJS) | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(OBJDIR)/%.d: $(SRCDIR)/%.c | $(OBJDIR)
	@(echo -n $(OBJDIR)/ ; \
	  $(CC) $(CFLAGS) $(INCLUDES) -MM $< ) > $@
doc:
	@latex $(DOCDIR)/pda.tex
	@dvipdf $(PROJECT_ROOT)/pda.dvi $(DOCDIR)/pda.pdf
	@rm -rf $(PROJECT_ROOT)/pda.*


dot: $(RESDIR)/tree.dot
	@dot -Tpdf $(RESDIR)/tree.dot > $(RESDIR)/tree.pdf

clean:
	@rm -rf $(OBJDIR)

-include $(DEPS)
