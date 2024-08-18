/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:58:24 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/18 22:28:34 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h> /* TODO: delete */

time_t	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	wait_for(time_t wait_time)
{
	time_t	stime;
	time_t	time_diff;

	stime = timestamp();
	time_diff = timestamp() - stime;
	while (time_diff < wait_time)
	{
		if (usleep(50) < 0)
			return (1);
		time_diff = timestamp() - stime;
	}
	return (0);
}

time_t	think_time(t_table *table)
{
	if (table->philo_n > 1 && table->philo_n & 1
		&& table->t_eat * 2 > table->t_sleep)
		return ((table->t_eat * 2) - table->t_sleep);
	else
		return (0);
}
