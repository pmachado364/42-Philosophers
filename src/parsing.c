/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:10:39 by pmachado          #+#    #+#             */
/*   Updated: 2025/02/12 10:48:59 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_validate(int ac, char **av)
{
	if(ac < 5 || ac > 6)
		ft_end(1, NULL);
	if(!is_digit(ac, av))
		ft_end(2, NULL);
	if(!check_values(ac, av))
		ft_end(2, NULL);
	return (true);
}

bool	is_digit(int ac, char **av)
{
	int	i;
	int	j;
	
	i = 1;
	while(i < ac)
	{
		j = 0;
		if(!av[i][0])
			return (false);
		while(av[i][j])
		{
			if(av[i][j] < '0' || av[i][j] > '9')
				return (false);
			j++;
		}
		if (j > 10)
			return (false);
		i++;
	}
	return(true);
}

bool	check_values(int ac, char **av)
{
	int	i;
	int	value;

	value = ft_atoi(av[1]);
	if (value < 1 || value > 100)
		return (false);
	i = 1;
	while(++i < 5)//nbr_philos, t_die, t_eat, t_sleep
	{
		value = ft_atoi(av[i]);
		if (value < 1)
			return(false);
	}
	if (ac == 6)//se o arg must_eat_count for dado
	{
		value = ft_atoi(av[5]);
		if (value < 0)
			return(false);
	}
	return (true);
}
