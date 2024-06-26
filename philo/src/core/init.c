/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:51:07 by astavrop          #+#    #+#             */
/*   Updated: 2024/06/26 17:57:33 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"
#include "../../inc/colors.h"

#include <bits/pthreadtypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static int	initialize_forks(t_data	*data);
static void	assign_values_to_philo(t_data *data, t_philo *philo, int i);

int	initialize_philos(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	data->philos = malloc(sizeof(t_philo *) * data->philo_n_fork_num);
	if (!data->philos)
		return (dprintf(2, "malloc failed at %s:%d\n", __FILE__, __LINE__));
	if (initialize_forks(data) != 0)
		return (-1);
	while (i < data->philo_n_fork_num)
	{
		philo = malloc(sizeof(*philo));
		if (!philo)
			return (dprintf(2, "malloc failed at %s:%d\n", __FILE__, __LINE__));
		assign_values_to_philo(data, philo, i);
		i++;
	}
	return (0);
}

static int	initialize_forks(t_data	*data)
{
	pthread_mutex_t	*fork;
	int				i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_n_fork_num);
	if (!data->forks)
		return (dprintf(2, "malloc failed at %s:%d\n", __FILE__, __LINE__));
	while (i < data->philo_n_fork_num)
	{
		fork = malloc(sizeof(*fork));
		if (!fork)
			return (dprintf(2, "malloc failed at %s:%d\n", __FILE__, __LINE__));
		data->forks[i] = fork;
		i++;
	}
	return (0);
}

static void	assign_values_to_philo(t_data *data, t_philo *philo, int i)
{
	philo->data = data;
	philo->state = THINKING;
	philo->id = i;
	philo->meals_count = 0;
	philo->right_fork = data->forks[(i + 1) % data->philo_n_fork_num];
	philo->left_fork = data->forks[i];
	data->philos[i] = philo;
}
