/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:06:52 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/02 18:30:48 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	free_all(t_data *data, int exit_code)
{
	free(data->philos);
	sem_close(data->params->forks);
	sem_close(data->params->print);
	sem_close(data->params->finish);
	return (exit_code);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_params	params;
	int			return_code;

	data.params = &params;
	return_code = 0;
	if (!init_params(&params, argc, argv))
		return (1);
	if (!create_philos(&data))
		return (1);
	if (!create_process(&data))
		return_code = stop_process(&data);
	if (!wait_process(&data))
		return (free_all(&data, 1));
	return (free_all(&data, return_code));
}
