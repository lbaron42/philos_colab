/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmooney <kmooney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:31:42 by kmooney           #+#    #+#             */
/*   Updated: 2023/08/16 15:50:25 by kmooney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	ft_free_all(t_data *data)
{
	//pthread_mutex_unlock(data->dead_mutex);
	ft_destroy_forks(data);
	if (data->philo)
		ft_free_philo(data);
	if (data->forks)
		ft_free_forks(data);
	free (data);
	exit (0);
}

void	ft_destroy_forks(t_data *data)
{
	int	i;
	char c;

	i = 0;
	if (data->forks)
	{
		while (i < data->num_philo)
		{
			if (pthread_mutex_destroy(&(data->forks[i]->mutex)) != 0)
				write(2, "Mutex Destroy fail\n", 19);
			i++;
		}
	}
	return ;
}

void	ft_join_philos(t_data *data)
{
	int	i;

	i = 0;
	if (data->philo)
	{
		while(i < data->num_philo && data->philo[i])
		{
			if (pthread_join(*(data)->philo[i]->thread, NULL) != 0)
				write(2, "pthread join fail", 17);
			i++;
		}
	}
	ft_free_all (data);
	return ;
}

void	ft_free_forks(t_data *data)
{
	int	i;

	i= 0;
	while (i < data->num_philo)
	{
		free (data->forks[i]);
		i++;
	}
	free (data->forks);
}

void	ft_free_philo(t_data *data)
{
	int	i;

	i= 0;
	while (i < data->num_philo)
	{
		free (data->philo[i]);
		i++;
	}
	free (data->philo);
}
