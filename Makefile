
SRC = philos.c philos_utils.c philos_exit.c philos_func.c
INCLUDES = philos.h

all:
	cc $(SRC) -g3 -pthread -o philos
fclean:
	rm philos
