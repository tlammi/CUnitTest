
CC = gcc
C_FLAGS = -Wall -pthread


SRCS = c_unit_test.c test_func.c test_main.c test_set.c assertions.c test_thread.c linked_list.c


all:
	${CC} ${C_FLAGS} ${SRCS}
