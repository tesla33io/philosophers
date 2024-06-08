/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:44:49 by astavrop          #+#    #+#             */
/*   Updated: 2024/06/08 21:20:59 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

#include <stdio.h> /* printf() */

static int	check_arguments(int ac, char *av[]);

/**
 * @brief Validates program arguments.
 *
 * This function checks the number and format of the program arguments. 
 * It ensures that there are exactly four mandatory arguments and one optional 
 * argument. The function returns different error codes based on the validation
 * outcome:
 * - ERR_NOT_ENOUGH_ARGS (20): If the program has fewer than the required
 *                             number of arguments.
 * - ERR_TOO_MANY_ARGS (21): If more arguments are provided than needed.
 * - ERR_NON_DIGIT_ARG (22): If any of the arguments contain non-digit
 *                           characters.
 * - SUCCESS (0): If all arguments are valid.
 *
 * @param ac The argument count.
 * @param av The argument vector.
 * @return int Error code indicating the validation result.
 */
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
