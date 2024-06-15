/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:51:07 by astavrop          #+#    #+#             */
/*   Updated: 2024/06/15 22:23:48 by astavrop         ###   ########.fr       */
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
	if (i < data->philo_n_fork_num - 1)
		philo->right_fork = data->forks[i + 1];
	else
		philo->right_fork = data->forks[0];
	philo->left_fork = data->forks[i];
	data->philos[i] = philo;
}

/*static void	*say_hi(void *philo_ref)
{
	t_philo	*philo;

	philo = philo_ref;
	pthread_mutex_lock(&philo->data->print_lock);
	printf("Philo [%d] status - %d\n", philo->id, philo->state);
	printf("L_fork addr: %s%p%s | R_fork addr: %s%p%s\n",
		GRN, (void *) philo->left_fork, R, YEL, (void *) philo->right_fork, R);
	pthread_mutex_unlock(&philo->data->print_lock);
	return (NULL);
}*/
