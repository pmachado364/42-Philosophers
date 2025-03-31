/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:43:14 by pmachado          #+#    #+#             */
/*   Updated: 2025/03/31 17:12:50 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_threads(t_table *table)
{
	int			i;
	pthread_t	monitor_thread;

	table->start_time = current_time_ms();
	i = 0;
	while (i < table->nbr_thinkers)
	{
		if (pthread_create(&table->bigbrains[i].thread, NULL,
				philo_behavior, (void *)&table->bigbrains[i]) != 0)
			return (1);
		printf("✅ Thread created for philosopher %d\n", i + 1);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, check_philos, (void *)table) != 0)
		return (1);
	pthread_detach(monitor_thread);
	return (0);
}

void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_thinkers)
	{
		pthread_join(table->bigbrains[i].thread, NULL);
		i++;
	}
}

void	*check_philos(void *arg)
{
	t_table		*table;
	uint64_t	now;
	uint64_t	last_log;
	int			i;

	last_log = 0;
	table = (t_table *)arg;
	while (1)
	{
		pthread_mutex_lock(&table->mtx_simulation);
		if (table->someone_died)
			return (pthread_mutex_unlock(&table->mtx_simulation), NULL);
		pthread_mutex_unlock(&table->mtx_simulation);
		now = current_time_ms();
		if (now - last_log >= 10)
			printf("[%lu] 🔍 Monitoring philosophers...\n", last_log = now);
		i = -1;
		while (++i < table->nbr_thinkers)
			if (has_philo_died(table, i, now))
				return (NULL);
		cycle_turns(table);
		usleep(200);
	}
	return (NULL);
}

int	has_philo_died(t_table *table, int i, uint64_t now)
{
	uint64_t		time_since_last_meal;
	uint64_t		last_meal;

	pthread_mutex_lock(&table->bigbrains[i].mtx_last_meal_time);
	last_meal = table->bigbrains[i].last_meal_time;
	pthread_mutex_unlock(&table->bigbrains[i].mtx_last_meal_time);
	if (now < last_meal)
		time_since_last_meal = 0;
	else
		time_since_last_meal = now - last_meal;
	if (time_since_last_meal > (uint64_t)table->time_to_die)
	{
		pthread_mutex_lock(&table->mtx_simulation);
		table->someone_died = true;
		pthread_mutex_unlock(&table->mtx_simulation);
		printf("[%lu] 💀 Philosopher %d has died after %lu ms without eating.\n",
			now, table->bigbrains[i].id, time_since_last_meal);
		return (1);
	}
	return (0);
}

void	cycle_turns(t_table *table)
{
	pthread_mutex_lock(&table->mtx_simulation);
	table->current_turn = (table->current_turn % table->nbr_thinkers) + 1;
	pthread_mutex_unlock(&table->mtx_simulation);
}
