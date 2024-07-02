/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:07:12 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/02 18:59:14 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_process(t_data *data)
{
	int	i;

	data->params->start_time = get_timestamp();
	i = 0;
	while (i < data->params->num)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == 0)
			return (philo_life(data->philos + i));
		i++;
	}
	if (pthread_create(&data->params->death_thread, NULL,
			wait_death, data))
		return (0);
	pthread_join(data->params->death_thread, NULL);
	return (1);
}

int	wait_process(t_data *data)
{
	int	i;
	int	return_code;

	i = 0;
	return_code = 1;
	while (i < data->params->num)
	{
		if (waitpid(data->philos[i].pid, NULL, 0) == -1)
			return_code = 0;
		i++;
	}
	return (return_code);
}

int	philo_life(t_philo *philo)
{
	pthread_t	death_thread;

	pthread_create(&death_thread, NULL, check_death, philo);
	if (philo->id % 2 != 0)
		ft_usleep(philo->params->time_eat);
	while (1)
	{
		if (philo->meal_count >= philo->params->max_meals
			&& philo->params->max_meals > 0)
			break ;
		take_fork(philo);
		take_fork(philo);
		write_state("is eating", philo);
		ft_usleep(philo->params->time_eat);
		philo->meal_count++;
		sem_wait(philo->semaphore);
		philo->last_meal = get_timestamp() - philo->params->start_time;
		sem_post(philo->semaphore);
		release_forks_and_sleep(philo);
		ft_usleep((philo->params->time_die - philo->params->time_eat
				- philo->params->time_sleep) / 2);
	}
	sem_post(philo->params->finish);
	return (1);
}
