CC=gcc
source_dir=source
path_program=build/
name_program=program
OS=Linux
IDIR=include
ODIR=build/obj

CFLAGS=-I$(IDIR)
LIBS=-lm

_DEPS = main.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
install-dependencies-Linux:
	mkdir -p temp
	cd temp
	wget https://github.com/glfw/glfw/releases/download/3.3.4/glfw-3.3.4.zip
	
install-dependencies: install-dependencies-$(OS)
	

init: install-dependencies
	mkdir -p build/obj
	
$(ODIR)/%.o: $(source_dir)/%.c $(DEPS) init
	$(CC) -c -o $@ $< $(CFLAGS)

build: $(OBJ)
	$(CC) -o $(path_program)$(name_program) $^ $(CFLAGS) $(LIBS)
all:: build
clear:
	rm -rf build/*
	rm -f $(path_program)$(name_program)
run: build
	./build/program