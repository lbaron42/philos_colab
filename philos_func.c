/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmooney <kmooney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 23:22:38 by kmooney           #+#    #+#             */
/*   Updated: 2023/08/16 00:48:43 by kmooney          ###   ########.fr       */
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
		if (ft_eat(philo) == 1)
		{
			if (i < 1)
			{
				pthread_mutex_lock(philo->dead_mutex);     //dead_mutex added to ensure that only one philosopher can report death
				philo->dead = 1;                  	       //dead_mutex is closed in free_all function
				i++;                                       //if philo->dead == 1, then thread_init function will hopefully lock all mutex - this will hopefully
				printf("philo %d is dead \n", philo->id);  //kill the rest of the philosophers and as long as the keep quiet about it all is good!
			}
			return (NULL);
		}
		else
			usleep (philo->t_sleep * 1000);
	}
	return NULL;
}

int	ft_eat(t_philo *philo)
{
	uint64_t current;

	while (philo->dead == 0 && philo->hungry == 1)			//need to add this to struct - once fed they should exit the function and return to routine
	{
		philo->f_count = 0;
		if (philo->id % 2 == 0)
		{
			if (pthread_mutex_lock(philo->fork_right) == 0)  					//if the even numbers try to take their right fork first and odd numbers take left, then whoever gets to the fork
			{	   										     					//first will have a fork free on the other side. Maybe only take the other if the already have one. If even numbers put the right fork
		        printf("%hu Philo %d has taken a fork\n",current, philo->id);	//down first and then the left, this will hopefully allow the odd number to pick up again before the even grabs the forks again.
				pthread_mutex_lock(philo->fork_left); 
				printf("%hu Philo %d has taken a fork\n",current, philo->id);
				philo->hungry = 0;
				pthread_mutex_unlock(philo->fork_right);
				pthread_mutex_unlock(philo->fork_left);
			}
		}
		else if (philo->id % 2 == 1)                        
		{                                                   
			if (pthread_mutex_lock(philo->fork_left) == 0)
			{
				printf("%hu Philo %d has taken a fork\n", current, philo->id);
				pthread_mutex_lock(philo->fork_right);
				printf("%hu Philo %d has taken a fork\n",current, philo->id);
				philo->hungry = 0;
				pthread_mutex_unlock(philo->fork_left);
				pthread_mutex_unlock(philo->fork_right);
			}
		}
	}
	return (0);
}
		current = get_time() - philo->start;
		printf("ft_eat says current is %lu\n", current );
		printf("ft_eat says philo->reset is %lu\n", philo->reset);
		printf("ft_eat says current - philo->reset is %lu\n", current - philo->reset);
/// issue here with time management
		printf("ft_eat says philo->t_die is %lu\n", philo->t_die);

		i = ft_die_verify(philo);
		if  == 0)
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