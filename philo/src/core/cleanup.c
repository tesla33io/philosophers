/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 20:36:08 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/18 20:54:38 by astavrop         ###   ########.fr       */
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
	err |= pthread_mutex_destroy(philo->right_fork);
	free(philo->right_fork);
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
		if (p_get_state(table->philos[i]) != THINKING)
		{
			wait_for(1, NULL, false);
			continue ;
		}
		i++;
	}
	return (err);
}
