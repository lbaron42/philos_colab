/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmooney <kmooney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:43:54 by kmooney           #+#    #+#             */
/*   Updated: 2023/08/16 00:09:42 by kmooney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
#define PHILOS_H

# include <pthread.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdint.h>

typedef struct s_philo
{
	uint64_t		start;
	uint64_t		reset;
	int				id;
	int				meals;
	uint64_t		t_die;
	uint64_t		t_eat;
	uint64_t		t_sleep;
	int				dead;
	int				f_count;
	pthread_mutex_t *fork_left;
	pthread_mutex_t *fork_right;
	pthread_mutex_t	*dead_mutex;
	pthread_t		*thread;
} t_philo;

typedef struct s_forks
{
	int				id;
	pthread_mutex_t	mutex;
} t_forks;

typedef struct s_data
{
	uint64_t		start;
	int				num_philo;
	uint64_t		time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_to_eat;
	int				death;
	pthread_mutex_t	dead_mutex;
	t_philo			**philo;
	t_forks			**forks;
} t_data;

int		main(int argc, char **argv);
int		ft_atoi(char *str);
uint64_t	ft_atoi_uint64t(char *str);
void	print_message(void);
uint64_t	get_time(void);


void	ft_input_convert(char **argv, int argc, t_data *data);

void	ft_create_forks(t_data *v);

void	ft_create_philos(t_data *v);
void	ft_philo_init(t_data *data, int i);

void	ft_thread_init(t_data *data);

void	*ft_routine(void *philo);

void	ft_free_all(t_data *data);
void	ft_destroy_forks(t_data *data);
void	ft_join_philos(t_data *data);
void	ft_free_forks(t_data *data);
void	ft_free_philo(t_data *data);

void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);
int		ft_eat(t_philo *philo);
int		ft_die_verify(t_philo *philo);

#endif //PHILOS_H