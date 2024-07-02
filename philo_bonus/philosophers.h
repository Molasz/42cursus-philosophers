/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:24:34 by ocartier          #+#    #+#             */
/*   Updated: 2024/07/02 18:28:47 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>

typedef struct s_params
{
	pthread_t	death_thread;
	int			num;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			max_meals;
	long		start_time;
	sem_t		*print;
	sem_t		*forks;
	sem_t		*finish;
}	t_params;

typedef struct s_philo
{
	pid_t		pid;
	int			id;
	long		last_meal;
	sem_t		*semaphore;
	int			meal_count;
	t_params	*params;
}	t_philo;

typedef struct s_data
{
	t_params	*params;
	t_philo		*philos;
}	t_data;

// death.c
void	*check_death(void *arg);
void	*wait_death(void *arg);
int		stop_process(t_data *data);
// forks.c
void	take_fork(t_philo *philo);
void	release_forks_and_sleep(t_philo *philo);
// init.c
int		create_philos(t_data *data);
int		init_params(t_params *params, int argc, char **argv);
// main.c
int		philo_life(t_philo *philo);
// process.c
int		create_process(t_data *data);
int		wait_process(t_data *data);
// utils.c
int		ft_strlen(char *s);
void	ft_usleep(long int time_in_ms);
void	write_state(char *str, t_philo *philo);
long	get_timestamp(void);
// libft.c
char	*ft_itoa(int n);
int		ft_atoi(char *str);
char	*ft_strjoin(char *s1, char *s2);
#endif
