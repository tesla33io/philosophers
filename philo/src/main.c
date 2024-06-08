/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:41:23 by astavrop          #+#    #+#             */
/*   Updated: 2024/06/08 22:09:01 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
 * The only true wisdom is in knowing you know nothing.
 * (c) Socrates
 */
int	main(int ac, char *av[])
{
	t_data	*data;

	if (validate_input(ac, av) != SUCCESS && (print_usage(), 1))
		return (FAIL);
	data = malloc(sizeof(*data));
	if (!data)
		return (dprintf(2, "malloc failed at %s:%d\n", __FILE__, __LINE__));
	data->philo_n_fork_num = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	print_data(data);
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (dprintf(2, "mutex init failed at %s:%d\n", __FILE__, __LINE__));
	if (ac == 6)
		data->max_meal_num = ft_atoi(av[5]);
	initialize_philos(data);
	return (ac);
}
