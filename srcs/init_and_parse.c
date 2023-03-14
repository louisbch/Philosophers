/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouchon <lbouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:06:16 by lbouchon          #+#    #+#             */
/*   Updated: 2023/03/14 17:07:49 by lbouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	initialize_struct(t_args *args)
{
	args->dead = malloc(sizeof(int));
	if (!args->dead)
		return ;
	args->nb_philo = 0;
	args->die = 0;
	args->sleep = 0;
	args->nb_eat = 0;
	args->nb_philo = 0;
	args->eat = 0;
}

int	ft_fill_struct(int ac, char **av, t_philo *ph, t_args *args)
{
	args->nb_philo = ft_check_atoi(av[1]);
	if (args->nb_philo == -1)
		return (ft_error("Bad arguments\n", 2));
	args->die = ft_check_atoi(av[2]);
	if (args->die == -1)
		return (ft_error("Bad arguments\n", 2));
	args->eat = ft_check_atoi(av[3]);
	if (args->eat == -1)
		return (ft_error("Bad arguments\n", 2));
	args->sleep = ft_check_atoi(av[4]);
	if (args->sleep == -1)
		return (ft_error("Bad arguments\n", 2));
	if (av[5])
	{
		args->nb_eat = ft_check_atoi(av[5]);
		if (args->nb_eat == -1)
			return (ft_error("Bad arguments\n", 2));
	}
	return (0);
}

int	create_mutex(t_args *args)
{
	int	i;
	int	res;
	int	res1;
	int	res2;

	i = 0;
	args->death = malloc(sizeof(pthread_mutex_t));
	res1 = pthread_mutex_init(args->death, NULL);
	if (res1 != 0)
		return (-1);
	args->write = malloc(sizeof(pthread_mutex_t));
	res2 = pthread_mutex_init(args->write, NULL);
	if (res2 != 0)
		return (-1);
	args->mutex = malloc(sizeof(pthread_mutex_t) * args->nb_philo);
	if (!args->mutex)
		return (-1);
	while (i < args->nb_philo)
	{
		res = pthread_mutex_init(args->mutex + i, NULL);
		if (res != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	init_philo(t_philo *ph, t_args *args)
{
	int	i;
	int	start_time;

	i = 0;
	start_time = get_time();
	while (i < args->nb_philo)
	{
		ph[i].start_time = start_time;
		ph[i].id = i;
		ph[i].last_meal = start_time;
		ph[i].die = args->die;
		ph[i].death = args->death;
		ph[i].write = args->write;
		ph[i].nb_philo = args->nb_philo;
		ph[i].eat = args->eat;
		ph[i].sleep = args->sleep;
		ph[i].nb_eat = args->nb_eat;
		ph[i].dead = args->dead;
		ph[i].mutex = args->mutex;
		i++;
	}
	return (0);
}
