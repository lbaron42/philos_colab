/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmooney <kmooney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 23:37:56 by lbaron            #+#    #+#             */
/*   Updated: 2023/08/15 12:51:20 by kmooney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void print_message(void)
{
	printf ("Only positive numbers are allowed!\n");
	printf ("Usage: philosophers number_of_philosophers ");
	printf("time_to_die time_to_eat time_to_sleep\n");
	printf("Optional: number_of_times_each_philosopher_must_eat\n");
}

static void	error_no_digit(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		str++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			write (2, "Non numerical value inserted!\n", 30);
			print_message();
			exit (4);
		}
		i++;
	}
}

int	ft_atoi(char *str)
{
	int	i;
	int	sig;
	int	res;

	i = 0;
	sig = 1;
	res = 0;
	error_no_digit(str);
	if (str[0] == '-')
	{
		sig = -1;
		str++;
	}
	while (str[i])
	{
		res = res + (str[i] - '0');
		if (str[i + 1] != '\0')
			res = res * 10;
		i++;
	}
	return (res * sig);
}
