GOOGLE_TEST_LIB := gtest
GOOGLE_TEST_INCLUDE := /usr/include

G++_COMPILE_FLAGS := -g -c -I ${GOOGLE_TEST_INCLUDE} -fmax-errors=1
G++_LINKING_FLAGS := -L /usr/lib -l ${GOOGLE_TEST_LIB} -l pthread

SRC_DIR := ./src
SRC_BUILD_DIR := ${SRC_DIR}/build
TEST_DIR := ./test
TEST_BUILD_DIR := ${TEST_DIR}/build
BIN_DIR := ./bin
SRCS := $(shell find $(SRC_DIR) -name '*.cpp' -or -name '*.c' -or -name '*.s')
#$(info $$SRCS is [${SRCS}])
SRC_OBJS := $(SRCS:${SRC_DIR}/%=$(SRC_BUILD_DIR)/%.o)
#$(info $$SRC_OBJS is [${SRC_OBJS}])
SRC_INCS := ${shell find $(SRC_DIR) -name '*.h'}
#$(info $$SRC_INCS is [${SRC_INCS}])
SRC_LIB := $(SRCS:${SRC_DIR}/%=$(SRC_BUILD_DIR)/%.a)
#$(info $$SRC_LIB is [${SRC_LIB}])
TESTS := ${shell find $(TEST_DIR) -name '*.cpp' -or -name '*.c' -or -name '*.s'}
#$(info $$TESTS is [${TESTS}])
TEST_OBJS := $(TESTS:${TEST_DIR}/%=$(TEST_BUILD_DIR)/%.o)
#$(info $$TEST_OBJS is [${TEST_OBJS}])
TEST_INCS := ${shell find $(TEST_DIR) -name '*.h'}
#$(info $$TEST_INCS is [${TEST_INCS}])

EXECUTABLE := TestAll.exe

all: build ${BIN_DIR}/${EXECUTABLE} 

${BIN_DIR}/${EXECUTABLE} : ${TEST_OBJS} ${SRC_OBJS} 
	g++ -o $@ ${TEST_OBJS} ${SRC_OBJS} ${G++_LINKING_FLAGS}

#${SRC_BUILD_DIR}/%.cpp.a : ${SRC_OBJS}
#	ar rvs $@ $<

${SRC_BUILD_DIR}/%.c.o : ${SRC_DIR}/%.c ${SRC_INCS}
	mkdir -p $(dir $@)
	gcc ${G++_COMPILE_FLAGS} $< -o $@

${TEST_BUILD_DIR}/%.cpp.o : ${TEST_DIR}/%.cpp ${TEST_INCS}
	mkdir -p $(dir $@)
	g++ ${G++_COMPILE_FLAGS} $< -o $@

build:
	@mkdir -p bin

.PHONY : clean
clean :
	rm ${BIN_DIR}/${EXECUTABLE}
	rm ${SRC_BUILD_DIR}/*.o
	rm ${TEST_BUILD_DIR}/*.o
