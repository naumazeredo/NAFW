# C++ Compiler
CXX=g++
CXXFLAGS=-c -Wall -std=c++11
LDFLAGS = $(addprefix -l,$(LIBS))

SOURCES := $(wildcard src/*.cpp) \
	$(wildcard src/render/*.cpp)

VPATH := src:src/render

OBJECTS := $(addprefix obj/,$(notdir $(SOURCES:.cpp=.o)))
EXECUTABLE = nafw.out

LIBS := SDL2 SDL2_image

.PHONY: clean obj

debug: CXX += -DDEBUG
debug: $(SOURCES) $(EXECUTABLE)
release: CXX += -DSDL_ASSERT_LEVEL=1
release: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $^ $(LDFLAGS) -o $@

$(OBJECTS): | obj

obj:
	@mkdir -p $@

obj/%.o: %.cpp
	$(CXX) $< $(CXXFLAGS) -o $@

clean:
	@- $(RM) -R obj $(EXECUTABLE)

rebuild:
	make clean
	make
