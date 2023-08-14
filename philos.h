/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   'philos.h'                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron  <lbaron@student.42berlin.de>       :+:  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023-07-29 23:31:07 by lbaron            :+:    #+#             */
/*   Updated: 2023-07-29 23:31:07 by lbaron           ###   ########.fr       */
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

//philos_utils1.c

void print_message(void);
int	ft_atoi(char *str);

#endif //PHILOS_H
