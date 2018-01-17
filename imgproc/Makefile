#! Makefile
BUILD_DIR := $(pwd)
CXXFLAGS :=  -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc
UNAME := $(shell uname -s)
INCLUDE := -I/usr/local/include/opencv -I/usr/local/include 

ifeq ($(UNAME),Linux)
	LINUX := 1	
endif

ifeq ($(LINUX),1)
	CXX ?= g++
	GCCVERSION := $(shell $(CXX) -dumpversion | cut -f1,2 -d.)
endif
SOURCES := \
	test_warpPerspective.cpp \
	test_affineTransform.cpp

OBJECTS := $(patsubst %.cpp, %.o, $(SOURCES))

all:$(OBJECTS)

%.o: %.cpp
	$(CXX) $< $(INCLUDE) $(CXXFLAGS) -o $@

test_affine: test_affineTransform.o
	./test_affineTransform.o

test_perspective: test_warpPerspective.o
	./test_warpPerspective.o

clean:
	rm -f *.o
	rm -f *.jpg

