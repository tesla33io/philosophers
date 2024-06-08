/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 22:02:33 by astavrop          #+#    #+#             */
/*   Updated: 2024/06/08 22:08:06 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

#include <stdio.h> /* printf() */

#define MARK "[\033[33;1mDEBUG\033[0m]::: \033[0m"

void	print_data(t_data *data)
{
	printf("%sNumber of philos: %d\n", MARK, data->philo_n_fork_num);
	printf("%sDie\t| Eat\t| Sleep\n", MARK);
	printf("%s%d\t| %d\t| %d\n", MARK, data->time_to_die, data->time_to_eat,
			data->time_to_sleep);
}
