/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouchon <lbouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:12:08 by lbouchon          #+#    #+#             */
/*   Updated: 2023/03/14 15:08:36 by lbouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_check_atoi(char *str)
{
	size_t		i;
	long int	res;
	int			sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{	
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		if (res * sign > INT_MAX)
			return (-1);
		i++;
	}
	if (str[i] || (sign == -1 && i == 1) || i == 0)
			return (-1);
	return (res * sign);
}

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

int	ft_error(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	write(fd, str, ft_strlen(str));
	return (-1);
}

void	print_status(char *str, t_philo *ph)
{
	int	time;

	time = get_time() - ph->start_time;
	pthread_mutex_lock(ph->write);
	if (ph->dead[0] != 1)
		printf("%dms\t Philo %d %s\n", time, ph->id, str);
	pthread_mutex_unlock(ph->write);
}