/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:29:48 by astavrop          #+#    #+#             */
/*   Updated: 2024/07/11 17:19:36 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"
#include <pthread.h>
#include <unistd.h>

#include <stdio.h> /* TODO: DELETE */

static int	check_for_starvation(t_table *table);

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
		// printf("[d]:: ret - 1: %d\n", ret - 1);
		if (ret != 0)
		{
			// printf("BIG BRO\n");
			// printf("[d]:: LMT: %ld\n", p_get_last_meal_t(table->philos[ret - 1]));
			starvation_time(table->philos[ret - 1]);
			return (NULL);
		}
		if (table->full_philo_n >= table->philo_n)
			break ; /* stop simulation */
		usleep(50);
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
		t_diff = timestamp() - p_get_last_meal_t(table->philos[i]);
		// printf("\n\n[pid: %i]:: %ld - %ld", table->philos[i]->id + 1,
				// timestamp(), p_get_last_meal_t(table->philos[i]));
		// printf(" = %ld\n", t_diff);
		if (table->philos[i]->state == DEAD || t_diff >= table->t_die)
			return (i + 1);
		i++;
	}
	return (0);
}
