/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:21:33 by pmachado          #+#    #+#             */
/*   Updated: 2025/03/04 13:40:11 by pmachado         ###   ########.fr       */
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
	int	i;

	if (!table)
		return ;
	i = -1;
	while (++i < table->nbr_thinkers)
		pthread_join(table->bigbrains[i].thread, NULL);
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
	int	i;

	i = -1;
	while (++i < table->nbr_thinkers)
	{
		pthread_mutex_destroy(&table->bigbrains[i].mtx_last_meal_time);
		pthread_mutex_destroy(&table->bigbrains[i].mtx_meals_eaten);
	}
	free(table->bigbrains);
}
