/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouchon <lbouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:35:59 by lbouchon          #+#    #+#             */
/*   Updated: 2023/02/24 13:26:25 by lbouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	initialize_struct(t_ph *ph)
{
	ph->args.nb_philo = 0;
	ph->args.die = 0;
	ph->args.sleep = 0;
	ph->args.nb_eat = 0;
	ph->args.nb_philo = 0;
}

void	*hello(void *arg)
{
	int	i;

	i = 0;
	usleep(10000);
	while (i < 100)
	{
		printf("\033[0;31mthread 1 : Bonjour\n");
		i++;
	}
	return (NULL);
}

int	ft_fill_struct(int ac, char **av, t_ph *ph)
{
	if (ac == 1)
	{
		ph->args.nb_philo = ft_check_atoi(av[ac]);
		if (ph->args.nb_philo == -1)
			return (ft_error("Bad arguments\n", 2));
			
	}
	if (ac == 2)
	{
		ph->args.eat = ft_check_atoi(av[ac]);
		if (ph->args.eat == -1)
			return (ft_error("Bad arguments\n", 2));
	}
	if (ac == 3)
	{
		ph->args.sleep = ft_check_atoi(av[ac]);
		if (ph->args.sleep == -1)
			return (ft_error("Bad arguments\n", 2));
	}
	if (ac == 4)
	{
		ph->args.nb_eat = ft_check_atoi(av[ac]);
		if (ph->args.nb_eat == -1)
			return (ft_error("Bad arguments\n", 2));
	}
	return (0);
}

void	*routine(void *arg)
{
	int		i;

	i = 0;
	while (i < 5)
	{
		i++;
	}
	return (NULL);
}

int	create_philo(t_ph *ph)
{
	int	i;
	int	res;
	
	i = 0;
	id_philo(ph);
	while (i < ph->args.nb_philo)
	{
		printf("Philo id :%d\n", ph->philo[i].id);
		res = pthread_create(&ph->philo[i].philo, NULL, routine, &ph->philo + i);
		if (res != 0)
			ft_error("Problem in creation of thread\n", 2);
		i++;
	}
	i = 0;
	while (i < ph->args.nb_philo)
	{
		res = pthread_join(ph->philo[i].philo, NULL);
		if (res != 0)
			ft_error("Problem in join thread\n", 2);
		i++;
	}
	return (0);
}

int	id_philo(t_ph *ph)
{
	int	i;

	i = 0;
	while (i < ph->args.nb_philo)
	{
		ph->philo[i].id = i + 1;
		i++;
	}
	return (0);
}

int main(int ac, char **av)
{
	t_ph	ph;

	if (ac < 5 || ac > 6)
		printf("Error\nNumber of arguments is invalid\n");
	initialize_struct(&ph);
	while (--ac >= 1)
	{
		if (ft_fill_struct(ac, av, &ph) == -1)
			return (-1);
	}
	ph.philo = malloc(sizeof(t_philo) * ph.args.nb_philo);
	if (!ph.philo)
		ft_error("Malloc failed\n", 2);
		if (create_philo(&ph) != 0)
			return (-1);
		id_philo(&ph);
	return (0);
}
