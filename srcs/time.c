/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouchon <lbouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:18:29 by lbouchon          #+#    #+#             */
/*   Updated: 2023/02/22 12:23:07 by lbouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

long	get_time(void)
{
	struct timeval	tp;
	long			milliseconds;
	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	printf("Voici milliseconds : %ld\n", milliseconds);
	return (milliseconds);
}

int main(void)
{
	long	start_time;
	start_time = get_time();
	
	while (1)
	{
		printf("%ld\n", get_time() - start_time);
		usleep(1 * 100);
	}
}