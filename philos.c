/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmooney <kmooney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 14:24:18 by kmooney           #+#    #+#             */
/*   Updated: 2023/08/16 15:26:20 by kmooney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	ft_kill_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		data->philo[i]->dead = 1;
		i++;
	}
	return ;
}

void	ft_monitor(t_data *data)
{
	int i;
	while (1)
	{
		i = 0;
		while (i < data->num_philo)
		{
			if (data->philo[i]->dead != 1)
				i++;
			else
			{
				ft_kill_all(data);
				return ;
			}
		}
	}
	return ;
}

void	ft_thread_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo && data->death != 1)
	{
		data->philo[i]->thread = (pthread_t *)malloc(sizeof(pthread_t));
		{
			if (pthread_create(data->philo[i]->thread, NULL, &ft_routine, (void *)data->philo[i]) != 0)
				write(2, "Thread creation fail", 20);
			i++;
		}
	}
	ft_monitor(data);
	ft_join_philos(data);
	ft_free_all(data);
	return ;
}

void	ft_philo_init(t_data *data, int i)
{
		data->philo[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!data->philo[i])
			ft_free_all(data);
		data->philo[i]->start = data->start;
		data->philo[i]->reset = data->start - get_time();
		data->philo[i]->id = i;
		data->philo[i]->t_die = data->time_to_die;
		data->philo[i]->t_eat = data->time_to_eat;
		data->philo[i]->t_sleep = data->time_to_sleep;
		data->philo[i]->dead = 0;
		data->philo[i]->meals = 0;
		data->philo[i]->current = 0;
		data->philo[i]->thread = (pthread_t *)malloc(sizeof(pthread_t));
		if (!data->philo[i]->thread)
			ft_free_all(data);
		if (i == 0)
			data->philo[i]->fork_left = &data->forks[data->num_philo - 1]->mutex;
		else 
			data->philo[i]->fork_left = &data->forks[i - 1]->mutex;
		data->philo[i]->fork_right = &data->forks[i]->mutex;
		return ;
}

void	ft_create_philos(t_data *data)
{
	int i;

	i = 0;
	data->philo = (t_philo **)malloc((data->num_philo + 1) * sizeof(t_philo *));
	if (!data->philo)
		ft_free_all(data);
	while (i < data->num_philo)
	{
		ft_philo_init(data, i);
		i++;
	}
	data->philo[i] = NULL;
	return ;
}

void	ft_create_dead_mutex(t_data *data)
{
	data->dead_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(data->dead_mutex, NULL) != 0)
			write(2, "Mutex creation fail", 20);
	return ;
}

void	ft_create_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = (t_forks **)malloc((data->num_philo + 1) * sizeof(t_forks *));
	if (!data->forks)
		ft_free_all(data);
	while (i < data->num_philo)
	{
		data->forks[i] = (t_forks *)malloc(sizeof(t_forks));
		data->forks[i]->id = i;
		if (pthread_mutex_init(&(data->forks[i])->mutex, NULL) != 0)
			write(2, "Mutex creation fail", 20);
		i++;
	}
	data->forks[i] = NULL;
	return ;
}

void	ft_input_convert(char **argv, int argc, t_data *data)
{
	data->num_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi_uint64t(argv[2]);
	data->time_to_eat = ft_atoi_uint64t(argv[3]);
	data->time_to_sleep = ft_atoi_uint64t(argv[4]);
	data->start = get_time();
	if (argv[5])
		data->n_to_eat = ft_atoi(argv[5]);
	else
		data->n_to_eat = -2;
	return ;
}

uint64_t	get_time(void) // returns time in milliseconds
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

int	main(int argc, char **argv)
{
	t_data	*data;
	
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		exit (1);
	if (argc != 5 && argc != 6)
	{
		print_message();
		ft_free_all(data);
	}
	ft_input_convert(argv, argc, data);
	ft_create_forks(data);
	ft_create_philos(data);
	ft_thread_init(data);
	ft_free_all(data);
	printf("%lu\n", get_time());
	return (0);
}
