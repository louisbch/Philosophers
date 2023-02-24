/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouchon <lbouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:34:16 by lbouchon          #+#    #+#             */
/*   Updated: 2023/02/24 12:40:43 by lbouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t	philo;
	int			id;
}	t_philo;

typedef struct s_args
{
	int	nb_philo;
	int	die;
	int	eat;
	int	sleep;
	int	nb_eat;
}	t_args;

typedef struct s_ph
{
	t_philo	*philo;
	t_args	args;
}	t_ph;

/*--FT_UTILS.C--*/

int		ft_check_atoi(char *str);
int		ft_strlen(char *str);
int		ft_error(char *str, int fd);
int	id_philo(t_ph *ph);

#endif