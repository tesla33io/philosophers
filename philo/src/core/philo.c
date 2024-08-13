/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 19:38:09 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/11 22:29:57 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"
#include <pthread.h>
#include <time.h>

time_t	p_get_last_meal_t(t_philo *philo)
{
	time_t	ret;

	pthread_mutex_lock(&philo->p_write_lock);
	ret = philo->last_meal_time;
	pthread_mutex_unlock(&philo->p_write_lock);
	return (ret);
}

void	p_set_last_meal_t(t_philo *philo, time_t time)
{
	pthread_mutex_lock(&philo->p_write_lock);
	philo->last_meal_time = time;
	pthread_mutex_unlock(&philo->p_write_lock);
}

t_state	p_get_state(t_philo *philo)
{
	t_state	ret;

	pthread_mutex_lock(&philo->p_state_lock);
	ret = philo->state;
	pthread_mutex_unlock(&philo->p_state_lock);
	return (ret);
}

void	p_set_state(t_philo *philo, t_state state)
{
	pthread_mutex_lock(&philo->p_state_lock);
	philo->state = state;
	pthread_mutex_unlock(&philo->p_state_lock);
}
