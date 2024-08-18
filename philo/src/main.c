/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:41:23 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/18 20:52:40 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

static int	start_simulation(t_table *table);
static int	init_table_mutexes(t_table *table);

/*
 * The only true wisdom is in knowing you know nothing.
 * (c) Socrates
 */
int	main(int ac, char *av[])
{
	t_table	*table;

	if (validate_input(ac, av) != SUCCESS && (print_usage(), 1))
		return (FAIL);
	table = malloc(sizeof(*table));
	if (!table)
		return (dprintf(2, "malloc failed at %s:%d\n", __FILE__, __LINE__));
	table->philo_n = ft_atoi(av[1]);
	table->t_die = ft_atoi(av[2]);
	table->t_eat = ft_atoi(av[3]);
	table->t_sleep = ft_atoi(av[4]);
	table->max_meal_n = -1;
	table->someone_died = false;
	table->full_philo_n = 0;
	if (ac == 6)
		table->max_meal_n = ft_atoi(av[5]);
	if (init_table_mutexes(table) == FAIL)
		return (FAIL);
	initialize_philos(table);
	start_simulation(table);
	free(table->philos);
	free(table->forks);
	free(table);
	return (ac);
}

static int	start_simulation(t_table *table)
{
	int	i;

	i = 0;
	if (!table)
		return (-1);
	table->t_start = timestamp();
	pthread_mutex_lock(&table->ready_lock);
	pthread_create(&table->monitor_thrd, NULL,
		wake_up_big_brother, (void *) table);
	while (i < table->philo_n)
	{
		pthread_create(&table->philos[i]->thrd, NULL, philo_routine,
			(void *) table->philos[i]);
		i++;
	}
	pthread_mutex_unlock(&table->ready_lock);
	i = 0;
	while (i < table->philo_n)
	{
		pthread_join(table->philos[i]->thrd, NULL);
		destroy_philo(table->philos[i]);
		i++;
	}
	pthread_join(table->monitor_thrd, NULL);
	return (SUCCESS);
}

bool	check_if_someone_died(t_table *table)
{
	bool	ret;

	pthread_mutex_lock(&table->death_lock);
	ret = table->someone_died;
	pthread_mutex_unlock(&table->death_lock);
	return (ret);
}

static int	init_table_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
		return (mutex_init_failed(__FILE__, (char *) __FUNCTION__));
	if (pthread_mutex_init(&table->death_lock, NULL) != 0)
		return (mutex_init_failed(__FILE__, (char *) __FUNCTION__));
	if (pthread_mutex_init(&table->write_lock, NULL) != 0)
		return (mutex_init_failed(__FILE__, (char *) __FUNCTION__));
	if (pthread_mutex_init(&table->ready_lock, NULL) != 0)
		return (mutex_init_failed(__FILE__, (char *) __FUNCTION__));
	return (SUCCESS);
}
