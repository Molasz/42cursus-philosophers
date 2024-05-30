/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:07:30 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/30 18:29:27 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_args
{
	int				philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				min_eats;
	int				start;
}	t_args;

typedef struct s_mutex
{
	pthread_mutex_t	print;
	pthread_mutex_t	death;
}	t_mutex;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eats;
	pthread_mutex_t	philo_mutex;
	int				last_eat;
	t_args			*args;
	t_mutex			*mutex;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
}	t_philo;

typedef struct s_data
{
	t_philo			*philos;
	t_args			*args;
	t_mutex			*mutex;
}	t_data;

// Parser
int		parse(t_args *args, int argc, char **argv);

// Routines
void	*philo_routine(void *philo);

// Utils
void	ft_sleep(int mili);
int		get_time();

// Print
void	print(char *str, int fd);
void	putnbr_fd(int nb, int fd);
void	print_time_philo(int time, int philo);
void	print_fork(t_philo *philo);
void	print_eat(t_philo *philo);
void	print_sleep(t_philo *philo);
void	print_think(t_philo *philo);
void	print_died(t_philo *philo);

#endif
