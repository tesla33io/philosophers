/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:06:26 by astavrop          #+#    #+#             */
/*   Updated: 2024/06/08 20:17:04 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> /* printf() */

void	print_usage(void)
{
	printf("\nUsage: philo <* number_of_philosophers> ");
	printf("<* time_to_die> <* time_to_eat> <* time_to_sleep> ");
	printf("<? number_of_times_each_philosopher_must_eat>\n");
	printf("\n\t<*> - mandatory\n\t<?> - optional\n");
}
