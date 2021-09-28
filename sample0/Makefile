CC=$(MAKE_CC:-gcc)
source_dir=$(MAKE_SOURCE_DIR:-src)
path_program=$(MAKE_PATH_PROGRAM:-build/)
name_program=$(MAKE_NAME_PROGRAM:-program)
OS=$(MAKE_OS:-Linux)
IDIR=$(MAKE_IDIR:-include)
ODIR=$(MAKE_ODIR:-build/obj)

CFLAGS=-I$(IDIR)
LIBS=-I/usr/local/include -L/usr/local/lib -lglfw3 -lGL -lX11  -lXrandr -pthread -ldl -lm -lXxf86vm -lXi $(MAKE_LIBS)

_DEPS= main.h glad/glad.h KHR/khrplatform.h $(MAKE_HEADERS)
DEPS= $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ= main.o glad.o $(MAKE_OBJECTS)
OBJ= $(patsubst %,$(ODIR)/%,$(_OBJ))
GLFW_VERSION=$(MAKE_GLFW_VERSION:-3.3.4)
CMAKE_VERSION=$(MAKE_CMAKE_VERSION:-3.21.3)
GLSL_VERSION=1.30
GL_VERSION=4.20



help:
	print "Makefile of opengl project"
	print "Environment variables that can be set up into .env file:"
	print "MAKE_SOURCE_DIR"
	print "MAKE_PATH_PROGRAM"
	print "MAKE_NAME_PROGRAM"
	print "MAKE_OS"
	print "MAKE_IDIR"
	print "MAKE_ODIR"
	print "MAKE_LIBS"
	print "MAKE_HEADERS"
	print "MAKE_OBJECTS"
	print "MAKE_GLFW_VERSION"
	print "MAKE_CMAKE_VERSION"
	print ""
	print ""
	print ""
	print ""
	print ""

init:
	mkdir -p $(ODIR)
	mkdir -p $(path_program)
	mkdir -p build/cmake

glad:
	cd build/temp 
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
build/Makefile: build/cmake/bin/cmake build/temp/glfw-$(GLFW_VERSION)/
	cd build \
	&& cmake/bin/cmake temp/glfw-$(GLFW_VERSION)/ 
/usr/local/lib/libglfw3.a: build/Makefile
	cd build/ \
	&& sudo make install

install-dependencies-Linux: /usr/local/lib/libglfw3.a
	
install-dependencies: init install-dependencies-$(OS)
	
install-package:
	sudo apt install -y libglfw3-dev
	sudo apt install -y xorg-dev
$(ODIR)/%.o: $(source_dir)/%.c $(DEPS) init install-package
	$(CC) -c -o $@ $< $(CFLAGS)

build: $(OBJ)
	$(CC) -o $(path_program)$(name_program) $^ $(CFLAGS) $(LIBS)
clear:
	rm -rf build/
run: build
	./build/program
all:: build
