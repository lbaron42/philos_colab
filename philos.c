/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmooney <kmooney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:31:34 by kmooney           #+#    #+#             */
/*   Updated: 2023/08/15 21:11:45 by kmooney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void *ft_routine(void *philo_void)
{
	int i;
	
	i = 0;
	t_philo *philo;
	philo = (t_philo *)philo_void;

	while (i == 0)
	{
		// printf("Current time is %lu \n", get_time());
		// usleep(100000);
		// printf("After 1000 usleep Current time is %lu \n", get_time());
		if(i == 1)
			printf("filo is dead%d\n", i);
		if (ft_eat(philo) == 1)
			return ((void *)1);
		usleep(philo->t_sleep * 1000);
		//ft_think(philo);
		// while (i == 0)
		// {
		// 	usleep(10*1000);
		// 	i = ft_die_verify(philo);

		// }
	}
	return NULL;
}

int	ft_eat(t_philo *philo)
{
	uint64_t current;
	int i = 0;

	while (i == 0)
	{
		philo->f_count = 0;
		current = get_time() - philo->start;
		printf("ft_eat says current is %lu\n", current );
		printf("ft_eat says philo->reset is %lu\n", philo->reset);
		printf("ft_eat says current - philo->reset is %lu\n", current - philo->reset);
/// issue here with time management
		printf("ft_eat says philo->t_die is %lu\n", philo->t_die);

		i = ft_die_verify(philo);
		if(pthread_mutex_lock(philo->fork_left) == 0 && pthread_mutex_lock(philo->fork_right) == 0)
		{
			printf("%lu Philo %d has taken both forks\n",current, philo->id);
			philo->f_count++;
			philo->f_count++;
		}

		// if(pthread_mutex_lock(philo->fork_left))
		// {
		// 	printf("%hu Philo %d has taken a fork\n",current, philo->id);
		// 	philo->f_count++;
		// }
		// if (pthread_mutex_lock(philo->fork_right))
		// {
		// 		printf("%hu Philo %d has taken a fork\n",current, philo->id);
		// 		philo->f_count++;
		// }
		if (philo->f_count == 2)
		{
			printf("%lu Philo %d is eating\n",current, philo->id);
			usleep(philo->t_eat * 1000);
			current = get_time() - philo->start;
			printf("%lu Philo %d has finished eating\n",current, philo->id);
			philo->reset = get_time();
		}
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		philo->meals--;
	}
	// if (i == 1)
	// {
	// 	current = get_time() - philo->start;
	// 	printf("%lu Philo %d is dead\n", current, philo->id);
	// 	return (1);
	// }
	return (0);
}

void	ft_sleep(t_philo *philo)
{
	uint64_t current;
	
	current = get_time() - philo->start;
	pthread_mutex_lock(philo->fork_left);
	pthread_mutex_lock(philo->fork_right);
	printf("Time stamp: %lu Philo %d is eating\n",current, philo->id);
	usleep(200000);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);	
}

void	ft_think(t_philo *philo)
{
	uint64_t current;
	
	current = get_time() - philo->start;
	pthread_mutex_lock(philo->fork_left);
	pthread_mutex_lock(philo->fork_right);
	printf("Time stamp: %lu Philo %d is eating\n",current, philo->id);
	usleep(200000);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

// int	ft_die_verify(t_philo *philo)
// {
// 	int i;

// 	i = 0;
// 	uint64_t current;
// 	current = get_time();
// 	if(current - philo->reset > philo->t_die)
// 	{
// 		i = 1;
// 		return (i);
// 	}
// 	return (i);
// }


int	ft_die_verify(t_philo *philo)
{
	int i;

	i = 0;
	uint64_t current;
	current = get_time() - philo->start;
	// printf("ft_die_verify says current - philo->reset is %lu\n", current - philo->reset);
	// printf("ft_die_verify says current - current is %lu\n", current);
	// printf("ft_die_verify says philo->reset is %lu\n", philo->reset);
	// printf("ft_die_verify says philo->t_die is %lu\n", philo->t_die);
	if((current - philo->reset) > philo->t_die)
	{
		printf("ft_die_verify says current - philo->reset is %lu\n", current - philo->reset);
		printf("ft_die_verify says philo->t_die is %lu\n", philo->t_die);
		printf("%lu Philo %d is dead\n", current, philo->id);


		i = 1;
		return (i);
	}
	return (i);
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
		data->philo[i]->f_count = 0;
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