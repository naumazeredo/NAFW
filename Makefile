# C++ Compiler
CC=g++
CXXFLAGS=-c -Wall -std=c++11
LDFLAGS = $(addprefix -L,$(LIBSSOURCE)) $(addprefix -l,$(LIBS))

SOURCES := $(wildcard src/*.cpp) $(wildcard src/network/*.cpp)
OBJECTS := $(addprefix obj/,$(notdir $(SOURCES:.cpp=.o)))
EXECUTABLE = nafw

LIBS := mingw32 SDL2main SDL2 SDL2_image SDL2_net
LIBSSOURCE := "C:\SDL-2.0.0-mingw\lib"

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJECTS): | obj

obj:
	mkdir $@

obj/%.o: src/%.cpp
	$(CC) -o $@ $< $(CXXFLAGS)

clean:
	- $(RM) -R obj $(addsuffix .exe,$(EXECUTABLE))

rebuild:
	make clean
	make
