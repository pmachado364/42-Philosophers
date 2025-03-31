/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:52:26 by pmachado          #+#    #+#             */
/*   Updated: 2025/03/31 23:34:19 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool wait_time(t_bigbrain *ph, uint64_t ms)
{
	uint64_t start;

	start = current_time_ms();
	while ((current_time_ms() - start) < ms)
	{
		if (has_simulation_stopped(ph))
			return (true);
		usleep(500);
	}
	return (false);
}
