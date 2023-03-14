/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouchon <lbouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:34:16 by lbouchon          #+#    #+#             */
/*   Updated: 2023/03/14 14:56:06 by lbouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
#include <stdatomic.h>

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*write;
	pthread_mutex_t	*death;
	pthread_mutex_t	*lst_meal;
	int				nb_philo;
	int				die;
	int				*dead;
	int				sleep;
	int				nb_eat;
	int				id;
	int				eat;
	int				start_time;
	atomic_int		last_meal;
}	t_philo;

typedef struct s_args
{
	pthread_mutex_t	*death;
	pthread_mutex_t	*write;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*lst_meal;
	int				*dead;
	int				nb_philo;
	int				die;
	int				eat;
	int				sleep;
	int				nb_eat;
}	t_args;

/*--MAIN.C--*/

int	create_mutex(t_args *args);

/*--FT_UTILS.C--*/

int		ft_check_atoi(char *str);
int		ft_strlen(char *str);
int		ft_error(char *str, int fd);
void	print_status(char *str, t_philo *ph);

/*--TIME.C--*/

int				get_time(void);
void			ft_usleep(int time_in_ms);

#endif