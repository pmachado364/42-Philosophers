/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behaviour.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:48:33 by pmachado          #+#    #+#             */
/*   Updated: 2025/03/04 13:46:21 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_behavior(void *philo)
{
	t_bigbrain	*ph;

	ph = (t_bigbrain *)philo;
	printf("[%lu] 👤 Philosopher %d has started.\n", current_time_ms(), ph->id);
	if (ph->id % 2 == 0)
		usleep(ph->table->time_to_eat * 500);
	while (1)
	{
		pthread_mutex_lock(&ph->table->mtx_simulation);
		if (ph->table->someone_died)
		{
			pthread_mutex_unlock(&ph->table->mtx_simulation);
			printf("[%lu] 🚨 Philosopher %d is stopping due to death.\n",
				current_time_ms(), ph->id);
			return (NULL);
		}
		pthread_mutex_unlock(&ph->table->mtx_simulation);
		philo_eat(ph);
		philo_sleep(ph);
	}
	return (NULL);
}

void	philo_think(t_bigbrain *ph)
{
	pthread_mutex_lock(&ph->table->mtx_simulation);
	if (ph->table->someone_died)
	{
		pthread_mutex_unlock(&ph->table->mtx_simulation);
		return ;
	}
	pthread_mutex_unlock(&ph->table->mtx_simulation);
	printf("👤 Philosopher %d is thinking.\n", ph->id);
	usleep(500);
}

void	philo_eat(t_bigbrain *ph)
{
	philo_think(ph);
	if (ph->id % 2 == 0)
	{
		pthread_mutex_lock(ph->right_fork);
		printf("[%lu] 🍴 Philo %d took right fork\n", current_time_ms(), ph->id);
		pthread_mutex_lock(ph->left_fork);
	}
	else
	{
		pthread_mutex_lock(ph->left_fork);
		printf("[%lu] 🍴 Philo %d took left fork\n", current_time_ms(), ph->id);
		pthread_mutex_lock(ph->right_fork);
	}
	pthread_mutex_lock(&ph->mtx_last_meal_time);
	ph->last_meal_time = current_time_ms();
	pthread_mutex_unlock(&ph->mtx_last_meal_time);
	printf("[%lu] 🍝 Philosopher %d is eating.\n", current_time_ms(), ph->id);
	usleep(ph->table->time_to_eat * 800);
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_unlock(ph->left_fork);
}

void	philo_wait_turn(t_bigbrain *ph)
{
	if (ph->table->nbr_thinkers < 3)
		return ;
	while (1)
	{
		pthread_mutex_lock(&ph->table->mtx_simulation);
		if (ph->table->current_turn == ph->id)
		{
			pthread_mutex_unlock(&ph->table->mtx_simulation);
			break ;
		}
		pthread_mutex_unlock(&ph->table->mtx_simulation);
		usleep(500);
	}
}

void	philo_sleep(t_bigbrain *ph)
{
	printf("[%lu] 😴 Philo %d is sleeping...\n", current_time_ms(), ph->id);
	usleep(ph->table->time_to_sleep * 850);
}
