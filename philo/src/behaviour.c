/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behaviour.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:48:33 by pmachado          #+#    #+#             */
/*   Updated: 2025/04/05 13:45:19 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_behavior(void *philo)
{
	t_bigbrain	*ph;

	ph = (t_bigbrain *)philo;
	if (ph->table->nbr_thinkers == 1)
	{
		log_philo_status(ph->table, ph->id, "took a fork");
		usleep(ph->table->time_to_die * 1000);
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

bool	routine(t_bigbrain *ph)
{
	if (has_simulation_stopped(ph))
		return (false);
	if (!handle_priority(ph))
		return (false);
	if (!handle_meal(ph))
		return (false);
	if (has_simulation_stopped(ph))
		return (false);
	if (!handle_rest(ph))
		return (false);
	return (true);
}

bool	handle_priority(t_bigbrain *ph)
{
	int	priority_id;

	if (!ph->has_eaten_once)
		return (true);
	while (1)
	{
		pthread_mutex_lock(&ph->table->mtx_priority);
		priority_id = ph->table->most_starving_id;
		pthread_mutex_unlock(&ph->table->mtx_priority);
		if (priority_id == -1 || priority_id == ph->id)
			break ;
		if (has_simulation_stopped(ph))
			return (false);
		usleep(100);
	}
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
