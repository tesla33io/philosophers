/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:51:07 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/18 22:19:41 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"
#include "../../inc/colors.h"

#include <bits/pthreadtypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static int	initialize_forks(t_table *table);
static void	assign_values_to_philo(t_table *table, t_philo *philo, int i);

int	initialize_philos(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	table->philos = malloc(sizeof(t_philo *) * table->philo_n);
	if (!table->philos)
		return (malloc_failed(__FILE_NAME__, (char *) __func__));
	if (initialize_forks(table) != 0)
		return (-1);
	while (i < table->philo_n)
	{
		philo = malloc(sizeof(*philo));
		if (!philo)
			return (malloc_failed(__FILE_NAME__, (char *) __func__));
		assign_values_to_philo(table, philo, i);
		i++;
	}
	return (0);
}

static int	initialize_forks(t_table *table)
{
	pthread_mutex_t	*fork;
	int				i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_n + 1);
	if (!table->forks)
		return (malloc_failed(__FILE_NAME__, (char *) __func__));
	while (i < table->philo_n)
	{
		fork = malloc(sizeof(*fork));
		if (!fork)
			return (malloc_failed(__FILE_NAME__, (char *) __func__));
		table->forks[i] = fork;
		if (pthread_mutex_init(table->forks[i], NULL) != 0)
			return (mutex_init_failed(__FILE_NAME__, (char *) __func__));
		i++;
	}
	table->forks[i] = NULL;
	return (0);
}

static void	assign_values_to_philo(t_table *table, t_philo *philo, int i)
{
	philo->table = table;
	philo->state = THINKING;
	philo->id = i;
	philo->meals_count = 0;
	philo->last_meal_time = timestamp();
	philo->right_fork = table->forks[(i + 1) % table->philo_n];
	philo->left_fork = table->forks[i];
	if (pthread_mutex_init(&philo->p_write_lock, NULL) != 0
		&& mutex_init_failed(__FILE_NAME__, (char *) __func__))
		return ;
	if (pthread_mutex_init(&philo->p_state_lock, NULL) != 0
		&& mutex_init_failed(__FILE_NAME__, (char *) __func__))
		return ;
	table->philos[i] = philo;
}
