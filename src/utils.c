/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:32:09 by pmachado          #+#    #+#             */
/*   Updated: 2025/03/04 13:53:08 by pmachado         ###   ########.fr       */
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

bool	philo_check_death(t_bigbrain *ph)
{
	bool	status;

	pthread_mutex_lock(&ph->table->mtx_simulation);
	status = ph->table->someone_died;
	pthread_mutex_unlock(&ph->table->mtx_simulation);
	return (status);
}

bool	philo_take_forks(t_bigbrain *ph)
{
	pthread_mutex_lock(ph->left_fork);
	printf("🍴 Philosopher %d took the left fork\n", ph->id);
	if (philo_check_death(ph))
	{
		pthread_mutex_unlock(ph->left_fork);
		return (false);
	}
	pthread_mutex_lock(ph->right_fork);
	printf("🍴 Philosopher %d took the right fork\n", ph->id);
	if (philo_check_death(ph))
	{
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);
		return (false);
	}
	return (true);
}

void	philo_drop_forks(t_bigbrain *ph)
{
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
}
