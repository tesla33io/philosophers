/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:41:23 by astavrop          #+#    #+#             */
/*   Updated: 2024/05/19 19:54:23 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

#include <stdio.h> /* printf() */

/*
 * The only true wisdom is in knowing you know nothing.
 * (c) Socrates
 */
int	main(int ac, char *av[])
{
	struct s_data	*data;

	if (validate_input(ac, av) != SUCCESS)
		return (FAIL);
	data = save_arguments(ac, av);
	if (!data)
		return (FAIL);
	printf("Philos num: %d\n", data->philo_n_fork_num);
	printf("Time to die: %d\n", data->time_to_die);
	printf("Time to eat: %d\n", data->time_to_eat);
	printf("Time to sleep: %d\n", data->time_to_sleep);
	printf("Max meal num: %d\n", data->max_meal_num);
	return (SUCCESS);
}
