/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:41:23 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/18 22:19:03 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

static int	set_sim_settings(int ac, char *av[], t_table *table);
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
		return (malloc_failed(__FILE_NAME__, (char *) __func__));
	if (!set_sim_settings(ac, av, table))
	{
		free(table->philos);
		free(table->forks);
		free(table);
		return (0);
	}
	if (init_table_mutexes(table) == FAIL)
		return (FAIL);
	initialize_philos(table);
	start_simulation(table);
	free(table);
	return (0);
}

static int	start_simulation(t_table *t)
{
	int	i;

	i = 0;
	if (!t)
		return (-1);
	t->t_start = timestamp();
	pthread_mutex_lock(&t->ready_lock);
	pthread_create(&t->monitor_thrd, NULL, wake_up_big_brother, (void *) t);
	while (i < t->philo_n)
	{
		pthread_create(&t->philos[i]->thrd, NULL, philo_routine, t->philos[i]);
		i++;
	}
	pthread_mutex_unlock(&t->ready_lock);
	i = 0;
	while (i < t->philo_n)
	{
		pthread_join(t->philos[i]->thrd, NULL);
		i++;
	}
	pthread_join(t->monitor_thrd, NULL);
	destroy_forks(t);
	destroy_philos(t);
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

static int	set_sim_settings(int ac, char *av[], t_table *table)
{
	table->philo_n = ft_atoi(av[1]);
	table->t_die = ft_atoi(av[2]);
	table->t_eat = ft_atoi(av[3]);
	table->t_sleep = ft_atoi(av[4]);
	table->max_meal_n = -1;
	table->someone_died = false;
	table->full_philo_n = 0;
	if (ac == 6)
		table->max_meal_n = ft_atoi(av[5]);
	if (table->max_meal_n == 0)
		return (0);
	return (1);
}
