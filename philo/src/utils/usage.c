/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:06:26 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/15 16:01:32 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> /* printf() */

void	print_usage(void)
{
	printf("\nUsage: \033[32mphilo\033[0m ");
	printf("\033[41m*\033[30;46mnumber_of_philosophers\033[45m:int\033[0m ");
	printf("\033[41m*\033[30;46mtime_to_die\033[45m:int\033[0m ");
	printf("\033[41m*\033[30;46mtime_to_eat\033[45m:int\033[0m ");
	printf("\033[41m*\033[30;46mtime_to_sleep\033[45m:int\033[0m ");
	printf("\033[30;43m?\033[46mnumber_of_times_each_philosopher_must_eat");
	printf("\033[45m:int\033[0m\n");
	printf("\n\t\033[31m<*>\033[0m - mandatory\n");
	printf("\t\033[30;43m<?>\033[0m - optional\n");
}
