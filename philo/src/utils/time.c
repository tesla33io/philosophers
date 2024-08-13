/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:58:24 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/13 22:05:05 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h> /* TODO: delete */

time_t	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	wait_for(time_t wait_time, t_philo *phl, bool extra)
{
	time_t	stime;
	time_t	time_diff;

	stime = timestamp();
	time_diff = timestamp() - stime;
	while (time_diff < wait_time)
	{
		usleep(10);
		time_diff = timestamp() - stime;
		pthread_mutex_lock(&phl->table->death_lock);
		if (extra && (time_diff >= phl->table->t_die
				|| timestamp() - p_get_last_meal_t(phl) >= phl->table->t_die))
		{
			pthread_mutex_unlock(&phl->table->death_lock);
			starvation_time(phl);
			return (1);
		}
		pthread_mutex_unlock(&phl->table->death_lock);
	}
	return (0);
}
