BIN=bin/
SRC=src/
LIB=lib/
OBJ=obj/

FLAGS = -lGL -lGLU -lglut

all: ${BIN}drone-path

${BIN}drone-path: ${OBJ}parameters.o ${OBJ}armPart.o ${OBJ}arm.o ${OBJ}main.o
	@/bin/echo -e "\n\e[1;34mCompiling object files:\e[0m"
	g++ -g -o ${BIN}drone-path ${OBJ}main.o ${OBJ}armPart.o ${OBJ}arm.o $(FLAGS)

${OBJ}main.o: ${SRC}main.cpp
	g++ -g -O0 -g3 -Wall -I${LIB} -c -o ${OBJ}main.o ${SRC}main.cpp

${OBJ}parameters.o: ${LIB}parameters.h
	g++ -g -O0 -g3 -Wall -I${LIB} -c -o ${OBJ}parameters.o ${LIB}parameters.h

${OBJ}armPart.o: ${SRC}armPart.cpp
	g++ -g -O0 -g3 -Wall -I${LIB} -c -o ${OBJ}armPart.o ${SRC}armPart.cpp

${OBJ}arm.o: ${SRC}arm.cpp
	g++ -g -O0 -g3 -Wall -I${LIB} -c -o ${OBJ}arm.o ${SRC}arm.cpp

clean:
	@/bin/echo -e "\n\e[1;34mCleaning project...\e[0m"
	@rm -rf ${OBJ}*.o
	@rm -f ${BIN}drone-path

run: all
	@/bin/echo -e "\n\e[1;34mRunning drone path...\e[0m"
	./${BIN}drone-path
