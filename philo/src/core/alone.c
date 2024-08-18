/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alone.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 22:07:20 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/18 22:24:49 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"
#include <pthread.h>
#include <stdbool.h>

void	*alone_philo_simulation(t_philo *philo)
{
	p_set_last_meal_t(philo, timestamp());
	pthread_mutex_lock(philo->left_fork);
	log_action(philo, FORK_TAKEN_MSG);
	wait_for(philo->table->t_die);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}
