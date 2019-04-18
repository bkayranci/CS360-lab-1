CC = gcc
CFLAGS = -O2 -Wall -pedantic -g
LIBS = -lm -lnsl
PROGRAM_NAME = parser
LIBFDR_SRC = ./libfdr
LIBFDR_OUT = libfdr.a

.PHONY: parser parse.o parser.c

${PROGRAM_NAME}: ${PROGRAM_NAME}.o
	$(CC) $(CFLAGS) $(LIBS) -I./libfdr -o ${PROGRAM_NAME} ${PROGRAM_NAME}.o libfdr.a

${PROGRAM_NAME}.o: ${PROGRAM_NAME}.c libfdr.a
	$(CC) $(CFLAGS) -c ${PROGRAM_NAME}.c

libfdr.a:
	make -C ${LIBFDR_SRC}
	cp ${LIBFDR_SRC}/${LIBFDR_OUT} .
	make -C ${LIBFDR_SRC} clean


clean:
	rm -f ${PROGRAM_NAME} *.o ${LIBFDR_OUT}

run: ${PROGRAM_NAME}
	cat fam1 ./${PROGRAM_NAME}
	make clean