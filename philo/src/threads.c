/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:43:14 by pmachado          #+#    #+#             */
/*   Updated: 2025/04/04 16:07:03 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_threads(t_table *table)
{
	int	i;

	table->start_time = current_time_ms();
	i = 0;
	while (i < table->nbr_thinkers)
	{
		if (pthread_create(&table->bigbrains[i].thread, NULL,
				philo_behavior, (void *)&table->bigbrains[i]) != 0)
			return (1);
		i++;
	}
	check_philos(table);
	usleep(1000);
	i = 0;
	while (i < table->nbr_thinkers)
	{
		pthread_join(table->bigbrains[i].thread, NULL);
		i++;
	}
	return (0);
}

bool	check_philos(t_table *table)
{
	int			i;
	int			full_philos;
	t_bigbrain	*ph;

	while (1)
	{
		i = -1;
		full_philos = 0;
		while (++i < table->nbr_thinkers)
		{
			ph = &table->bigbrains[i];
			if (table->must_eat_count > 0 && check_philo_full(ph))
				full_philos++;
			if (full_philos == table->nbr_thinkers && table->must_eat_count > 0)
				return (end_simulation(table), true);
			if (!table->someone_died && has_philo_died(table, i))
			{
				log_philo_status(table, ph->id, "died");
				return (end_simulation(table), true);
			}
		}
		usleep(500);
	}
	return (true);
}

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

bool	check_philo_full(t_bigbrain *philo)
{
	bool	is_full;

	pthread_mutex_lock(&philo->mtx_meals_eaten);
	is_full = (philo->meals_eaten >= philo->table->must_eat_count);
	pthread_mutex_unlock(&philo->mtx_meals_eaten);
	return (is_full);
}
