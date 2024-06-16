/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:58:24 by astavrop          #+#    #+#             */
/*   Updated: 2024/06/16 16:55:51 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

time_t	timestamp(void)
{
	struct	timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	wait_for(time_t wait_time, t_philo *philo)
{
	time_t	stime;
	time_t	time_diff;

	stime = timestamp();
	time_diff = timestamp() - stime;
	while (time_diff < wait_time)
	{
		usleep(100);
		time_diff = timestamp() - stime;
		pthread_mutex_lock(&philo->data->death_lock);
		if (philo->data->someone_died)
		{
			pthread_mutex_unlock(&philo->data->death_lock);
			return (1);
		}
		if (time_diff >= philo->data->time_to_die
				|| timestamp() - philo->last_meal_time >= philo->data->time_to_die)
		{
			pthread_mutex_unlock(&philo->data->death_lock);
			starvation_time(philo);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->death_lock);
	}
	return (0);
}
