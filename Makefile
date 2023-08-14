
SRC = philos.c philos_utils1.c

all:
	cc $(SRC) -g3 -pthread -o philos
fclean:
	rm philos
