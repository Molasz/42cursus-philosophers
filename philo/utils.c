/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:25:40 by molasz-a          #+#    #+#             */
/*   Updated: 2024/06/10 20:13:04 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep(size_t mili)
{
	size_t	start;
	size_t	time;

	start = get_time();
	while (1)
	{
		time = get_time();
		if (time - start >= mili)
			break ;
	}
}

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	lock_mutex(pthread_mutex_t *mutex, t_args *args)
{
	pthread_mutex_lock(mutex);
	pthread_mutex_lock(&args->death_mutex);
	if (args->death)
	{
		pthread_mutex_unlock(&args->death_mutex);
		return (pthread_mutex_unlock(mutex), 1);
	}
	pthread_mutex_unlock(&args->death_mutex);
	return (0);
}

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
