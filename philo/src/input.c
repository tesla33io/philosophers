/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:44:49 by astavrop          #+#    #+#             */
/*   Updated: 2024/05/19 19:54:50 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

#include <stdio.h> /* printf() */
#include <stdlib.h> /* malloc() */

static int	check_arguments(int ac, char *av[]);

int	validate_input(int ac, char *av[])
{
	if (ac < 5)
	{
		printf("Error: %s %d\n", NOT_ENOUGH_ARGS_MSG, ac - 1);
		return (ERR_NOT_ENOUGH_ARGS);
	}
	else if (ac > 6)
	{
		printf("Error: %s %d\n", TOO_MANY_ARGS_MSG, ac - 1);
		return (ERR_TOO_MANY_ARGS);
	}
	if (check_arguments(ac, av) != SUCCESS)
		return (ERR_NON_DIGIT_ARG);
	return (SUCCESS);
}

struct s_data	*save_arguments(int ac, char *av[])
{
	struct s_data	*data;

	data = malloc(sizeof(*data));
	if (!data)
	{
		printf("[%s:%d] Error: %s\n", __FILE__, __LINE__, MALLOC_FAIL_MSG);
		return (NULL);
	}
	data->philo_n_fork_num = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->max_meal_num = -1;
	if (ac == 6)
		data->max_meal_num = ft_atoi(av[5]);
	return (data);
}

static int	check_arguments(int ac, char *av[])
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_strisnum(av[i]) != SUCCESS)
		{
			printf("Error: %s: %s\n", NON_DIGIT_ARG_MSG, av[i]);
			return (ERR_NON_DIGIT_ARG);
		}
		i++;
	}
	return (SUCCESS);
}
