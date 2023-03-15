/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouchon <lbouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:35:59 by lbouchon          #+#    #+#             */
/*   Updated: 2023/03/15 15:22:48 by lbouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_all(t_philo *ph)
{
	int	i;
	int	res;

	i = -1;
	if (ph[i].mutex)
	{
		while (++i < ph->nb_philo)
			pthread_mutex_destroy(ph[i].mutex);
	}
	if (ph->write)
		pthread_mutex_destroy(ph->write);
	if (ph->write)
		pthread_mutex_destroy(ph->death);
	if (ph->dead)
		free(ph->dead);
	if (ph->full_eat)
		free(ph->full_eat);
	if (ph)
		free(ph);
}

int	main(int ac, char **av)
{
	t_args	args;
	t_philo	*philo;

	if (ac < 5 || ac > 6)
	{
		ft_error("Error\nNumber of arguments is invalid !\n", 2);
		return (-1);
	}
	if (initialize_struct(&args) == -1)
		return (-1);
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
	free_all(philo);
	return (0);
}
