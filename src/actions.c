/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:17:50 by pmachado          #+#    #+#             */
/*   Updated: 2025/04/01 00:18:54 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_bigbrain *ph)
{
	if (has_simulation_stopped(ph))
		return ;
	log_philo_status(ph->table, ph->id, "is thinking 🤔");
}

void philo_eat(t_bigbrain *ph)
{
    if (has_simulation_stopped(ph))
        return;
    pthread_mutex_lock(&ph->mtx_last_meal_time);
    ph->last_meal_time = current_time_ms();
    pthread_mutex_unlock(&ph->mtx_last_meal_time);
    pthread_mutex_lock(&ph->mtx_meals_eaten);
    ph->meals_eaten++;
    pthread_mutex_unlock(&ph->mtx_meals_eaten);
    log_philo_status(ph->table, ph->id, "is eating 🍝");
}

void	philo_sleep(t_bigbrain *ph)
{
	if (has_simulation_stopped(ph))
		return ;
	log_philo_status(ph->table, ph->id, "is sleeping 😴");
}

// bool philo_take_forks(t_bigbrain *ph)
// {
// 	if (has_simulation_stopped(ph))
// 		return (false);
// 	if (ph->id % 2 == 0)
// 	{
// 		pthread_mutex_lock(ph->right_fork);
// 		log_philo_status(ph->table, ph->id, "took the right fork 🍴");
// 		pthread_mutex_lock(ph->left_fork);
// 		log_philo_status(ph->table, ph->id, "took the left fork 🍴");
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(ph->left_fork);
// 		log_philo_status(ph->table, ph->id, "took the left fork 🍴");
// 		pthread_mutex_lock(ph->right_fork);
// 		log_philo_status(ph->table, ph->id, "took the right fork 🍴");
// 	}
// 	return (true);
// }

bool philo_take_forks(t_bigbrain *ph)
{
	bool got_left = false;
	bool got_right = false;

	if (has_simulation_stopped(ph))
		return (false);

	if (ph->id % 2 == 0)
	{
		if (has_simulation_stopped(ph))
			return (false);
		printf("🔐 Philo %d locking RIGHT fork (%p)\n", ph->id, (void *)ph->right_fork);
		pthread_mutex_lock(ph->right_fork);
		got_right = true;

		if (has_simulation_stopped(ph))
			goto cleanup;
		log_philo_status(ph->table, ph->id, "took the right fork 🍴");

		if (has_simulation_stopped(ph))
			goto cleanup;
		printf("🔐 Philo %d locking LEFT fork (%p)\n", ph->id, (void *)ph->left_fork);
		pthread_mutex_lock(ph->left_fork);
		got_left = true;

		if (has_simulation_stopped(ph))
			goto cleanup;
		log_philo_status(ph->table, ph->id, "took the left fork 🍴");
	}
	else
	{
		if (has_simulation_stopped(ph))
			return (false);
		printf("🔐 Philo %d locking LEFT fork (%p)\n", ph->id, (void *)ph->left_fork);
		pthread_mutex_lock(ph->left_fork);
		got_left = true;

		if (has_simulation_stopped(ph))
			goto cleanup;
		log_philo_status(ph->table, ph->id, "took the left fork 🍴");

		if (has_simulation_stopped(ph))
			goto cleanup;
		printf("🔐 Philo %d locking RIGHT fork (%p)\n", ph->id, (void *)ph->right_fork);
		pthread_mutex_lock(ph->right_fork);
		got_right = true;

		if (has_simulation_stopped(ph))
			goto cleanup;
		log_philo_status(ph->table, ph->id, "took the right fork 🍴");
	}
	return (true);

cleanup:
	if (got_left)
		pthread_mutex_unlock(ph->left_fork);
	if (got_right)
		pthread_mutex_unlock(ph->right_fork);
	return (false);
}

void philo_drop_forks(t_bigbrain *ph)
{
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
}


