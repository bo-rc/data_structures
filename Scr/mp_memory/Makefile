CXX := clang++
CXXFLAGS := -Iinclude -std=c++14 -stdlib=libc++ -g -O0 -c -Wall -Wextra
LDFLAGS := -stdlib=libc++ -lc++abi -lpng

ifdef SANITIZE
CXXFLAGS += -fsanitize=$(SANITIZE)
LDFLAGS += -fsanitize=$(SANITIZE)
endif

.PHONY: all doc tidy clean

EXES = scoped_ptr_test dynamic_array_test collage_test

EPNG_HEADERS = include/epng.h include/rgba_pixel.h
SPTR_HEADERS = include/scoped_ptr.h include/scoped_ptr.tcc
SARR_HEADERS = include/dynamic_array.h include/dynamic_array.tcc
SCOPED_HEADERS = $(SPTR_HEADERS) $(SARR_HEADERS)

all: $(EXES)

scoped_ptr_test.o : $(SPTR_HEADERS) src/scoped_ptr_test.cpp
	$(CXX) $(CXXFLAGS) src/scoped_ptr_test.cpp

scoped_ptr_test : scoped_ptr_test.o
	$(CXX) $(LDFLAGS) scoped_ptr_test.o -o scoped_ptr_test

dynamic_array_test.o : $(SARR_HEADERS) src/dynamic_array_test.cpp
	$(CXX) $(CXXFLAGS) src/dynamic_array_test.cpp

dynamic_array_test : dynamic_array_test.o moveonly.o
	$(CXX) $(LDFLAGS) dynamic_array_test.o moveonly.o -o dynamic_array_test

moveonly.o : include/moveonly.h src/moveonly.cpp
	$(CXX) $(CXXFLAGS) src/moveonly.cpp

rgba_pixel.o : include/rgba_pixel.h src/rgba_pixel.cpp
	$(CXX) $(CXXFLAGS) src/rgba_pixel.cpp

epng.o : include/epng.h src/epng.cpp
	$(CXX) $(CXXFLAGS) src/epng.cpp

collage.o : $(EPNG_HEADERS) $(SCOPED_HEADERS) include/collage.h src/collage.cpp
	$(CXX) $(CXXFLAGS) src/collage.cpp

collage_test.o : $(EPNG_HEADERS) $(SCOPED_HEADERS) include/collage.h src/collage_test.cpp
	$(CXX) $(CXXFLAGS) src/collage_test.cpp

collage_test : collage_test.o collage.o epng.o rgba_pixel.o
	$(CXX) $(LDFLAGS) collage_test.o collage.o epng.o rgba_pixel.o -o collage_test

doc:
	doxygen mp_memory.doxygen

tidy:
	rm -rf scene*.png doc

clean: tidy
	rm -rf *.o $(EXES)
