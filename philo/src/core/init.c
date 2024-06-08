/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:51:07 by astavrop          #+#    #+#             */
/*   Updated: 2024/06/08 22:36:57 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static void	*say_hi(void *philo_ref);

int	initialize_philos(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	data->philos = malloc(sizeof(t_philo *) * data->philo_n_fork_num);
	if (!data->philos)
		return (dprintf(2, "malloc failed at %s:%d\n", __FILE__, __LINE__));
	while (i < data->philo_n_fork_num)
	{
		philo = malloc(sizeof(*philo));
		if (!philo)
			return (dprintf(2, "malloc failed at %s:%d\n", __FILE__, __LINE__));
		philo->id = i;
		philo->status = DEAD;
		philo->data = data;
		data->philos[i] = philo;
		pthread_create(&philo->thrd, NULL, say_hi, (void *) philo);
		pthread_join(philo->thrd, NULL);
		i++;
	}
	return (0);
}

static void	*say_hi(void *philo_ref)
{
	t_philo	*philo;

	philo = philo_ref;
	pthread_mutex_lock(&philo->data->print_lock);
	printf("Philo [%d] status - %d\n", philo->id, philo->status);
	pthread_mutex_unlock(&philo->data->print_lock);
	return (NULL);
}
