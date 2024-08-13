/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:54:00 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/13 22:38:21 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

#include <stdio.h> /* printf() */
#include <pthread.h> /* pthread_mutex_lock() */

void	log_state(t_philo *philo, t_state state)
{
	pthread_mutex_lock(&philo->table->print_lock);
	if (!philo || p_get_state(philo) == DEAD || someone_died(philo->table))
	{
		pthread_mutex_unlock(&philo->table->print_lock);
		return ;
	}
	p_set_state(philo, state);
	printf("%li ", timestamp() - philo->table->t_start);
	printf("%d is ", philo->id + 1);
	if (state == EATING)
		printf("eating\n");
	else if (state == SLEEPING)
		printf("sleeping\n");
	else if (state == THINKING)
		printf("thinking\n");
	else
		printf("something wrong\n");
	pthread_mutex_unlock(&philo->table->print_lock);
}

void	log_action(t_philo *philo, char *act)
{
	pthread_mutex_lock(&philo->table->print_lock);
	if (philo && act && !someone_died(philo->table))
	{
		printf("%li ", timestamp() - philo->table->t_start);
		printf("%d %s\n", philo->id + 1, act);
	}
	pthread_mutex_unlock(&philo->table->print_lock);
}
