CC = g++
# Text style
RED    = \033[0;31m
GREEN  = \033[0;32m
NC     = \033[0m
BOLD   = \033[1m

# Folders
BIN	   = bin/
SRC	   = src/
SRCO   = src/opengl/
LIB    = lib/
LIBO   = lib/opengl/
OBJ    = obj/

# Files
FILES-OPENGL = window camera material model mesh texture shader light directionalLight pointLight spotLight
FILES = main

SOURCES=$(patsubst %, ${SRCO}%.cpp, ${FILES-OPENGL})
SOURCES+=$(patsubst %, ${SRC}%.cpp, ${FILES})

HEADERS=$(patsubst %, ${LIBO}%.h, ${FILES-OPENGL})
HEADERS+=$(patsubst %, ${LIB}%.h, ${FILES})

OBJECTS=$(patsubst %, ${OBJ}%.o, ${FILES-OPENGL})
OBJECTS+=$(patsubst %, ${OBJ}%.o, ${FILES})

DEPENDENCIES=${LIB}parameters.h

EXECUTABLE=${BIN}droneSwarm

# Flags
FLAGS= -lGL -lGLU -lglfw -lGLEW -lassimp -Wall -I${LIBO} -I${LIB}
export LD_LIBRARY_PATH=/usr/local/lib

# Targets
${EXECUTABLE}: ${OBJECTS} ${DEPENDENCIES}
	@/bin/echo -e "${GREEN}${BOLD}----- Creating executable -----${NC}"
	${CC} -g ${OBJECTS} -o ${EXECUTABLE} ${FLAGS} 

# Compile OpenGL files
${OBJ}%.o: ${SRCO}%.cpp
	@/bin/echo -e "${GREEN}Compiling $<${NC}"
	${CC} -c $< -o $@ ${FLAGS} 

# Compile project files
${OBJ}%.o: ${SRC}%.cpp
	@/bin/echo -e "${GREEN}Compiling $<${NC}"
	${CC} -c $< -o $@ ${FLAGS} 

clean:
	@/bin/echo -e "${GREEN}${BOLD}----- Cleaning project -----${NC}"
	rm  ${OBJ}*.o
	rm  ${EXECUTABLE}

run: ${EXECUTABLE}
	@/bin/echo -e "${GREEN}${BOLD}----- Running ${EXECUTABLE} -----${NC}"
	./${EXECUTABLE}
