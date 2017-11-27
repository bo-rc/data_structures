CXX = clang++
CXXFLAGS += -Iinclude -std=c++14 -stdlib=libc++ -Wall -Wextra
LDFLAGS += -stdlib=libc++ -lc++abi -lpng

ifeq ($(strip $(MP_PART)),1)
TESTOBJS = epng.o rgba_pixel.o coloredout.o
else
#no maptiles.o because it is inlined in unit_tests.cpp for partial compilation advantages
TESTOBJS = epng.o rgba_pixel.o coloredout.o mosaiccanvas.o sourceimage.o tileimage.o
endif

include Makefile.proxy
