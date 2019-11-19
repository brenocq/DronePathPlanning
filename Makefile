# Text style
RED    = \033[0;31m
GREEN  = \033[0;32m
NC     = \033[0m
BOLD   = \033[1m


BIN=bin/
SRC=src/
LIB=lib/
OBJ=obj/

FLAGS = -lGL -lGLU -lglut

all: ${BIN}drone-path

${BIN}drone-path: ${OBJ}parameters.o ${OBJ}armPart.o ${OBJ}arm.o ${OBJ}geneticAlg.o ${OBJ}main.o
	@/bin/echo -e "${GREEN}${BOLD}----- Compiling object files -----${NC}"
	g++ -g -o ${BIN}drone-path ${OBJ}main.o ${OBJ}geneticAlg.o ${OBJ}arm.o ${OBJ}armPart.o $(FLAGS)

${OBJ}main.o: ${SRC}main.cpp
	g++ -g -O0 -g3 -Wall -I${LIB} -c -o ${OBJ}main.o ${SRC}main.cpp

${OBJ}parameters.o: ${LIB}parameters.h
	g++ -g -O0 -g3 -Wall -I${LIB} -c -o ${OBJ}parameters.o ${LIB}parameters.h

${OBJ}armPart.o: ${SRC}armPart.cpp
	g++ -g -O0 -g3 -Wall -I${LIB} -c -o ${OBJ}armPart.o ${SRC}armPart.cpp

${OBJ}arm.o: ${SRC}arm.cpp
	g++ -g -O0 -g3 -Wall -I${LIB} -c -o ${OBJ}arm.o ${SRC}arm.cpp

${OBJ}geneticAlg.o: ${SRC}geneticAlg.cpp
	g++ -g -O0 -g3 -Wall -I${LIB} -c -o ${OBJ}geneticAlg.o ${SRC}geneticAlg.cpp


clean:
	@/bin/echo -e "${GREEN}${BOLD}----- Cleaning project -----${NC}"
	@rm -rf ${OBJ}*.o
	@rm -f ${BIN}drone-path

run: all
	@/bin/echo -e "${GREEN}${BOLD}----- Running drone-path -----${NC}"
	./${BIN}drone-path
