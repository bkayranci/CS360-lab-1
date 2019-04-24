CC = gcc
CFLAGS = -O2 -Wall -pedantic -g
LIBS = -lm -lnsl
PROGRAM_NAME = parser
LIBFDR_SRC = ./libfdr
LIBFDR_OUT = libfdr.a

PROGRAM_FLAG ?= 

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

run-fam1: ${PROGRAM_NAME}
	./${PROGRAM_NAME} fams/fam1 ${PROGRAM_FLAG}
	make clean

run-fam2: ${PROGRAM_NAME}
	./${PROGRAM_NAME} fams/fam2 ${PROGRAM_FLAG}
	make clean

run-fam3: ${PROGRAM_NAME}
	./${PROGRAM_NAME} fams/fam3 ${PROGRAM_FLAG}
	make clean

run-fam4: ${PROGRAM_NAME}
	./${PROGRAM_NAME} fams/fam4 ${PROGRAM_FLAG}
	make clean

run-fam5: ${PROGRAM_NAME}
	./${PROGRAM_NAME} fams/fam5 ${PROGRAM_FLAG}
	make clean

run-cyclefam: ${PROGRAM_NAME}
	./${PROGRAM_NAME} fams/cyclefam ${PROGRAM_FLAG}
	make clean

run-redundant: ${PROGRAM_NAME}
	./${PROGRAM_NAME} fams/redundant ${PROGRAM_FLAG}
	make clean

run-nonredundant: ${PROGRAM_NAME}
	./${PROGRAM_NAME} fams/nonredundant ${PROGRAM_FLAG}
	make clean
