/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:07:30 by molasz-a          #+#    #+#             */
/*   Updated: 2024/06/30 19:01:43 by molasz-a         ###   ########.fr       */
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
}	t_args;

typedef struct s_philo
{
	int				id;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	int				stop;
	int				eats;
	size_t			last_eat;
	size_t			*start;
	pthread_t		thread;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*print;
	pthread_mutex_t	*flag;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
}	t_philo;

typedef struct s_data
{
	t_philo			*philos;
	int				philos_num;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	int				min_eats;
	size_t			start;
	pthread_mutex_t	print;
	pthread_mutex_t	flag;
}	t_data;

// Philo
int		parse(t_data *data, int argc, char **argv);
void	*philo_routine(void *philo);
int		monitoring(t_data *data);

// Print utils
void	print(char *str, int fd);
int		print_action(t_philo *philo, char *str);

// Utils
void	ft_sleep(size_t mili);
size_t	get_time(void);
size_t	ft_strlen(char *str);

#endif
