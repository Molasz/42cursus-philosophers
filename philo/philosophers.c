/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:07:42 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/01 21:46:57 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	free_all(t_data *data, int exit_code)
{
	free(data->philos);
	free(data->forks);
	return (exit_code);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_params	params;
	int			exit_code;

	data.params = &params;
	if (!init_params(&params, argc, argv))
		return (1);
	printf("%d %d %d\n", params.time_die, params.time_eat, params.time_sleep);
	if (!create_philos(&data))
		return (1);
	if (!create_threads(&data))
		exit_code = stop_threads(data.philos);
	if (!wait_threads(&data))
		return (free_all(&data, 1));
	return (free_all(&data, exit_code));
}
