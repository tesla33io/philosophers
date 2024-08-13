/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:51:07 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/11 21:45:20 by astavrop         ###   ########.fr       */
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
		return (dprintf(2, "malloc failed at %s:%d\n", __FILE__, __LINE__));
	if (initialize_forks(table) != 0)
		return (-1);
	while (i < table->philo_n)
	{
		philo = malloc(sizeof(*philo));
		if (!philo)
			return (dprintf(2, "malloc failed at %s:%d\n", __FILE__, __LINE__));
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
		return (dprintf(2, "malloc failed at %s:%d\n", __FILE__, __LINE__));
	while (i < table->philo_n)
	{
		fork = malloc(sizeof(*fork));
		if (!fork)
			return (dprintf(2, "malloc failed at %s:%d\n", __FILE__, __LINE__));
		table->forks[i] = fork;
		i++;
	}
	table->forks[i] = NULL;
	return (0);
}

static void	assign_values_to_philo(t_table *table, t_philo *philo, int i)
{
	philo->table = table;
	p_set_state(philo, THINKING);
	philo->id = i;
	philo->meals_count = 0;
	philo->right_fork = table->forks[(i + 1) % table->philo_n];
	philo->left_fork = table->forks[i];
	if (pthread_mutex_init(&philo->p_write_lock, NULL) != 0
		&& dprintf(2, "mutex init failed at %s:%d\n", __FILE__, __LINE__))
		return ;
	if (pthread_mutex_init(&philo->p_state_lock, NULL) != 0
		&& dprintf(2, "mutex init failed at %s:%d\n", __FILE__, __LINE__))
		return ;
	table->philos[i] = philo;
}
