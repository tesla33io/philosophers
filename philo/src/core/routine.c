/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:59:29 by astavrop          #+#    #+#             */
/*   Updated: 2024/07/14 20:18:12 by astavrop         ###   ########.fr       */
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
		wait_for(philo->table->t_sleep, philo, true);
		log_state(philo, THINKING);
		if (are_all_philos_done(philo->table) == true)
			break ;
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
	wait_for(philo->table->t_eat - 1, philo, true);
	update_full_philos(philo, philo->table);
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
