/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouchon <lbouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:34:16 by lbouchon          #+#    #+#             */
/*   Updated: 2023/03/15 14:31:28 by lbouchon         ###   ########.fr       */
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
# include <stdatomic.h>

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*write;
	pthread_mutex_t	*death;
	int				nb_philo;
	int				die;
	int				*dead;
	int				sleep;
	int				nb_eat;
	int				id;
	int				eat;
	int				start_time;
	atomic_int		last_meal;
	atomic_int		*full_eat;
}	t_philo;

typedef struct s_args
{
	pthread_mutex_t	*death;
	pthread_mutex_t	*write;
	pthread_mutex_t	*mutex;
	int				*dead;
	int				nb_philo;
	int				die;
	int				eat;
	int				sleep;
	int				nb_eat;
	atomic_int		*f_eat;
}	t_args;

/*--MAIN.C--*/

void	free_all(t_philo *ph);

/*--FT_UTILS.C--*/

int		ft_check_atoi(char *str);
int		ft_strlen(char *str);
int		ft_error(char *str, int fd);
void	print_status(char *str, t_philo *ph);

/*--TIME.C--*/

int		get_time(void);
void	ft_usleep(int time_in_ms);

/*--INIT_AND_PARSE.C--*/

int		initialize_struct(t_args *args);
int		ft_fill_struct(int ac, char **av, t_philo *ph, t_args *args);
int		create_mutex(t_args *args);
int		init_philo(t_philo *ph, t_args *args);

/*--ROUTINE.C--*/

int		create_philo(t_philo *ph);
void	*routine(void *arg);
void	routine_of_philo(t_philo *ph);
void	check_philo(t_philo *ph);
void	death(t_philo *ph);

#endif