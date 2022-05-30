GOOGLE_TEST_LIB = gtest
GOOGLE_TEST_INCLUDE = /usr/include

G++_COMPILE_FLAGS = -c -I ${GOOGLE_TEST_INCLUDE} -std=c++17
G++_LINKING_FLAGS = -L /usr/lib -l ${GOOGLE_TEST_LIB} -l pthread

SOURCES = ${wildcard src/*.cpp}
INCLUDES = ${wildcard src/*.h}
INCLUDES += ${wildcard test/*.h}
TESTS = ${wildcard test/*.cpp}

SOURCE_OBJECTS = ${patsubst %.cpp, %.o, ${SOURCES}}
TEST_OBJECTS = ${patsubst %.cpp, %.o, ${TESTS}}

EXECUTABLE = bin/TestAll.exe

all: build ${EXECUTABLE} 

${EXECUTABLE} : ${SOURCE_OBJECTS} ${TEST_OBJECTS}
	g++ -o $@ ${SOURCE_OBJECTS} ${TEST_OBJECTS} ${G++_LINKING_FLAGS}

${SOURCE_OBJECTS} : src/%.o : src/%.cpp ${INCLUDES}
	g++ ${G++_COMPILE_FLAGS} $< -o $@

${TEST_OBJECTS} : test/%.o : test/%.cpp ${INCLUDES}
	g++ ${G++_COMPILE_FLAGS} $< -o $@

build:
	@mkdir -p bin

.PHONY : clean
clean :
	rm -rf ${EXECUTABLE} bin
