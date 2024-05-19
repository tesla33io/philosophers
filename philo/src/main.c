/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:41:23 by astavrop          #+#    #+#             */
/*   Updated: 2024/05/19 17:33:36 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

#include <stdio.h>

/*
 * The only true wisdom is in knowing you know nothing.
 * (c) Socrates
 */
int	main(int ac, char *av[])
{
	if (validate_input(ac, av) != SUCCESS)
		return (FAIL);
	for (int i = 1; i < ac; i++)
	{
		int num = ft_atoi(av[i]);
		printf("[%d]: %d\n", i, num);
	}
	return (ac);
}
