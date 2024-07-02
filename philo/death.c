/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:05:47 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/02 19:30:59 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_dead(t_philo *phil)
{
	int	alive;

	pthread_mutex_lock(&phil->params->mutex_death);
	alive = phil->params->death;
	pthread_mutex_unlock(&phil->params->mutex_death);
	return (alive);
}

int	stop_threads(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->mutex_death);
	philo->params->death = 1;
	pthread_mutex_unlock(&philo->params->mutex_death);
	return (1);
}

static int	check_philo_death(t_philo *philo, long time)
{
	int	death;
	int	last_meal;

	death = 0;
	pthread_mutex_lock(&philo->mutex);
	last_meal = time - philo->last_meal;
	pthread_mutex_unlock(&philo->mutex);
	if (last_meal > philo->params->time_die)
	{
		pthread_mutex_lock(&philo->params->print);
		stop_threads(philo);
		if (!(philo->params->max_meals > 0
				&& philo->meal_count >= philo->params->max_meals))
			printf("%ld %d died\n", time, philo->id + 1);
		pthread_mutex_unlock(&philo->params->print);
		death = 1;
	}
	return (death);
}

void	*check_philos_death(void *arg)
{
	t_params	*params;
	t_philo		*philos;
	long		time;
	int			i;

	philos = arg;
	params = philos->params;
	while (1)
	{
		i = 0;
		time = get_timestamp() - params->start_time;
		while (i < params->num)
		{
			if (check_philo_death(philos + i, time))
				return (NULL);
			i++;
		}
		ft_usleep(1);
	}
	return (NULL);
}
