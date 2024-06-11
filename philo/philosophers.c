/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:50:58 by molasz-a          #+#    #+#             */
/*   Updated: 2024/06/11 19:17:21 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof (t_philo) * data->args->philos);
	if (!data->philos)
		return (print("MALLOC error\n", 2), 1);
	i = -1;
	while (++i < data->args->philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].args = data->args;
		data->philos[i].eats = 0;
		data->philos[i].last_eat = 0;
		pthread_mutex_init(&data->philos[i].mutex, NULL);
		pthread_mutex_init(&data->philos[i].l_fork, NULL);
		if (i)
			data->philos[i].r_fork = &data->philos[i - 1].l_fork;
	}
	if (data->args->philos > 1)
		data->philos[0].r_fork = &data->philos[i - 1].l_fork;
	else
		data->philos[0].r_fork = NULL;
	pthread_mutex_init(&data->args->print, NULL);
	pthread_mutex_init(&data->args->death_mutex, NULL);
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

	data.args = &args;
	args.death = 0;
	if (parse(&args, argc, argv))
		return (1);
	if (init_philos(&data))
		return (1);
	args.start = get_time();
	if (init_threads(&data))
		return (1);
	ft_sleep(args.time_die - 10);
	monitoring(&data);
	return (0);
}
