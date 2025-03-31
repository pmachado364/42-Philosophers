/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:17:50 by pmachado          #+#    #+#             */
/*   Updated: 2025/03/31 16:19:01 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_bigbrain *ph)
{
	if (has_simulation_stopped(ph))
		return ;
	printf("[%lu] 🤔 Philosopher %d is thinking.\n", current_time_ms(), ph->id);
}

void	philo_eat(t_bigbrain *ph)
{
	pthread_mutex_lock(&ph->mtx_last_meal_time);
	ph->last_meal_time = current_time_ms();
	pthread_mutex_unlock(&ph->mtx_last_meal_time);
	pthread_mutex_lock(&ph->mtx_meals_eaten);
	ph->meals_eaten++;
	pthread_mutex_unlock(&ph->mtx_meals_eaten);
	printf("[%lu] 🍝 Philosopher %d is eating.\n", current_time_ms(), ph->id);
}

void	philo_sleep(t_bigbrain *ph)
{
	if (has_simulation_stopped(ph))
		return ;
	printf("[%lu] 😴 Philo %d is sleeping...\n", current_time_ms(), ph->id);
}

bool	philo_take_forks(t_bigbrain *ph)
{
	if (has_simulation_stopped(ph))
		return (false);
	if (ph->id % 2 == 0)
	{
		pthread_mutex_lock(ph->right_fork);
		printf("[%lu] 🍴 Philosopher %d took the right fork\n",
			current_time_ms(), ph->id);
		pthread_mutex_lock(ph->left_fork);
		printf("[%lu] 🍴 Philosopher %d took the left fork\n",
			current_time_ms(), ph->id);
	}
	else
	{
		pthread_mutex_lock(ph->left_fork);
		printf("[%lu] 🍴 Philosopher %d took the left fork\n",
			current_time_ms(), ph->id);
		pthread_mutex_lock(ph->right_fork);
		printf("[%lu] 🍴 Philosopher %d took the right fork\n",
			current_time_ms(), ph->id);
	}
	return (true);
}

void	philo_drop_forks(t_bigbrain *ph)
{
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
}
