/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:07:54 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/02 19:02:50 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_params
{
	int				num;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				max_meals;
	long			start_time;
	pthread_mutex_t	print;
	int				death;
	pthread_mutex_t	mutex_death;
	pthread_t		monitoring_thread;
}	t_params;

typedef struct s_fork
{
	int				used;
	pthread_mutex_t	lock;
}	t_fork;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	long			last_meal;
	int				meal_count;
	pthread_mutex_t	mutex;
	t_fork			*r_fork;
	int				r_taken;
	t_fork			*l_fork;
	int				l_taken;
	t_params		*params;
}	t_philo;

typedef struct data
{
	t_params	*params;
	t_philo		*philos;
	t_fork		*forks;
}	t_data;

// init.c
int		init_params(t_params *params, int argc, char **argv);
int		create_philos(t_data *data);

// threads.c
int		create_threads(t_data *data);
int		wait_threads(t_data *data);

// death.c
int		is_dead(t_philo *philo);
void	*check_philos_death(void *arg);
int		stop_threads(t_philo *philo);

// forks.c
void	take_fork(t_philo *philo, int leftFork);
void	release_fork(t_philo *philo, int leftFork);
void	release_forks_and_sleep(t_philo *philo);

// utils.c
void	ft_usleep(long int time_in_ms);
void	write_state(char *str, t_philo *philo);
long	get_timestamp(void);
int		ft_atoi(char *str);

#endif
