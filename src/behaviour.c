/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behaviour.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:48:33 by pmachado          #+#    #+#             */
/*   Updated: 2025/03/31 16:30:14 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_behavior(void *philo)
{
	t_bigbrain	*ph;

	ph = (t_bigbrain *)philo;
	if (ph->table->nbr_thinkers == 1)
	{
		printf("[%lu] 🍴 Philo %d took a fork\n", current_time_ms(), ph->id);
		usleep(ph->table->time_to_die * 1000);
		printf("[%lu] 💀 Philo %d died alone\n", current_time_ms(), ph->id);
		return (NULL);
	}
	while (!has_simulation_stopped(philo))
	{
		if (!routine(philo))
			break ;
	}
	return (NULL);
}

bool	routine(t_bigbrain *ph)
{
	if (has_simulation_stopped(ph))
		return (false);
	philo_take_forks(ph);
	philo_eat(ph);
	wait_time(ph, ph->table->time_to_eat);
	if (has_simulation_stopped(ph))
	{
		philo_drop_forks(ph);
		return (false);
	}
	philo_drop_forks(ph);
	philo_sleep(ph);
	wait_time(ph, ph->table->time_to_sleep);
	philo_think(ph);
	usleep(500);
	return (true);
}
int	has_simulation_stopped(t_bigbrain *ph)
{
	pthread_mutex_lock(&ph->table->mtx_simulation);
	if (ph->table->someone_died)
	{
		pthread_mutex_unlock(&ph->table->mtx_simulation);
		return (1);
	}
	pthread_mutex_unlock(&ph->table->mtx_simulation);
	return (0);
}
