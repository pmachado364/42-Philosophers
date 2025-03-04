/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:52:26 by pmachado          #+#    #+#             */
/*   Updated: 2025/03/04 13:53:19 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_for(t_bigbrain *ph, uint64_t time_to_wait)
{
	uint64_t	start_time;

	start_time = current_time_ms();
	while ((current_time_ms() - start_time) < time_to_wait)
	{
		if (philo_check_death(ph))
			break ;
		usleep(100);
	}
}
