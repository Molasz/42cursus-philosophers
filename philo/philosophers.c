/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:50:58 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/30 00:02:35 by molasz-a         ###   ########.fr       */
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
		data->philos[i].eats = 0;
		data->philos[i].eating = 0;
		data->philos[i].last_eat = 0;
		i++;
	}
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

	if (parse(&args, argc, argv))
		return (1);
	data.args = &args;
	if (init_philos(&data))
		return (1);
	if (init_threads(&data))
		return (1);
	usleep(5000);
	return (0);
}
