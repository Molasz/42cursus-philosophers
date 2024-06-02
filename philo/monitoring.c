/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 14:34:06 by molasz-a          #+#    #+#             */
/*   Updated: 2024/06/02 17:53:18 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	read_philo(t_data *data, int i, size_t *last_eat, size_t *eats)
{
	pthread_mutex_lock(&data->philos[i].last_eats_mutex);
	*last_eat = data->philos[i].last_eat;
	pthread_mutex_unlock(&data->philos[i].last_eats_mutex);
	if (data->args->min_eats > 0)
	{
		pthread_mutex_lock(&data->philos[i].eats_mutex);
		*eats = data->philos[i].eats;
		pthread_mutex_unlock(&data->philos[i].eats_mutex);
	}
}

static void	thread_exit(t_data *data, int i)
{
	pthread_mutex_lock(&data->mutex->print);
	if (i >= 0)
		print_died(&data->philos[i]);
	else
		printf("All philos eat at least %ld times\n", data->args->min_eats);
	exit(0);
}

int	monitoring(t_data *data)
{
	size_t	last_eat;
	size_t	time;
	size_t	eats;
	int		all_eats;
	int		i;

	eats = 0;
	while (1)
	{
		i = -1;
		all_eats = 0;
		while (++i < data->args->philos)
		{
			read_philo(data, i, &last_eat, &eats);
			time = get_time();
			if (last_eat && time - last_eat > data->args->time_die)
				thread_exit(data, i);
			if (data->args->min_eats > 0 && eats >= data->args->min_eats)
				all_eats++;
		}
		if (all_eats == data->args->philos)
			thread_exit(data, -1);
	}
	return (0);
}
