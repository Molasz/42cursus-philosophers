/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:07:30 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/29 12:23:09 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_args
{
	int	philos;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	min_eats;
}	t_args;

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	int			eats;
	int			eating;
	long		last_eat;
	t_args		*args;
}	t_philo;

typedef struct s_data
{
	t_args	*args;
	t_philo	*philos;
}	t_data;

// Parser
int		parse(t_args *args, int argc, char **argv);

// Utils
void	print(char *str, int fd);

#endif
