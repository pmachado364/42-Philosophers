/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behaviour.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:48:33 by pmachado          #+#    #+#             */
/*   Updated: 2025/04/01 00:21:54 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_behavior(void *philo)
{
	t_bigbrain	*ph;

	ph = (t_bigbrain *)philo;
	if (!ph || !ph->table)
	{
		printf("NULL pointer in philo_behavior\n");
		return (NULL);
	}
	if (ph->table->nbr_thinkers == 1)
	{
		log_philo_status(ph->table, ph->id, "took a fork 🍴");
		usleep(ph->table->time_to_die * 1000);
		log_philo_status(ph->table, ph->id, "died alone 💀");
		pthread_mutex_lock(&ph->table->mtx_simulation);
		ph->table->someone_died = true;
		pthread_mutex_unlock(&ph->table->mtx_simulation);
		return (NULL);
	}
	while (!has_simulation_stopped(ph))
	{
		if (!routine(ph))
			break ;
	}
	return (NULL);
}

bool routine(t_bigbrain *ph)
{
	if (has_simulation_stopped(ph))
		return (false);

	if (!philo_take_forks(ph))
		return (false);

	philo_eat(ph);
	if (wait_time(ph, ph->table->time_to_eat))
	{
		philo_drop_forks(ph);
		return (false); // simulation stopped mid-eating
	}

	philo_drop_forks(ph);

	if (has_simulation_stopped(ph))
		return (false);

	philo_sleep(ph);
	if (wait_time(ph, ph->table->time_to_sleep))
		return (false); // simulation stopped mid-sleep

	if (has_simulation_stopped(ph))
		return (false);

	philo_think(ph);
	usleep(500); // tiny delay for better interleaving
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
