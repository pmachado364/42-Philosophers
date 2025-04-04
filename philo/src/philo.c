/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:50:30 by pmachado          #+#    #+#             */
/*   Updated: 2025/04/04 12:36:07 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	*table;

	if (!ft_validate(ac, av))
		exit(1);
	table = ft_start_dinner(ac, av);
	if (start_threads(table))
		ft_end(3, table);
	free_all(table);
	return (0);
}
