/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:17:50 by pmachado          #+#    #+#             */
/*   Updated: 2025/04/04 20:12:34 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_bigbrain *ph)
{
	if (has_simulation_stopped(ph))
		return ;
	log_philo_status(ph->table, ph->id, "is thinking");
}

void	philo_eat(t_bigbrain *ph)
{
	if (has_simulation_stopped(ph))
		return ;
	pthread_mutex_lock(&ph->mtx_last_meal_time);
	ph->last_meal_time = current_time_ms();
	pthread_mutex_unlock(&ph->mtx_last_meal_time);
	pthread_mutex_lock(&ph->mtx_meals_eaten);
	ph->meals_eaten++;
	pthread_mutex_unlock(&ph->mtx_meals_eaten);
	ph->has_eaten_once = true;
	log_philo_status(ph->table, ph->id, "is eating");
}

void	philo_sleep(t_bigbrain *ph)
{
	if (has_simulation_stopped(ph))
		return ;
	log_philo_status(ph->table, ph->id, "is sleeping");
}

// bool	philo_take_forks(t_bigbrain *ph)
// {
// 	if (has_simulation_stopped(ph))
// 		return (false);
// 	if (ph->id % 2 == 0)
// 	{
// 		pthread_mutex_lock(ph->right_fork);
// 		log_philo_status(ph->table, ph->id, "took the right fork");
// 		pthread_mutex_lock(ph->left_fork);
// 		log_philo_status(ph->table, ph->id, "took the left fork");
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(ph->left_fork);
// 		log_philo_status(ph->table, ph->id, "took the left fork");
// 		pthread_mutex_lock(ph->right_fork);
// 		log_philo_status(ph->table, ph->id, "took the right fork");
// 	}
// 	if (has_simulation_stopped(ph))
// 	{
// 		pthread_mutex_unlock(ph->left_fork);
// 		pthread_mutex_unlock(ph->right_fork);
// 		return (false);
// 	}
// 	return (true);
// }

bool	philo_take_forks(t_bigbrain *ph)
{
	if (has_simulation_stopped(ph))
		return (false);
	if (ph->id % 2 == 0)
	{
		pthread_mutex_lock(ph->right_fork);
		log_philo_status(ph->table, ph->id, "has taken a fork");
		pthread_mutex_lock(ph->left_fork);
		log_philo_status(ph->table, ph->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(ph->left_fork);
		log_philo_status(ph->table, ph->id, "has taken a fork");
		pthread_mutex_lock(ph->right_fork);
		log_philo_status(ph->table, ph->id, "has taken a fork");
	}
	if (has_simulation_stopped(ph))
	{
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);
		return (false);
	}
	return (true);
}

void	philo_drop_forks(t_bigbrain *ph)
{
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
}
