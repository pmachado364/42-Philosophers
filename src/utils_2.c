/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:52:26 by pmachado          #+#    #+#             */
/*   Updated: 2025/03/31 16:18:34 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_time(t_bigbrain *ph, uint64_t time)
{
	uint64_t	now;
	uint64_t	deadline;
	uint64_t	time_to_die;

	now = current_time_ms();
	pthread_mutex_lock(&ph->mtx_last_meal_time);
	deadline = ph->last_meal_time + ph->table->time_to_die;
	pthread_mutex_unlock(&ph->mtx_last_meal_time);
	if (deadline > now)
		time_to_die = deadline - now;
	else
		time_to_die = 0;
	if (time >= time_to_die)
		usleep(time_to_die * 1000);
	else
		usleep(time * 1000);
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
