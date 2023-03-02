/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouchon <lbouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:35:59 by lbouchon          #+#    #+#             */
/*   Updated: 2023/03/02 15:43:55 by lbouchon         ###   ########.fr       */
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
}

int	ft_fill_struct(int ac, char **av, t_philo *ph, t_args *args)
{
	if (ac == 1)
	{
		args->nb_philo = ft_check_atoi(av[ac]);
		if (args->nb_philo == -1)
			return (ft_error("Bad arguments\n", 2));
			
	}
	if (ac == 2)
	{
		args->eat = ft_check_atoi(av[ac]);
		if (args->eat == -1)
			return (ft_error("Bad arguments\n", 2));
	}
	if (ac == 3)
	{
		args->sleep = ft_check_atoi(av[ac]);
		if (args->sleep == -1)
			return (ft_error("Bad arguments\n", 2));
	}
	if (ac == 4)
	{
		args->nb_eat = ft_check_atoi(av[ac]);
		if (args->nb_eat == -1)
			return (ft_error("Bad arguments\n", 2));
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo			*ph;
	int				left_fork;
	long int		actual_time;

	ph = (t_philo*)arg;
	// if (ph->id % 2 == 0)
	// 	ft_usleep(1);
	actual_time = get_time();
	if (ph->id == 1)
		left_fork = ph->nb_philo - 1;
	else
		left_fork = ph->id - 1;
	pthread_mutex_lock(&ph->mutex[left_fork]);
	printf("%ldms\t Philo %d took a fork\n", actual_time - ph->start_time, ph->id);
	//pthread_mutex_lock(&ph->mutex[ph->id - 1]);
	//printf("%ldms\t Philo %d took a fork\n", actual_time - ph->start_time, ph->id);
	//pthread_mutex_unlock(&ph->mutex[left_fork]);
	//pthread_mutex_unlock(&ph->mutex[ph->id - 1]);
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

int	create_mutex(t_philo *ph)
{
	int	i;
	int	res;

	i = 0;
	ph->mutex = malloc(sizeof(pthread_mutex_t) * ph->nb_philo);
	if (!ph->mutex)
		return (-1);
	while (i < ph->nb_philo)
	{
		res = pthread_mutex_init(ph[i].mutex + i, NULL);
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
		ph[i].id = i + 1;
		ph[i].nb_philo = args->nb_philo;
		ph[i].sleep = args->sleep;
		ph[i].nb_eat = args->nb_eat;
		ph[i].fork = args->nb_philo;
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
	create_mutex(philo);
	philo = malloc(sizeof(t_philo) * args.nb_philo);
	if (!philo)
		return (-1);
	init_philo(philo, &args);
	create_mutex(philo);
	create_philo(philo);
	return (0);
}
