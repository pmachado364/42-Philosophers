/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:32:09 by pmachado          #+#    #+#             */
/*   Updated: 2025/04/05 12:47:12 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	long	result;

	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - 48);
		if (result > INT_MAX)
			return (-1);
		str++;
	}
	return ((int)result);
}

uint64_t	current_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

bool	end_simulation(t_table *table)
{
	pthread_mutex_lock(&table->mtx_simulation);
	table->someone_died = true;
	pthread_mutex_unlock(&table->mtx_simulation);
	return (true);
}

void	log_philo_status(t_table *table, int philo_id, char *status)
{
	uint64_t	timestamp;
	bool		is_death;

	pthread_mutex_lock(&table->mtx_simulation);
	is_death = (status[0] == 'd' && status[1] == 'i'
			&& status[2] == 'e' && status[3] == 'd');
	if (table->someone_died && !is_death)
	{
		pthread_mutex_unlock(&table->mtx_simulation);
		return ;
	}
	if (is_death)
		table->someone_died = true;
	pthread_mutex_unlock(&table->mtx_simulation);
	pthread_mutex_lock(&table->mtx_prints);
	timestamp = current_time_ms() - table->start_time;
	printf("%lu %d %s\n", timestamp, philo_id, status);
	pthread_mutex_unlock(&table->mtx_prints);
}

bool	wait_time(t_bigbrain *ph, uint64_t ms)
{
	uint64_t	start;
	uint64_t	elapsed;

	start = current_time_ms();
	while (true)
	{
		if (has_simulation_stopped(ph))
			return (true);
		elapsed = current_time_ms() - start;
		if (elapsed >= ms)
			break ;
		usleep(100);
	}
	return (false);
}
