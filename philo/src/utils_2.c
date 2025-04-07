/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:33:20 by pmachado          #+#    #+#             */
/*   Updated: 2025/04/07 15:08:34 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	has_philo_died(t_table *table, int i)
{
	uint64_t	now;
	uint64_t	last_meal;

	now = current_time_ms();
	pthread_mutex_lock(&table->bigbrains[i].mtx_last_meal_time);
	last_meal = table->bigbrains[i].last_meal_time;
	pthread_mutex_unlock(&table->bigbrains[i].mtx_last_meal_time);
	if (now - last_meal >= (uint64_t)table->time_to_die)
		return (true);
	return (false);
}

bool	check_any_philo_died(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nbr_thinkers)
	{
		if (!table->someone_died && has_philo_died(table, i))
		{
			log_philo_status(table, table->bigbrains[i].id, "died");
			end_simulation(table);
			return (true);
		}
	}
	return (false);
}

bool	check_philo_full(t_bigbrain *philo)
{
	bool	is_full;

	pthread_mutex_lock(&philo->mtx_meals_eaten);
	is_full = (philo->meals_eaten >= philo->table->must_eat_count);
	pthread_mutex_unlock(&philo->mtx_meals_eaten);
	return (is_full);
}

bool	handle_meal(t_bigbrain *ph)
{
	if (!philo_take_forks(ph))
		return (false);
	philo_eat(ph);
	if (wait_time(ph, ph->table->time_to_eat))
	{
		philo_drop_forks(ph);
		return (false);
	}
	philo_drop_forks(ph);
	return (true);
}

bool	handle_rest(t_bigbrain *ph)
{
	philo_sleep(ph);
	if (wait_time(ph, ph->table->time_to_sleep))
		return (false);
	if (has_simulation_stopped(ph))
		return (false);
	philo_think(ph);
	usleep(100);
	return (true);
}
