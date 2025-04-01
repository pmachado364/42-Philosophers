/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:50:30 by pmachado          #+#    #+#             */
/*   Updated: 2025/04/01 15:20:46 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	*table;

	if (!ft_validate(ac, av))
		exit(1);
	printf("All good with parsing. Initiating structs\n");
	table = ft_start_dinner(ac, av);
	printf("✅ Starting philosopher threads...\n");
	if (start_threads(table))
		ft_end(3, table);
	free_all(table);
	return (0);
}
