/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:41:11 by astavrop          #+#    #+#             */
/*   Updated: 2024/06/27 21:52:20 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <time.h>

# define SUCCESS 0
# define FAIL 1
# define NOT_ENOUGH_ARGS_MSG "not enough arguments"
# define ERR_NOT_ENOUGH_ARGS 20
# define TOO_MANY_ARGS_MSG "too many arguments"
# define ERR_TOO_MANY_ARGS 21
# define NON_DIGIT_ARG_MSG "argument contains non-digit chracter(s)"
# define ERR_NON_DIGIT_ARG 22

# define FORK_TAKEN_MSG "has taken a fork"
# define DIED_MSG "died"

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

enum	e_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD
};

struct	s_philo
{
	t_data				*data;
	enum e_state		state;
	pthread_t			thrd;
	int					id;
	int					meals_count;
	time_t				last_meal_time;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
};

struct	s_data
{
	int					philo_n_fork_num;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	time_t				start_time;
	int					max_meal_num;
	bool				someone_died;
	int					full_philo_n;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		death_lock;
	pthread_mutex_t		write_lock;
	struct s_philo		**philos;
	pthread_mutex_t		**forks;
};

/* Core functions */

int			validate_input(int ac, char *av[]);
int			initialize_philos(t_data *data);

void		log_state(t_philo *philo);
void		log_action(t_philo *philo, char *act);

void		*philo_routine(void *philo_ref);
void		mealtime(t_philo *philo);
void		starvation_time(t_philo *philo);

/* Utility functions */

int			ft_strisnum(const char *str);
int			ft_atoi(const char *arg);
void		print_usage(void);
time_t		timestamp(void);
int			wait_for(time_t wait_time, t_philo *philo);

/* Debug functions */

void		print_data(t_data *data);

#endif /* PHILO_H */
