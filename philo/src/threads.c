/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:43:14 by pmachado          #+#    #+#             */
/*   Updated: 2025/04/05 13:37:28 by pmachado         ###   ########.fr       */
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
	int			full_philos;
	uint64_t	now;
	int			starving_id;
	int			i;

	while (1)
	{
		full_philos = 0;
		i = -1;
		now = current_time_ms();
		while (++i < table->nbr_thinkers)
			if (table->must_eat_count > 0
				&& check_philo_full(&table->bigbrains[i]))
				full_philos++;
		if (table->must_eat_count > 0 && full_philos == table->nbr_thinkers)
			return (end_simulation(table), true);
		if (check_any_philo_died(table))
			return (true);
		starving_id = update_starving_id(table, now);
		pthread_mutex_lock(&table->mtx_priority);
		table->most_starving_id = starving_id;
		pthread_mutex_unlock(&table->mtx_priority);
		usleep(500);
	}
	return (true);
}

int	update_starving_id(t_table *table, uint64_t now)
{
	int			i;
	uint64_t	last;
	uint64_t	time_since;
	uint64_t	max;
	int			id;

	i = -1;
	max = 0;
	id = -1;
	while (++i < table->nbr_thinkers)
	{
		pthread_mutex_lock(&table->bigbrains[i].mtx_last_meal_time);
		last = table->bigbrains[i].last_meal_time;
		pthread_mutex_unlock(&table->bigbrains[i].mtx_last_meal_time);
		time_since = now - last;
		if (time_since > max)
		{
			max = time_since;
			id = table->bigbrains[i].id;
		}
	}
	return (id);
}
