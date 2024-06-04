/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:41:11 by astavrop          #+#    #+#             */
/*   Updated: 2024/06/04 23:03:03 by astavrop         ###   ########.fr       */
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

typedef struct	s_data t_data;

struct	s_philo
{
	t_data				*data;
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

int			validate_input(int ac, char *av[]);

/* Utility functions */

int			ft_strisnum(const char *str);
int			ft_atoi(const char *arg);
void		print_usage(void);

#endif /* PHILO_H */
