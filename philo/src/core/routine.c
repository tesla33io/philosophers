/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:59:29 by astavrop          #+#    #+#             */
/*   Updated: 2024/07/11 19:16:21 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h> /* TODO: DELETE */
#include <stdio.h> /* printf() */

void	*philo_routine(void *philo_ref)
{
	t_philo	*philo;

	philo = philo_ref;
	if (philo->id % 2 == 0)
		wait_for(10, philo, false);
	p_set_last_meal_t(philo, timestamp());
	while (!philo->table->someone_died)
	{
		mealtime(philo);
		log_state(philo, SLEEPING);
		pthread_mutex_lock(&philo->table->write_lock);
		if (philo->table->full_philo_n == philo->table->philo_n)
		{
			pthread_mutex_unlock(&philo->table->write_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->table->write_lock);
		wait_for(philo->table->t_sleep, philo, true);
		log_state(philo, THINKING);
	}
	return (NULL);
}

void	mealtime(t_philo *philo)
{
	if (philo->table->someone_died)
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
	log_state(philo, EATING);
	p_set_last_meal_t(philo, timestamp());
	philo->meals_count++;
	wait_for(philo->table->t_eat, philo, true);
	pthread_mutex_lock(&philo->table->write_lock);
	if (philo->meals_count == philo->table->max_meal_n)
		philo->table->full_philo_n++;
	pthread_mutex_unlock(&philo->table->write_lock);
	pthread_mutex_unlock(&(*philo->left_fork));
	pthread_mutex_unlock(&(*philo->right_fork));
	p_set_state(philo, THINKING);
}

void	starvation_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->death_lock);
	if (philo->table->someone_died)
	{
		pthread_mutex_unlock(&philo->table->death_lock);
		return ;
	}
	log_action(philo, DIED_MSG);
	philo->table->someone_died = true;
	pthread_mutex_unlock(&philo->table->death_lock);
}
