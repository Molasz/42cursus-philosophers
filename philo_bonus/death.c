/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:06:13 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/02 18:58:25 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	stop_process(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->params->num)
		kill(data->philos[i].pid, SIGTERM);
	return (1);
}

void	*check_death(void *arg)
{
	t_philo		*philo;
	int			time;

	philo = arg;
	while (1)
	{
		time = get_timestamp() - philo->params->start_time;
		if (time - philo->last_meal > philo->params->time_die)
		{
			sem_wait(philo->params->print);
			printf("%d %d died\n", time, philo->id + 1);
			sem_post(philo->params->finish);
		}
		ft_usleep(1);
	}
	return (NULL);
}

void	*wait_death(void *arg)
{
	t_data	*data;

	data = arg;
	sem_wait(data->params->finish);
	stop_process(data);
	return (NULL);
}
