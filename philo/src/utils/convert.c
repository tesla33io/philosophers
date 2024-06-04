/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:27:44 by astavrop          #+#    #+#             */
/*   Updated: 2024/06/04 23:02:39 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Converts a string to an integer.
 *
 * This function takes a string representing a numerical value and converts it
 * into an integer. It processes each character in the string, assuming
 * all characters are digits ('0' to '9'), and computes the corresponding
 * integer value. The function does not handle negative numbers or non-digit
 * characters, and it assumes the input string is properly formatted.
 *
 * @param arg The input string to be converted to an integer.
 * @return int The integer value represented by the input string.
 */
int	ft_atoi(const char *arg)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (arg[i])
	{
		num = num * 10 + arg[i] - '0';
		i++;
	}
	return (num);
}
