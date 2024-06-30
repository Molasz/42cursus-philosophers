/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:50:58 by molasz-a          #+#    #+#             */
/*   Updated: 2024/06/30 19:02:41 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_philo_data(t_data *data, int i)
{
	data->philos[i].id = i + 1;
	data->philos[i].time_die = data->time_die;
	data->philos[i].time_eat = data->time_eat;
	data->philos[i].time_sleep = data->time_sleep;
	data->philos[i].start = &data->start;
	data->philos[i].stop = 0;
	data->philos[i].eats = 0;
	data->philos[i].last_eat = 0;
	data->philos[i].print = &data->print;
	data->philos[i].flag = &data->flag;
}

static int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof (t_philo) * data->philos_num);
	if (!data->philos)
		return (print("MALLOC error\n", 2), 1);
	i = -1;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->flag, NULL);
	pthread_mutex_lock(&data->flag);
	while (++i < data->philos_num)
	{
		init_philo_data(data, i);
		pthread_mutex_init(&data->philos[i].mutex, NULL);
		pthread_mutex_init(&data->philos[i].l_fork, NULL);
		if (i)
			data->philos[i].r_fork = &data->philos[i - 1].l_fork;
	}
	if (data->philos_num > 1)
		data->philos[0].r_fork = &data->philos[i - 1].l_fork;
	else
		data->philos[0].r_fork = NULL;
	return (0);
}

static int	init_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_num)
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

	if (parse(&data, argc, argv))
		return (1);
	if (init_philos(&data))
		return (1);
	if (init_threads(&data))
		return (1);
	data.start = get_time();
	pthread_mutex_unlock(&data.flag);
	ft_sleep(data.time_eat);
	monitoring(&data);
	return (0);
}
