CC=gcc
source_dir=src
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
GLFW_VERSION=3.3.4
CMAKE_VERSION=3.21.3
init:
	mkdir -p build/obj
	mkdir -p build/temp
	mkdir -p build/cmake

build/temp/glfw-$(GLFW_VERSION)/:
	cd build/temp/ \
	&& wget https://github.com/glfw/glfw/releases/download/$(GLFW_VERSION)/glfw-$(GLFW_VERSION).zip \
	&& unzip glfw-$(GLFW_VERSION).zip \
	&& rm -f glfw-$(GLFW_VERSION).zip

build/cmake/bin/cmake:
	cd build/temp \
	&& wget https://github.com/Kitware/CMake/releases/download/v$(CMAKE_VERSION)/cmake-$(CMAKE_VERSION)-linux-x86_64.sh \
	&& chmod +x cmake-$(CMAKE_VERSION)-linux-x86_64.sh \
	&& ./cmake-$(CMAKE_VERSION)-linux-x86_64.sh --skip-license --prefix=../cmake/ \
	&& rm -f cmake-$(CMAKE_VERSION)-linux-x86_64.sh*
build/cmake/src/Makefile: build/cmake/bin/cmake build/temp/glfw-$(GLFW_VERSION)/
	cd build/cmake \
	&& bin/cmake ../temp/glfw-$(GLFW_VERSION)/ 
/usr/local/lib/libglfw3.a: build/cmake/src/Makefile
	cd build/cmake/src \
	&& sudo make install

install-dependencies-Linux: /usr/local/lib/libglfw3.a
	
install-dependencies: init install-dependencies-$(OS)
	


	
$(ODIR)/%.o: $(source_dir)/%.c $(DEPS) init
	$(CC) -c -o $@ $< $(CFLAGS)

build: $(OBJ)
	$(CC) -o $(path_program)$(name_program) $^ $(CFLAGS) $(LIBS)
clear:
	rm -rf build/
run: build
	./build/program
all:: build
