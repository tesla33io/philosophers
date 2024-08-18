/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 20:09:08 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/18 18:04:30 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"
#include <pthread.h>
#include <stdbool.h>

bool	are_all_philos_done(t_table *table)
{
	bool	ret;

	pthread_mutex_lock(&table->write_lock);
	ret = false;
	if (table->full_philo_n >= table->philo_n)
		ret = true;
	pthread_mutex_unlock(&table->write_lock);
	return (ret);
}

bool	someone_died(t_table *table)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(&table->death_lock);
	if (table->someone_died)
		ret = true;
	pthread_mutex_unlock(&table->death_lock);
	return (ret);
}

void	update_full_philos(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&table->write_lock);
	if (philo->meals_count == table->max_meal_n)
		table->full_philo_n++;
	pthread_mutex_unlock(&table->write_lock);
}
