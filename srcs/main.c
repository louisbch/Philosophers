/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouchon <lbouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:35:59 by lbouchon          #+#    #+#             */
/*   Updated: 2023/03/03 15:10:02 by lbouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	initialize_struct(t_args *args)
{
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
		args->nb_eat = ft_check_atoi(av[5]);
	return (0);
}

void	routine_of_philo(t_philo *ph)
{
	int	left_fork;

	if (ph->id == 0)
		left_fork = ph->nb_philo - 1;
	else
		left_fork = ph->id - 1;
	pthread_mutex_lock(&ph->mutex[ph->id]);
	print("took a fork", ph);
	pthread_mutex_lock(&ph->mutex[left_fork]);
	print("took a fork", ph);
	print("is eating", ph);
	ft_usleep(ph->eat);
	pthread_mutex_unlock(&ph->mutex[ph->id]);
	pthread_mutex_unlock(&ph->mutex[left_fork]);
	print("is sleeping", ph);
	ft_usleep(ph->sleep);
	print("is thinking", ph);
}

void	*routine(void *arg)
{
	t_philo			*ph;
	int				left_fork;

	ph = (t_philo*)arg;
	if (ph->id % 2 == 0)
	 	ft_usleep(1);
	printf("%d\n", ph->nb_eat);
	if (ph->nb_eat > 0)
	{
		while (ph->nb_eat != 0)
		{
			routine_of_philo(ph);
			ph->nb_eat--;
		}
	}
	else
		routine_of_philo(ph);
	return (NULL);
}

int	create_philo(t_philo *ph)
{
	int	i;
	int	res;
	
	i = 0;
	while (i < ph->nb_philo)
	{
		res = pthread_create(&ph[i].thread, NULL, routine, ph + i);
		if (res != 0)
			ft_error("Problem in creation of thread\n", 2);
		i++;
	}
	i = 0;
	while (i < ph->nb_philo)
	{
		res = pthread_join(ph[i].thread, NULL);
		if (res != 0)
			ft_error("Problem in join thread\n", 2);
		i++;
	}
	return (0);
}

int	create_mutex(t_args *args)
{
	int	i;
	int	res;

	i = 0;
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
		ph[i].nb_philo = args->nb_philo;
		ph[i].eat = args->eat;
		ph[i].sleep = args->sleep;
		ph[i].nb_eat = args->nb_eat;
		ph[i].fork = args->nb_philo;
		ph[i].mutex = args->mutex;
		i++;
	}
	return (0);
}

int main(int ac, char **av)
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
