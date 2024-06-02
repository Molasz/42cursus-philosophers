/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:07:30 by molasz-a          #+#    #+#             */
/*   Updated: 2024/06/02 17:58:09 by molasz-a         ###   ########.fr       */
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
	int		philos;
	size_t	time_die;
	size_t	time_eat;
	size_t	time_sleep;
	size_t	min_eats;
	size_t	start;
}	t_args;

typedef struct s_mutex
{
	pthread_mutex_t	start;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
}	t_mutex;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eats;
	size_t			last_eat;
	t_args			*args;
	t_mutex			*mutex;
	pthread_mutex_t	eats_mutex;
	pthread_mutex_t	last_eats_mutex;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
}	t_philo;

typedef struct s_data
{
	t_philo	*philos;
	t_args	*args;
	t_mutex	*mutex;
}	t_data;

int		parse(t_args *args, int argc, char **argv);
void	*philo_routine(void *philo);
int		monitoring(t_data *data);

// Utils
void	ft_sleep(size_t mili);
size_t	get_time(void);

// Print
void	putchar_fd(char c, int fd);
void	print(char *str, int fd);
void	putnbr_fd(size_t nb, int fd);
void	print_time_philo(size_t time, int philo);
void	print_fork(t_philo *philo);
void	print_eat(t_philo *philo);
void	print_sleep(t_philo *philo);
void	print_think(t_philo *philo);
void	print_died(t_philo *philo);

#endif
