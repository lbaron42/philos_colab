
SRC = philos.c philos_utils1.c philo_exit.c
INCLUDES = philos.h

all:
	cc $(SRC) -g3 -pthread -o philos
fclean:
	rm philos
