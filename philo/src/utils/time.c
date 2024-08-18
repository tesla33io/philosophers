/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:58:24 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/18 20:54:16 by astavrop         ###   ########.fr       */
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
	(void)extra;
	if (usleep((unsigned int) wait_time * 1000))
	{
		if (phl)
			starvation_time(phl);
		return (1);
	}
	return (0);
}
