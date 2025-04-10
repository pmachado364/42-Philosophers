/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:49:33 by pmachado          #+#    #+#             */
/*   Updated: 2025/04/05 13:43:35 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdint.h>
# include "errors.h"

typedef struct s_bigbrain	t_bigbrain;
typedef struct s_table		t_table;

typedef struct s_bigbrain
{
	int					id;					//socrates ID number
	int					meals_eaten;		//number of meal the philosopher had
	bool				has_eaten_once;
	uint64_t			last_meal_time;		//timestamp of the last meal had
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		mtx_last_meal_time; //proteccs last_eat_time
	pthread_mutex_t		mtx_meals_eaten;	//proteccs meals_eaten
	t_table				*table;
	pthread_t			thread;				// thread ID
}	t_bigbrain;

typedef struct s_table
{
	int					nbr_thinkers;		//number of philos
	int					time_to_die;		//time left for a philo to die
	int					time_to_eat;		//eat duration
	int					time_to_sleep;		//sleep duration
	int					must_eat_count;		//Opt: Nbr meals before stopping
	int					most_starving_id;
	pthread_mutex_t		mtx_priority;
	uint64_t			start_time;			//referemce start time
	bool				someone_died;		//flag to indicate if a philo died
	pthread_mutex_t		*forks;				//array of forks
	pthread_mutex_t		mtx_prints;			//protecc the log print
	pthread_mutex_t		mtx_simulation;		//proteccs simulation state changes
	t_bigbrain			*bigbrains;			//array of philosophers
}	t_table;

/* parsing */
bool		ft_validate(int argc, char **argv);
bool		is_digit(int ac, char **av);
bool		check_values(int ac, char **av);

/* init */
t_table		*ft_start_dinner(int ac, char **av);
t_table		*ft_init_table(int ac, char **av);
void		ft_init_forks(t_table *table);
void		ft_init_philos(t_table *table);
void		init_philo_mutexes(t_bigbrain *ph, int i, t_table *table);

/* philos behaviour */
void		*philo_behavior(void *philo);
bool		routine(t_bigbrain *ph);
int			has_simulation_stopped(t_bigbrain *ph);
bool		handle_priority(t_bigbrain *ph);
bool		handle_meal(t_bigbrain *ph);
bool		handle_rest(t_bigbrain *ph);

/* actions */
void		philo_think(t_bigbrain *ph);
void		philo_eat(t_bigbrain *ph);
void		philo_sleep(t_bigbrain *ph);
bool		philo_take_forks(t_bigbrain *ph);
void		philo_drop_forks(t_bigbrain *ph);

/* thread creation and joining */
int			start_threads(t_table *table);
bool		check_philos(t_table *table);
bool		has_philo_died(t_table *table, int i);
bool		check_philo_full(t_bigbrain *philo);
bool		check_any_philo_died(t_table *table);
int			update_starving_id(t_table *table, uint64_t now);

/* utils */
int			ft_atoi(char *str);
uint64_t	current_time_ms(void);
bool		wait_time(t_bigbrain *ph, uint64_t ms);
bool		end_simulation(t_table *table);
void		log_philo_status(t_table *table, int philo_id, char *status);

/* clean-up */
void		ft_end(int code, t_table *table);
void		free_all(t_table *table);
void		free_forks(t_table *table);
void		free_bigbrains(t_table *table);

#endif