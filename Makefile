# Use the following website for more Makefile info:
# http://www.cprogramming.com/tutorial/makefiles_continued.html
# $@: the target
# $?: list of dependents changed since last invocation of target
# $^: all dependents minus duplicate names
# $+: all dependents, including duplicates, in the written order
# $<: the first dependency

# Note: For linux: -lGL
# 		For OSX: -framework Opengl
# 				 -framework,Cocoa,

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
CFLAGS=-Wall -c $(DEBUG)
CINCLUDES=-I/usr/local/include/SDL -I./inc
LFLAGS=-lSDLmain -lSDL -framework,Cocoa, -lSDL_image -lSDL_mixer -lGLEW -framework OpenGL
LINCLUDES=-L/usr/local/lib
DEFINES=-D_GNU_SOURCE=1 -D_THREAD_SAFE $(DEBUG_DEFINES)
EXECUTABLE=platformer

ll: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LFLAGS) $(LINCLUDES) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(CINCLUDES) $(DEFINES) $< -o $@

debug:
	$(MAKE) $(MAKEFILE) DEBUG="-g -O0 -fno-inline" EXECUTABLE=platformerd DEBUG_DEFINES="-DFOB_LOGGING -DFOB_ASSERTS_ENABLED"

clean:
	rm -rf $(OBJECTS) platformerd platformer
