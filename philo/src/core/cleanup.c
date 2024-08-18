/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 20:36:08 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/18 22:13:02 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

#include <pthread.h>
#include <stdlib.h>

int	destroy_philos(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->philo_n)
	{
		pthread_mutex_destroy(&t->philos[i]->p_write_lock);
		pthread_mutex_destroy(&t->philos[i]->p_state_lock);
		free(t->philos[i]);
		i++;
	}
	free(t->philos);
	return (0);
}

int	destroy_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_n)
	{
		pthread_mutex_destroy(table->forks[i]);
		free(table->forks[i]);
		i++;
	}
	free(table->forks);
	return (0);
}
