/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmooney <kmooney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 23:22:38 by kmooney           #+#    #+#             */
/*   Updated: 2023/08/16 16:30:31 by kmooney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void *ft_routine(void *philo_void)
{
	t_philo *philo;
	int i = 0;
		
	philo = (t_philo *)philo_void;
	while (philo->dead == 0)
	{
		philo->hungry = 1;
		if (ft_eat(philo) == 1)
		{
			philo->dead = 1;
			/*if (pthread_mutex_lock(philo->dead_mutex) == 0)
			{
				philo->dead = 1;                  	      
			    printf("philo %d is dead \n", philo->id);
			}*/
			return (NULL);
		}
		else
		{
			printf("%lu Philo %d is sleeping\n",philo->current, philo->id);
			usleep (philo->t_sleep * 1000);
			printf("%lu Philo %d is thinking\n",philo->current, philo->id);
			ft_die_verify(philo);
		}
	}
	return NULL;
}

void	odd_eat(t_philo *philo)
{
	if (pthread_mutex_lock(philo->fork_right) == 0)  							//if the even numbers try to take their right fork first and odd numbers take left, then whoever gets to the fork
	{	   										     							//first will have a fork free on the other side. Maybe only take the other if the already have one. If even numbers put the right fork
        printf("%lu Philo %d has taken a fork\n",philo->current, philo->id);	//down first and then the left, this will hopefully allow the odd number to pick up again before the even grabs the forks again.
		pthread_mutex_lock(philo->fork_left); 
		printf("%lu Philo %d has taken a fork\n",philo->current, philo->id);
		printf("%lu Philo %d is eating\n",philo->current, philo->id);
		usleep(philo->t_eat * 1000);
		philo->current = get_time() - philo->start;
		printf("%lu Philo %d has finished eating\n",philo->current, philo->id);
		philo->reset = get_time();
		philo->hungry = 0;
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
	}
}

void	even_eat(t_philo *philo)
{                                                   
	if (pthread_mutex_lock(philo->fork_left) == 0)
	{
		printf("%lu Philo %d has taken a fork\n", philo->current, philo->id);
		pthread_mutex_lock(philo->fork_right);
		printf("%lu Philo %d has taken a fork\n", philo->current, philo->id);
		printf("%lu Philo %d is eating\n",philo->current, philo->id);
		usleep(philo->t_eat * 1000);
		philo->current = get_time() - philo->start;
		printf("%lu Philo %d has finished eating\n", philo->current, philo->id);
		philo->reset = get_time();
		philo->hungry = 0;
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
	}
}

int	ft_eat(t_philo *philo)
{
	pthread_mutex_t	*dead_mutex;

	philo->current = get_time() - philo->start;
	while (philo->dead == 0 && philo->hungry == 1)			//need to add this to struct - once fed they should exit the function and return to routine
	{
		if (philo->id % 2 == 0)
			even_eat(philo);
		else if (philo->id % 2 == 1)                        
			odd_eat(philo);
		ft_die_verify(philo);
	}
	if (philo->dead == 1)
		return (1);
	else 
		return (0);
}

void ft_die_verify(t_philo *philo)
{
	philo->elapsed = get_time() - philo->reset;
	printf("Verify: %lu\n", philo->elapsed);
	// printf("ft_die_verify says current - philo->reset is %lu\n", current - philo->reset);
	// printf("ft_die_verify says current - current is %lu\n", current);
	// printf("ft_die_verify says philo->reset is %lu\n", philo->reset);
	// printf("ft_die_verify says philo->t_die is %lu\n", philo->t_die);
	if(philo->elapsed > philo->t_die)
	{
		printf("ft_die_verify says t_die - elapsed is %lu\n", philo->t_die - philo->elapsed);
		printf("ft_die_verify says philo->t_die is %lu\n", philo->t_die);
		printf("%lu Philo %d is dead\n", philo->current, philo->id);
		philo->dead = 1;
	}
	return ;
}