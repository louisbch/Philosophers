/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouchon <lbouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:35:59 by lbouchon          #+#    #+#             */
/*   Updated: 2023/03/14 15:12:43 by lbouchon         ###   ########.fr       */
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

void	routine_of_philo(t_philo *ph)
{
	int	left_fork;

	if (ph->id == 0)
		left_fork = ph->nb_philo - 1;
	else
		left_fork = ph->id - 1;
	pthread_mutex_lock(&ph->mutex[ph->id]);
	print_status("\033[1;33mtook a fork\033[0m", ph);
	pthread_mutex_lock(&ph->mutex[left_fork]);
	print_status("\033[1;33mtook a fork\033[0m", ph);
	pthread_mutex_lock(ph->lst_meal);
	ph->last_meal = get_time();
	printf("Routine : %d\n", ph->last_meal);
	pthread_mutex_unlock(ph->lst_meal);
	print_status("\033[1;32mis eating\033[0m", ph);
	ft_usleep(ph->eat);
	pthread_mutex_unlock(&ph->mutex[ph->id]);
	pthread_mutex_unlock(&ph->mutex[left_fork]);
	print_status("\033[1;34mis sleeping\033[0m", ph);
	ft_usleep(ph->sleep);
	print_status("\033[1;35mis thinking\033[0m", ph);
}

void	*routine(void *arg)
{
	t_philo			*ph;

	ph = (t_philo*)arg;
	if (ph->id % 2)
	 	ft_usleep(1);
	if (ph->nb_eat != 0)
	{
		while (ph->nb_eat != 0 && ph->dead[0] != 1)
		{
			routine_of_philo(ph);
			ph->nb_eat--;
		}
	}
	else
	{
		while (ph->dead[0] != 1)
			routine_of_philo(ph);
	}
	return (NULL);
}

void	death(t_philo *ph)
{
	pthread_mutex_lock(ph->death);
	pthread_mutex_lock(ph->write);
	printf("%dms\t Philo %d \033[1;31mdied\033[0m\n", get_time() - ph->start_time, ph->id);
	ph->dead[0] = 1;
	pthread_mutex_unlock(ph->death);
	pthread_mutex_unlock(ph->write);
}

void	check_philo(t_philo *ph)
{
	int		i;

	while (ph->dead[0] != 1)
	{
		ft_usleep(100);
		i = 0;
		while (i < ph->nb_philo)
		{
			if (get_time() - ph->last_meal >= ph->die)
			{
				death(ph);
				break ;
			}
			i++;
		}
	}
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
	check_philo(ph);
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
	int	res1;
	int	res2;
	int	res3;

	i = 0;
	args->death = malloc(sizeof(pthread_mutex_t));
	res1 = pthread_mutex_init(args->death, NULL);
	if (res1 != 0)
		return (-1);
	args->write = malloc(sizeof(pthread_mutex_t));
	res2 = pthread_mutex_init(args->write, NULL);
	if (res2 != 0)
		return (-1);
	args->lst_meal = malloc(sizeof(pthread_mutex_t));
	res3 = pthread_mutex_init(args->lst_meal, NULL);
	if (res3 != 0)
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
		ph[i].lst_meal = args->lst_meal;
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
