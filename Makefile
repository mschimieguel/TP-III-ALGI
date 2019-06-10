COMPILER := gcc
SRCDIR := src
TSTDIR := tests
OBJDIR := build
BINDIR := bin

MAIN := program/main.c
TESTER := program/tester.c

LANGUAGE := c
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(LANGUAGE))
OBJECTS := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.$(LANGUAGE)=.o))
TSTSOURCES := $(shell find $(TSTDIR) -type f -name *.$(LANGUAGE))

# -g debug, --coverage para cobertura
FLAGS := --coverage -Wall -pedantic -ansi -std=c11
INC := -I include/ -I third_party/
INC_MATH := -lm

$(OBJDIR)/%.o: $(SRCDIR)/%.$(LANGUAGE)
	@mkdir -p $(@D)
	$(COMPILER) $(FLAGS) $(INC)  -c -o $@  $< 

tp3: $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(COMPILER) $(FLAGS) $(INC) $(MAIN) $^ -o $(BINDIR)/tp3 $(INC_MATH)

tests: $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(COMPILER) $(FLAGS) $(INC) $(TESTER) $(TSTSOURCES) $^ -o $(BINDIR)/tester 
	$(BINDIR)/tester

all: tp3

run: tp3
	$(BINDIR)/tp3

coverage:
	@mkdir -p coverage/
	@gcov $(SOURCES) -rlpo build/
	@$(RM) *.gcda *.gcno

clean:
	$(RM) -r $(OBJDIR)/* $(BINDIR)/* coverage/* *.gcda *.gcno

.PHONY: clean coverage
