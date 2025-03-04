/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:50:30 by pmachado          #+#    #+#             */
/*   Updated: 2025/03/04 13:55:11 by pmachado         ###   ########.fr       */
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
	join_threads(table);
	printf("✅ All philosopher threads joined.\n");
	return (0);
}

// void	print_table_info(t_table *table)
// {
// 	printf("\n🎭 Debugging Table Initialization 🎭\n");
// 	printf("Philosophers: %d\n", table->nbr_thinkers);
// 	printf("Time to die: %d ms\n", table->time_to_die);
// 	printf("Time to eat: %d ms\n", table->time_to_eat);
// 	printf("Time to sleep: %d ms\n", table->time_to_sleep);
// 	printf("Must eat count: %d\n", table->must_eat_count);
// 	printf("Start time: %" PRIu64 " ms\n", table->start_time);
// 	printf("Someone died: %d\n", table->someone_died);
// 	printf("\n✅ Table initialization verified!\n");
// }