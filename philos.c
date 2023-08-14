/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   'main.c'                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron    <lbaron@student.42berlin.de>     :+:  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023-08-14 13:13:03 by lbaron            :+:    #+#             */
/*   Updated: 2023-08-14 13:13:03 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

typedef struct s_philo
{
	int		id;
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


u_int64_t get_time(void)
{
	struct timeval time;
	if (gettimeofday(&time, NULL))
		return (0);

	return ((time.tv_usec * (u_int64_t)1000) + (time.tv_usec / 1000));
}

void *routine(void *data)
{
	t_data *v;
	u_int64_t time;
	v = (t_data *)data;

	time = get_time();
	printf("Time %lu\n", time);
	printf("This is Time to sleep in the routine function %d\n", v->time_to_sleep);

	get_time();

	for (int i = 0; i < 5 ;i++)
	{
		//pthread_mutex_lock(&mutex);
		mails++;
		//pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

void create_philos(t_data *v)
{
	int i;

	i = 0;
	v->philo = malloc((v->num_philosophers + 1) * sizeof(v->philo));
	printf("v adress: %p\n", &v);
	while(i < v->num_philosophers)
	{
		v->philo[i] = malloc(sizeof(t_philo));
		v->philo[i]->id = i;
		if (pthread_create(&v->philo[i]->phi, NULL, &routine, v) != 0)
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

int	main(int argc, char *argv[])
{
	t_data	v;

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

	//pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", mails);
	return (0);
}

