/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:41:11 by astavrop          #+#    #+#             */
/*   Updated: 2024/06/09 14:39:03 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// # include <bits/pthreadtypes.h>
# include <pthread.h>
# include <stdbool.h>

# define SUCCESS 0
# define FAIL 1
# define NOT_ENOUGH_ARGS_MSG "not enough arguments"
# define ERR_NOT_ENOUGH_ARGS 20
# define TOO_MANY_ARGS_MSG "too many arguments"
# define ERR_TOO_MANY_ARGS 21
# define NON_DIGIT_ARG_MSG "argument contains non-digit chracter(s)"
# define ERR_NON_DIGIT_ARG 22

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

enum	e_status
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD
};

struct	s_philo
{
	t_data				*data;
	enum e_status		status;
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
	pthread_mutex_t		print_lock;
	struct s_philo		**philos;
	pthread_mutex_t		*forks;
};

/* Core functions */

int			validate_input(int ac, char *av[]);
int			initialize_philos(t_data *data);

/* Utility functions */

int			ft_strisnum(const char *str);
int			ft_atoi(const char *arg);
void		print_usage(void);

/* Debug functions */

void		print_data(t_data *data);

#endif /* PHILO_H */
