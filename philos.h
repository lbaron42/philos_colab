/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmooney <kmooney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:43:54 by kmooney           #+#    #+#             */
/*   Updated: 2023/08/15 15:34:28 by kmooney          ###   ########.fr       */
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

typedef struct s_philo
{
	int				id;
	int				out;
	pthread_mutex_t *fork_left;
	pthread_mutex_t *fork_right;
	pthread_t		*thread;
} t_philo;

typedef struct s_forks
{
	int				id;
	pthread_mutex_t	mutex;
} t_forks;

typedef struct s_data
{
	int		num_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		n_to_eat;
	t_philo	**philo;
	t_forks	**forks;
} t_data;

int		main(int argc, char **argv);
int		ft_atoi(char *str);
void	print_message(void);

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

#endif //PHILOS_H