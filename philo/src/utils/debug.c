/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 22:02:33 by astavrop          #+#    #+#             */
/*   Updated: 2024/06/30 21:17:09 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

#include <stdio.h> /* printf() */

#define MARK "[\033[33;1mDEBUG\033[0m]::: \033[0m"

void	print_table(t_table *table)
{
	printf("%sNumber of philos: %d\n", MARK, table->philo_n);
	printf("%sDie\t| Eat\t| Sleep\n", MARK);
	printf("%s%ld\t| %ld\t| %ld\n", MARK, table->t_die, table->t_eat,
		table->t_sleep);
}

void	print_philo(t_philo *philo)
{
	char	*states[] = {"eating", "sleeping", "thinking", "dead"};
	printf("%sState: %s\n", MARK, states[philo->state]);
	printf("%sTID: %ld | PID: %d\n", MARK, philo->thrd, philo->id + 1);
	printf("%sMeals: %d (last time: %ld)\n", MARK, philo->meals_count,
			philo->last_meal_time);
	printf("%sMutexes:\n", MARK);
	printf("%s\tL_F: %p | R_F: %p\n", MARK, (void *) philo->left_fork,
			(void *) philo->right_fork);
	printf("%s\tWR: %p | ST: %p\n", MARK, (void *) &philo->p_write_lock,
			(void *) &philo->p_state_lock);
}
