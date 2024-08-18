/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:41:11 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/18 20:53:53 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <time.h>

# include <stdio.h>
# include <string.h>

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
# define EAT_MSG "is eating"
# define SLEEP_MSG "is sleeping"
# define THINK_MSG "is thinking"

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

enum	e_state
{
	EATING = 42,
	SLEEPING = 43,
	THINKING = 44,
	DEAD = 45,
	FINISHED = 46
};

typedef enum e_state	t_state;

struct	s_philo
{
	t_table				*table;
	t_state				state;
	pthread_t			thrd;
	int					id;
	int					meals_count;
	time_t				last_meal_time;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		p_write_lock;
	pthread_mutex_t		p_state_lock;
};

struct	s_table
{
	int					philo_n;
	time_t				t_die;
	time_t				t_eat;
	time_t				t_sleep;
	time_t				t_start;
	int					max_meal_n;
	bool				someone_died;
	int					full_philo_n;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		death_lock;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		ready_lock;
	struct s_philo		**philos;
	pthread_mutex_t		**forks;
	pthread_t			monitor_thrd;
};

/* Core functions */

int			validate_input(int ac, char *av[]);
int			initialize_philos(t_table *table);

void		log_state(t_philo *philo, t_state state);
void		log_action(t_philo *philo, char *act);
time_t		p_get_last_meal_t(t_philo *philo);
void		p_set_last_meal_t(t_philo *philo, time_t time);
bool		check_if_someone_died(t_table *table);
t_state		p_get_state(t_philo *philo);
void		p_set_state(t_philo *philo, t_state state);

void		*wake_up_big_brother(void *table_ref);
void		*philo_routine(void *philo_ref);
void		mealtime(t_philo *philo);
void		starvation_time(t_philo *philo);
void		take_forks(t_philo *philo, t_table *table);
void		*alone_philo_simulation(t_philo *philo);

/* Utility functions */

int			ft_strisnum(const char *str);
int			ft_atoi(const char *arg);
void		print_usage(void);
time_t		timestamp(void);
int			wait_for(time_t wait_time, t_philo *philo, bool extra);
bool		are_all_philos_done(t_table *table);
void		update_full_philos(t_philo *philo, t_table *table);
size_t		ft_strlen(const char *s);
int			mutex_init_failed(char *file, char *func);
bool		someone_died(t_table *table);
int			destroy_philo(t_philo *philo);
int			destroy_table(t_table *table);

/* Debug functions */

void		print_table(t_table *table);
void		print_philo(t_philo *philo);

#endif /* PHILO_H */
