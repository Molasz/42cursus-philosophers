/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 14:34:06 by molasz-a          #+#    #+#             */
/*   Updated: 2024/06/04 22:32:26 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	read_philo(t_data *data, int i, size_t *last_eat, int *eats)
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

static void	destroy_mutex(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->args->print);
	i = 0;
	while (i < data->args->philos)
	{
		pthread_mutex_destroy(&data->philos[i].eats_mutex);
		pthread_mutex_destroy(&data->philos[i].last_eats_mutex);
		i++;
	}
}

static void	stop_threads(t_data *data, int i)
{
	int	j;

	pthread_mutex_lock(&data->args->print);
	if (i >= 0)
		print_died(&data->philos[i]);
	else
	{

	}
	j = -1;
	while (++j < data->args->philos)
		pthread_detach(data->philos[j].thread);
	destroy_mutex(data);
	free(data->philos);
}

int	monitoring(t_data *data)
{
	size_t	last_eat;
	size_t	time;
	int		eats;
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
				return (stop_threads(data, i), 0);
			if (data->args->min_eats > 0 && eats >= data->args->min_eats)
				all_eats++;
		}
		if (all_eats == data->args->philos)
			return (stop_threads(data, -1), 1);
	}
}
