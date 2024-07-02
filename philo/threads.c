/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:08:04 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/02 19:03:35 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*philo_routine(void *arg)
{
	t_philo		*philo;

	philo = arg;
	if (philo->id % 2 != 0)
		ft_usleep(philo->params->time_eat);
	while (!is_dead(philo))
	{
		if (philo->meal_count >= philo->params->max_meals
			&& philo->params->max_meals > 0)
			break ;
		take_fork(philo, 1);
		if (philo->l_taken)
			take_fork(philo, 0);
		if (philo->r_taken && philo->l_taken)
		{
			write_state("is eating", philo);
			ft_usleep(philo->params->time_eat);
			philo->meal_count++;
			pthread_mutex_lock(&philo->mutex);
			philo->last_meal = get_timestamp() - philo->params->start_time;
			pthread_mutex_unlock(&philo->mutex);
			release_forks_and_sleep(philo);
		}
	}
	return (NULL);
}

int	create_threads(t_data *data)
{
	int	i;

	data->params->start_time = get_timestamp();
	i = 0;
	while (i < data->params->num)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				data->philos + i))
			return (0);
		i++;
	}
	if (pthread_create(&(data->params->monitoring_thread), NULL,
			check_philos_death, data->philos))
		return (0);
	return (1);
}

int	wait_threads(t_data *data)
{
	int	i;
	int	return_code;

	i = 0;
	return_code = 1;
	while (i < data->params->num)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			return_code = 0;
		i++;
	}
	pthread_join(data->params->monitoring_thread, NULL);
	return (return_code);
}
