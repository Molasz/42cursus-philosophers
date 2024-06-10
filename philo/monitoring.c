/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 14:34:06 by molasz-a          #+#    #+#             */
/*   Updated: 2024/06/10 12:36:56 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	read_philo(t_data *data, int i, size_t *last_eat, int *eats)
{
	pthread_mutex_lock(&data->philos[i].mutex);
	*last_eat = data->philos[i].last_eat;
	if (data->args->min_eats > 0)
		*eats = data->philos[i].eats;
	pthread_mutex_unlock(&data->philos[i].mutex);
}

static void	destroy_mutex(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->args->print);
	pthread_mutex_destroy(&data->args->death_mutex);
	i = 0;
	while (i < data->args->philos)
	{
		pthread_mutex_lock(&data->philos[i].l_fork);
		pthread_mutex_unlock(&data->philos[i].l_fork);
		pthread_mutex_destroy(&data->philos[i].l_fork);
		i++;
	}
}

static void	wait_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args->philos)
	{
		while (1)
		{
			pthread_mutex_lock(&data->philos[i].mutex);
			if (data->philos[i].stopped)
				break ;
			pthread_mutex_unlock(&data->philos[i].mutex);
			ft_sleep(10);
		}
		pthread_mutex_unlock(&data->philos[i].mutex);
		pthread_mutex_destroy(&data->philos[i].mutex);
		i++;
	}
}

static void	stop_threads(t_data *data, int i)
{
	size_t	time;
	int		j;

	time = get_time() - data->args->start;
	pthread_mutex_lock(&data->args->death_mutex);
	data->args->death = 1;
	pthread_mutex_unlock(&data->args->death_mutex);
	j = -1;
	while (++j < data->args->philos)
		pthread_detach(data->philos[j].thread);
	wait_threads(data);
	if (i >= 0)
		printf("%ld %d died\n", time, data->philos[i].id);
	else
		printf("%ld All philosophers eat at least min meals\n", time);
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
		ft_sleep(10);
	}
}
