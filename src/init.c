/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:25:05 by pmachado          #+#    #+#             */
/*   Updated: 2025/03/04 13:49:32 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*ft_start_dinner(int ac, char **av)
{
	t_table	*table;

	table = ft_init_table(ac, av);
	if (!table)
		ft_end(3, NULL);
	ft_init_forks(table);
	ft_init_philos(table);
	printf("✅ All setup is complete.\n");
	return (table);
}

t_table	*ft_init_table(int ac, char **av)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		ft_end(3, NULL);
	table->nbr_thinkers = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->must_eat_count = ft_atoi(av[5]);
	else
		table->must_eat_count = -1;
	table->someone_died = false;
	table->start_time = current_time_ms();
	table->current_turn = 1;
	pthread_mutex_init(&table->mtx_simulation, NULL);
	table->bigbrains = NULL;
	table->forks = NULL;
	return (table);
}

void	ft_init_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->nbr_thinkers);
	if (!table->forks)
		ft_end(3, table);
	i = 0;
	while (i < table->nbr_thinkers)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			ft_end(3, table);
		i++;
	}
	if ((pthread_mutex_init(&table->mtx_simulation, NULL))
		|| (pthread_mutex_init(&table->mtx_prints, NULL)))
		ft_end(3, table);
}

void	ft_init_philos(t_table *table)
{
	int	i;

	i = 0;
	table->bigbrains = malloc(sizeof(t_bigbrain) * table->nbr_thinkers);
	if (!table->bigbrains)
		ft_end(3, table);
	while (i < table->nbr_thinkers)
	{
		table->bigbrains[i].id = i + 1;
		table->bigbrains[i].meals_eaten = 0;
		table->bigbrains[i].last_meal_time = table->start_time;
		table->bigbrains[i].table = table;
		table->bigbrains[i].left_fork = &table->forks[i];
		table->bigbrains[i].right_fork = &table->forks[(i + 1)
			% table->nbr_thinkers];
		if ((pthread_mutex_init(&table->bigbrains[i].mtx_last_meal_time, NULL))
			|| (pthread_mutex_init(&table->bigbrains[i].mtx_meals_eaten, NULL)))
			ft_end(3, table);
		table->bigbrains[i].thread = 0;
		i++;
	}
}
