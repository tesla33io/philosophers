/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:29:48 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/11 22:43:43 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"
#include <pthread.h>
#include <unistd.h>

#include <stdio.h> /* TODO: DELETE */

static int	check_for_starvation(t_table *table);
static int	stop_simulation(t_table *table);

/* Initialize monitoring thread */
void	*wake_up_big_brother(void *table_ref)
{
	t_table	*table;
	int		ret;

	table = (t_table *) table_ref;
	pthread_mutex_lock(&table->ready_lock);
	pthread_mutex_unlock(&table->ready_lock);
	while (1)
	{
		ret = check_for_starvation(table);
		if (ret != 0)
		{
			starvation_time(table->philos[ret - 1]);
			return (NULL);
		}
		pthread_mutex_lock(&table->write_lock);
		if (table->full_philo_n >= table->philo_n)
		{
			pthread_mutex_unlock(&table->write_lock);
			stop_simulation(table);
			break ;
		}
		pthread_mutex_unlock(&table->write_lock);
		usleep(10);
	}
	return (NULL);
}

static int	check_for_starvation(t_table *table)
{
	int			i;
	long int	t_diff;

	i = 0;
	while (i < table->philo_n)
	{
		if (p_get_last_meal_t(table->philos[i]) > 0)
		{
			t_diff = timestamp() - p_get_last_meal_t(table->philos[i]);
			if (p_get_state(table->philos[i]) == DEAD || t_diff >= table->t_die)
				return (i + 1);
		}
		i++;
	}
	return (0);
}

static int	stop_simulation(t_table *table)
{
	int	err;
	int	i;

	err = 0;
	i = 0;
	while (i < table->philo_n)
		err |= pthread_detach(table->philos[i]->thrd);
	err |= destroy_table(table);
	return (err);
}
