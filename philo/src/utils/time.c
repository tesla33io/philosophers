/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:58:24 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/13 22:40:27 by astavrop         ###   ########.fr       */
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
		if (extra && (time_diff >= phl->table->t_die
				|| timestamp() - p_get_last_meal_t(phl) >= phl->table->t_die))
		{
			starvation_time(phl);
			return (1);
		}
	}
	return (0);
}
