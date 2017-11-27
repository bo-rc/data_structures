CXX = clang++
CXXFLAGS += -Iinclude -std=c++14 -stdlib=libc++ -Wall -Wextra
LDFLAGS += -stdlib=libc++ -lc++abi -lpng

ifeq ($(strip $(MP_PART)),1)
TESTOBJS = rgba_pixel.o epng.o dsets.o
else ifeq ($(strip $(MP_PART)),2)
TESTOBJS = rgba_pixel.o epng.o dsets.o vertex.o edge.o
else
TESTOBJS = rgba_pixel.o epng.o dsets.o vertex.o edge.o maze.o mazereader.o
endif

include Makefile.proxy
