/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:41:11 by astavrop          #+#    #+#             */
/*   Updated: 2024/05/19 18:25:23 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <bits/pthreadtypes.h>
# include <stdbool.h>

# define SUCCESS 0
# define FAIL 1
# define NOT_ENOUGH_ARGS_MSG "not enough arguments"
# define ERR_NOT_ENOUGH_ARGS 20
# define TOO_MANY_ARGS_MSG "too many arguments"
# define ERR_TOO_MANY_ARGS 21
# define NON_DIGIT_ARG_MSG "argument contains non-digit chracter(s)"
# define ERR_NON_DIGIT_ARG 22

struct	s_data;

struct	s_philo
{
	struct				*s_data;
	pthread_t			thrd;
	int					id;
	int					meals_count;
	bool				eating;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
};

struct	s_data
{
	int					philo_n_fork_num;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_meal_num;
	pthread_t			*tlist;
	pthread_mutex_t		*forks;
};

/* Core functions */

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
int			validate_input(int ac, char *av[]);

/* Utility functions */

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
int			ft_strisnum(const char *str);

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
int			ft_atoi(const char *arg);

#endif /* PHILO_H */
