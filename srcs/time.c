/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouchon <lbouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:18:29 by lbouchon          #+#    #+#             */
/*   Updated: 2023/03/01 16:29:24 by lbouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

long int	get_time(void)
{
	struct timeval	tp;
	long int		milliseconds;
	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_usec / 1000;
	return (milliseconds);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;
	
	start_time = get_time();
	while ((get_time() - start_time) < time_in_ms)
		usleep(10);
}