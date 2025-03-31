/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:21:33 by pmachado          #+#    #+#             */
/*   Updated: 2025/04/01 00:39:39 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_end(int code, t_table *table)
{
	if (code == 1)
	{
		printf("%s\n", ERROR_ARGS);
		printf("%s\n", INSTRUCTION);
	}
	else if (code == 2)
	{
		printf("%s\n", ERROR_INPUT);
		printf("%s\n", INSTRUCTION2);
	}
	else if (code == 3)
		printf("%s\n", ERROR_MALLOC);
	if (code != 1 && code != 2)
		free_all(table);
	exit(1);
}

void	free_all(t_table *table)
{
	if (!table)
		return ;

	if (table->forks)
		free_forks(table);
	if (table->bigbrains)
		free_bigbrains(table);

	pthread_mutex_destroy(&table->mtx_prints);
	pthread_mutex_destroy(&table->mtx_simulation);
	free(table);
}

void	free_forks(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nbr_thinkers)
		pthread_mutex_destroy(&table->forks[i]);
	free(table->forks);
}

void	free_bigbrains(t_table *table)
{
	int	i = -1;

	while (++i < table->nbr_thinkers)
	{
		pthread_mutex_destroy(&table->bigbrains[i].mtx_last_meal_time);
		pthread_mutex_destroy(&table->bigbrains[i].mtx_meals_eaten);
		pthread_mutex_destroy(&table->bigbrains[i].mtx_fork_state); // 🔥 Important!
	}
	free(table->bigbrains);
}
