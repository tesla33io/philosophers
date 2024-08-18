/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:59:29 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/18 22:28:58 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

#include <pthread.h>
#include <unistd.h>
#include <stdio.h> /* printf() */

void	*philo_routine(void *philo_ref)
{
	t_philo	*philo;

	philo = philo_ref;
	pthread_mutex_lock(&philo->table->ready_lock);
	pthread_mutex_unlock(&philo->table->ready_lock);
	p_set_last_meal_t(philo, timestamp());
	if (philo->table->philo_n == 1)
		return (alone_philo_simulation(philo));
	if (philo->id % 2)
		wait_for(philo->table->t_eat / 2);
	while (!someone_died(philo->table) && !are_all_philos_done(philo->table))
	{
		mealtime(philo);
		if (are_all_philos_done(philo->table))
			break ;
		log_action(philo, SLEEP_MSG);
		wait_for(philo->table->t_sleep);
		log_state(philo, THINKING);
		wait_for(think_time(philo->table));
	}
	return (NULL);
}

void	mealtime(t_philo *philo)
{
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
	wait_for(philo->table->t_eat);
	philo->meals_count++;
	update_full_philos(philo, philo->table);
	pthread_mutex_unlock(&(*philo->right_fork));
	pthread_mutex_unlock(&(*philo->left_fork));
}

void	starvation_time(t_philo *philo)
{
	if (someone_died(philo->table))
		return ;
	log_action(philo, DIED_MSG);
	pthread_mutex_lock(&philo->table->death_lock);
	philo->table->someone_died = true;
	pthread_mutex_unlock(&philo->table->death_lock);
}
