/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:00:02 by astavrop          #+#    #+#             */
/*   Updated: 2024/06/04 23:02:06 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

/**
 * @brief Checks if a string contains only digit characters.
 *
 * This function iterates through the given string and verifies whether each 
 * character is a digit ('0' to '9'). If the string is composed entirely of 
 * digits, the function returns SUCCESS (0). If any non-digit characters are 
 * found, it returns FAIL (1).
 *
 * @param str The input string to be checked.
 * @return int Returns SUCCESS (0) if the string contains only digits, 
 *         otherwise returns FAIL (1).
 */
int	ft_strisnum(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}
