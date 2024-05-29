/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:07:30 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/29 11:57:25 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_data
{
	int	philos;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	min_eats;
}	t_data;

typedef struct s_philo
{
	int			id;
	int			eats;
}	t_philo;

// Parser
int		parse(t_data *data, int argc, char **argv);

// Utils
void	print(char *str, int fd);

#endif
