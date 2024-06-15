/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:54:00 by astavrop          #+#    #+#             */
/*   Updated: 2024/06/15 21:49:41 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

#include <stdio.h> /* printf() */
#include <pthread.h> /* pthread_mutex_lock() */

void	log_state(t_philo *philo)
{
	if (!philo || philo->state == DEAD || philo->data->someone_died)
		return ;
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%li ", timestamp() - philo->data->start_time);
	printf("%d is ", philo->id + 1);
	if (philo->state == EATING)
		printf("eating\n");
	else if (philo->state == SLEEPING)
		printf("sleeping\n");
	else if (philo->state == THINKING)
		printf("thinking\n");
	else
		printf("something wrong\n");
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	log_action(t_philo *philo, char *act)
{
	if (!philo || !act || philo->data->someone_died)
		return ;
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%li ", timestamp() - philo->data->start_time);
	printf("%d %s\n", philo->id + 1, act);
	pthread_mutex_unlock(&philo->data->print_lock);
}
