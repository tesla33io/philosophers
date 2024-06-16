/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:59:29 by astavrop          #+#    #+#             */
/*   Updated: 2024/06/16 18:18:43 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

#include <pthread.h>
#include <unistd.h>
#include <stdio.h> /* printf() */

void	*philo_routine(void* philo_ref)
{
	t_philo	*philo;

	philo = philo_ref;
	if (philo->id % 2)
		usleep(100);
	while (!philo->data->someone_died)
	{
		mealtime(philo);
		if (philo->data->full_philo_n == philo->data->philo_n_fork_num)
			break ;
		philo->state = SLEEPING;
		log_state(philo);
		if (wait_for(philo->data->time_to_sleep, philo) != 0)
			break ;
		philo->state = THINKING;
		log_state(philo);
	}
	return (NULL);
}

void	mealtime(t_philo *philo)
{
	if (philo->data->someone_died)
		return ;
	if (philo->id % 2 == 0)
	{
        pthread_mutex_lock(&(*philo->left_fork));
        log_action(philo, FORK_TAKEN_MSG);
        pthread_mutex_lock(&(*philo->right_fork));
    }
	else
	{
        pthread_mutex_lock(&(*philo->right_fork));
        log_action(philo, FORK_TAKEN_MSG);
        pthread_mutex_lock(&(*philo->left_fork));
    }
	log_action(philo, FORK_TAKEN_MSG);
	philo->state = EATING;
	log_state(philo);
	philo->last_meal_time = timestamp();
	wait_for(philo->data->time_to_eat, philo);
	philo->meals_count++;
	if (philo->meals_count == philo->data->max_meal_num)
		philo->data->full_philo_n++;
	philo->state = THINKING;
	pthread_mutex_unlock(&(*philo->left_fork));
	pthread_mutex_unlock(&(*philo->right_fork));
}

void	starvation_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_lock);
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->death_lock);
		return ;
	}
	log_action(philo, DIED_MSG);
	philo->data->someone_died = true;
	pthread_mutex_unlock(&philo->data->death_lock);
}

/*
static void	take_forks(t_philo *philo)
{
	int	id_prev;
	int	id_next;

	id_prev = philo->id - 1;
	id_next = philo->id + 1;
	if (id_prev < 0)
		id_prev = philo->data->philo_n_fork_num - id_prev;
	if (id_next > philo->data->philo_n_fork_num)
		id_next = id_next - philo->data->philo_n_fork_num;
	if (philo->data->philos[id_prev]->state != EATING
			&& philo->data->philos[id_next]->state != EATING)
	{
		pthread_mutex_lock(&(*philo->left_fork));
        log_action(philo, FORK_TAKEN_MSG);
		pthread_mutex_lock(&(*philo->right_fork));
        log_action(philo, FORK_TAKEN_MSG);
	}
}
*/
