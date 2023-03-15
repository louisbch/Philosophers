/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouchon <lbouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:10:50 by lbouchon          #+#    #+#             */
/*   Updated: 2023/03/15 15:31:24 by lbouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

void	*routine(void *arg)
{
	t_philo			*ph;

	ph = (t_philo *)arg;
	if (ph->id % 2)
		ft_usleep((ph->nb_philo + 50) / 50);
	if (ph->nb_eat != 0)
	{
		while (ph->nb_eat != 0 && ph->dead[0] != 1)
		{
			routine_of_philo(ph);
			if (ph->nb_eat - 1 == 0)
				ph->full_eat[0] = 1;
			ph->nb_eat--;
		}
	}
	else
	{
		while (ph->nb_eat == -2 && ph->dead[0] != 1)
			routine_of_philo(ph);
	}
	return (NULL);
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
	ph->last_meal = get_time();
	print_status("\033[1;32mis eating\033[0m", ph);
	ft_usleep(ph->eat);
	pthread_mutex_unlock(&ph->mutex[ph->id]);
	pthread_mutex_unlock(&ph->mutex[left_fork]);
	print_status("\033[1;34mis sleeping\033[0m", ph);
	ft_usleep(ph->sleep);
	print_status("\033[1;35mis thinking\033[0m", ph);
}

void	check_philo(t_philo *ph)
{
	int	i;

	if (ph->nb_eat != 0)
	{
		while (ph->dead[0] != 1 && ph->full_eat[0] != 1)
		{
			ft_usleep(1 / 10);
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
}

void	death(t_philo *ph)
{
	pthread_mutex_lock(ph->death);
	pthread_mutex_lock(ph->write);
	printf("%dms\t Philo %d \033[1;31mdied\033[0m\n",
		get_time() - ph->start_time, ph->id + 1);
	ph->dead[0] = 1;
	if (ph->nb_philo == 1)
		pthread_mutex_unlock(ph->mutex);
	pthread_mutex_unlock(ph->death);
	pthread_mutex_unlock(ph->write);
}
