/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:50:58 by molasz-a          #+#    #+#             */
/*   Updated: 2024/06/03 12:52:28 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof (t_philo) * data->args->philos);
	if (!data->philos)
		return (print("MALLOC error\n", 2), 1);
	i = 0;
	while (i < data->args->philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].args = data->args;
		data->philos[i].mutex = data->mutex;
		data->philos[i].eats = 0;
		data->philos[i].last_eat = 0;
		pthread_mutex_init(&data->philos[i].eats_mutex, NULL);
		pthread_mutex_init(&data->philos[i].last_eats_mutex, NULL);
		pthread_mutex_init(&data->philos[i].l_fork, NULL);
		if (i)
			data->philos[i].r_fork = &data->philos[i - 1].l_fork;
		i++;
	}
	data->philos[0].r_fork = &data->philos[i - 1].l_fork;
	return (0);
}

static int	init_mutex(t_data *data)
{
	pthread_mutex_init(&data->mutex->start, NULL);
	pthread_mutex_init(&data->mutex->print, NULL);
	pthread_mutex_init(&data->mutex->death, NULL);
	pthread_mutex_lock(&data->mutex->start);
	return (0);
}

static int	init_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args->philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]))
			return (print("PTHREAD CREATE error\n", 2), 1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_args	args;
	t_mutex	mutex;

	data.args = &args;
	data.mutex = &mutex;
	if (parse(&args, argc, argv))
		return (1);
	if (init_philos(&data))
		return (1);
	if (init_mutex(&data))
		return (1);
	if (init_threads(&data))
		return (1);
	args.start = get_time();
	pthread_mutex_unlock(&mutex.start);
	return (monitoring(&data));
}
