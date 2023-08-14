/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmooney <kmooney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:13:03 by lbaron            #+#    #+#             */
/*   Updated: 2023/08/14 21:20:14 by kmooney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"
#include <pthread.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

int j = 0;
pthread_mutex_t mutex;

typedef struct s_philo
{
	int		id;
	int		out;
	pthread_mutex_t fork_left;
	pthread_mutex_t fork_right;
	pthread_t phi;
}t_philo;

typedef struct s_forks
{
	int id;
	pthread_mutex_t mutex;
}t_forks;

typedef struct s_data
{
	int		num_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		n_to_eat;
	t_philo	**philo;
	t_forks **forks;
}t_data;

int mails = 0;

void *routine(void *philo)
{
	t_philo *v;
	v = (t_philo *)philo;
 	printf("First mail is %d and philo is %d\n", mails, v->id);
	for (int i = 0; i < 10000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		v->out++;
		printf("Mail is %d and %d/10000 from philo %d\n", mails, v->out, v->id);
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

void create_philos(t_data *v)
{
	int i;

	i = 0;
	v->philo = malloc((v->num_philosophers + 1) * sizeof(v->philo));
	while(i < v->num_philosophers)
	{
		v->philo[i] = malloc(sizeof(t_philo));
		v->philo[i]->id = i;
		v->philo[i]->out = 0;
		v->philo[i]->fork_left = v->forks[i]->mutex;
		if (pthread_create(&v->philo[i]->phi, NULL, &routine, v->philo[i]) != 0)
		{
			write(2, "Thread creation fail", 20);
		}
		i++;
	}
	v->philo[i] = NULL;
}

void join_philos(int num_phi, t_philo **philo)
{
	int	i;

	i = 0;
	while(i < num_phi)
	{
		if (pthread_join(philo[i]->phi, NULL) != 0)
		{
			write(2, "pthread join fail", 17);
		}
		i++;
	}
}

void create_forks(int num_phi, t_forks ***forks)
{
	int i;

	*forks = malloc((num_phi + 1) * sizeof(**forks));
	for (i = 0; i < num_phi; i++)
	{
		(*forks)[i] = malloc(sizeof(t_forks));
		(*forks)[i]->id = i;
		if (pthread_mutex_init(&(*forks)[i]->mutex, NULL) != 0)
		{
			write(2, "Mutex creation fail", 20);
		}
	}
	(*forks)[i] = NULL;
}

void destroy_forks(t_data *v)
{
	int i;

	for (i = 0; i < v->num_philosophers; i++)
	{
		if (pthread_mutex_destroy(&v->forks[i]->mutex) != 0)
		{
			write(2, "Mutex Destroy fail", 18);
		}
	}
}

int	main(int argc, char *argv[])
{
	t_data	v;
	int i = 0;

	pthread_mutex_init(&mutex, NULL);
	if (argc != 5 && argc != 6)
	{
		print_message();
		return (1);
	}
	v.num_philosophers = ft_atoi(argv[1]);
	v.time_to_die = ft_atoi(argv[2]);
	v.time_to_eat = ft_atoi(argv[3]);
	v.time_to_sleep = ft_atoi(argv[4]);
	if(argv[5])
		v.n_to_eat = ft_atoi(argv[5]);
	printf("Number of philosophers: %d\n", v.num_philosophers);
	printf("Time to die: %d\n", v.time_to_die);
	printf("Time to eat: %d\n", v.time_to_eat);
	printf("Time to sleep: %d\n", v.time_to_sleep);
	if (argv[5])
		printf("Number of times each philosopher must eat: %d\n", v.n_to_eat);
	create_forks(v.num_philosophers, &v.forks);
	create_philos(&v);
	join_philos(v.num_philosophers, v.philo);
	destroy_forks(&v);
	printf("Number of mails: %d\n", mails);
	return (0);
}

