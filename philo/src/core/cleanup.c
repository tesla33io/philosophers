/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 20:36:08 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/11 21:51:19 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

#include <pthread.h>
#include <stdlib.h>

int	destroy_philo(t_philo *philo)
{
	int	err;

	err = 0;
	err |= pthread_mutex_destroy(&philo->p_write_lock);
	err |= pthread_mutex_destroy(&philo->p_state_lock);
	free(philo);
	return (err);
}

int	destroy_table(t_table *table)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	while (i < table->philo_n)
	{
		err |= pthread_mutex_destroy(table->forks[i]);
		free(table->forks[i]);
		err |= destroy_philo(table->philos[i]);
		i++;
	}
	err |= pthread_mutex_destroy(&table->print_lock);
	err |= pthread_mutex_destroy(&table->death_lock);
	err |= pthread_mutex_destroy(&table->write_lock);
	err |= pthread_mutex_destroy(&table->ready_lock);
	return (err);
}
