/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouchon <lbouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:35:59 by lbouchon          #+#    #+#             */
/*   Updated: 2023/03/14 17:22:57 by lbouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_args	args;
	t_philo	*philo;

	if (ac < 5 || ac > 6)
	{
		ft_error("Error\nNumber of arguments is invalid !\n", 2);
		return (-1);
	}
	initialize_struct(&args);
	while (--ac >= 1)
	{
		if (ft_fill_struct(ac, av, philo, &args) == -1)
			return (-1);
	}
	create_mutex(&args);
	philo = malloc(sizeof(t_philo) * args.nb_philo);
	if (!philo)
		return (-1);
	init_philo(philo, &args);
	create_philo(philo);
	return (0);
}
