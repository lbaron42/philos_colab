/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmooney <kmooney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:31:34 by kmooney           #+#    #+#             */
/*   Updated: 2023/08/15 15:37:11 by kmooney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	mails = 0;
pthread_mutex_t mutex;

void *ft_routine(void *philo_void)
{
	t_philo *philo;
	philo = (t_philo *)philo_void;
	for (int i = 0; i < 10000; i++)
	{
		pthread_mutex_lock(philo->fork_left);
		pthread_mutex_lock(philo->fork_right);
		philo->out++;
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		printf("Philo %d is eating\n", philo->id);
	}
	return NULL;
}

void	ft_thread_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		data->philo[i]->thread = (pthread_t *)malloc(sizeof(pthread_t));
		{
			if (pthread_create(data->philo[i]->thread, NULL, &ft_routine, (void *)data->philo[i]) != 0)
				write(2, "Thread creation fail", 20);
			i ++;
		}
	}
	ft_join_philos(data);
	return ;
}

void	ft_philo_init(t_data *data, int i)
{
		data->philo[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!data->philo[i])
			ft_free_all(data);
		data->philo[i]->id = i;
		data->philo[i]->out = 0;
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
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->n_to_eat = ft_atoi(argv[5]);
	return ;
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
	return (0);	pthread_mutex_init(&mutex, NULL);
}
