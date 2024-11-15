###
### Makefile for RPNCalculator
###
### Author:  Harry Lynch

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow -fPIC
LDFLAGS  = -g3 -no-pie

RPNCalculator: main.o RPNCalc.o parser.o DatumStack.o Datum.o 
	${CXX} ${LDFLAGS} -o RPNCalculator main.o RPNCalc.o parser.o DatumStack.o Datum.o

Datum+vector_example.o: Datum+vector_example.cpp Datum.h

Datum+vector_example: Datum+vector_example.o Datum.o
	${CXX} ${LDFLAGS} -o $@ $^

main: main.cpp RPNCalc.h
	${CXX} ${CXXFLAGS} -c main.cpp

RPNCalc: RPNCalc.cpp RPNCalc.h
	${CXX} ${CXXFLAGS} -c RPNCalc.cpp

parser: parser.cpp parser.h
	${CXX} ${CXXFLAGS} -c parser.cpp

DatumStack: DatumStack.cpp DatumStack.h
	${CXX} ${CXXFLAGS} -c DatumStack.cpp

unit_test: unit_test_driver.o DatumStack.o Datum.o parser.o
	${CXX} ${CXXFLAGS} unit_test_driver.o DatumStack.o Datum.o parser.o

clean:
	@find . -type f \( \
	-name '*.o' ! -name 'Datum.o' \
	\) -exec rm -f {} \;
	@rm -f *~ a.out