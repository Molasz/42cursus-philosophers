/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:50:58 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/29 12:28:19 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof (t_philo) * (data->args->philos + 1));
	if (!data->philos)
		return (print("MALLOC error\n", 2), 1);
	data->philos[data->args->philos].id = -1;
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

int	main(int argc, char **argv)
{
	t_data	data;
	t_args	args;

	if (parse(&args, argc, argv))
		return (1);
	data.args = &args;
	if (init_philos(&data))
		return (1);
	return (0);
}
