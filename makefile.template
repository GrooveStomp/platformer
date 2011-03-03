# Use the following website for more Makefile info:
# http://www.cprogramming.com/tutorial/makefiles_continued.html
# $@: the target
# $?: list of dependents changed since last invocation of target
# $^: all dependents minus duplicate names
# $+: all dependents, including duplicates, in the written order
# $<: the first dependency

SOURCES=src/main.cpp \
        src/math/vec2.cpp \
        src/world/player.cpp \
        src/graphics/font.cpp \
        src/graphics/texture.cpp \
        src/system/timer.cpp \
        src/system/unique.cpp \
		src/system/application.cpp
OBJECTS=$(SOURCES:.cpp=.o)
CC=g++
DEBUG=
DEBUG_DEFINES=
CFLAGS=-Wall -c $(DEBUG)
CINCLUDES=-I/usr/local/include -I/usr/local/include/SDL -I/usr/include/SDL -I./inc
PLATFORM_LFLAGS=-framework OpenGL
PLATFORM_DEFINES=
LFLAGS=-lSDLmain -lSDL -lSDL_image -lSDL_mixer -lGLEW $(PLATFORM_LFLAGS)
LINCLUDES=-L/usr/local/lib -L/usr/lib
DEFINES=-D_GNU_SOURCE=1 -D_THREAD_SAFE $(DEBUG_DEFINES) $(PLATFORM_DEFINES)
EXECUTABLE=platformer

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LFLAGS) $(LINCLUDES) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(CINCLUDES) $(DEFINES) $< -o $@

clean:
	rm -rf $(OBJECTS) platformerd platformer
