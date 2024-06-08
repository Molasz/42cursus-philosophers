/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 23:52:56 by molasz-a          #+#    #+#             */
/*   Updated: 2024/06/08 18:57:40 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0 && lock_mutex(&philo->l_fork, philo->args))
		return (1);
	else if (philo->id % 2 && lock_mutex(philo->r_fork, philo->args))
		return (1);
	if (print_fork(philo))
	{
		if (philo->id % 2 == 0)
			return (pthread_mutex_unlock(&philo->l_fork), 1);
		else
			return (pthread_mutex_unlock(philo->r_fork), 1);
	}
	if (philo->id % 2 == 0 && lock_mutex(philo->r_fork, philo->args))
		return (pthread_mutex_unlock(&philo->l_fork), 1);
	else if (philo->id % 2 && lock_mutex(&philo->l_fork, philo->args))
		return (pthread_mutex_unlock(philo->r_fork), 1);
	if (print_fork(philo) || print_eat(philo))
		return (pthread_mutex_unlock(&philo->l_fork),
			pthread_mutex_unlock(philo->r_fork), 1);
	return (0);
}

static int	routine_eat(t_philo *philo)
{
	size_t	time;

	if (take_forks(philo))
		return (1);
	time = get_time();
	if (lock_mutex(&philo->last_eats_mutex, philo->args))
		return (1);
	philo->last_eat = time;
	pthread_mutex_unlock(&philo->last_eats_mutex);
	if (philo->args->min_eats > 0)
	{
		if (lock_mutex(&philo->eats_mutex, philo->args))
			return (1);
		philo->eats++;
		pthread_mutex_unlock(&philo->eats_mutex);
	}
	ft_sleep(philo->args->time_eat);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (lock_mutex(&philo->args->print, philo->args))
		return (NULL);
	pthread_mutex_unlock(&philo->args->print);
	if (lock_mutex(&philo->last_eats_mutex, philo->args))
		return (NULL);
	philo->last_eat = philo->args->start;
	pthread_mutex_unlock(&philo->last_eats_mutex);
	if (philo->id % 2 == 0)
		ft_sleep(philo->args->time_eat - 10);
	while (1)
	{
		if (routine_eat(philo))
			return (NULL);
		if (print_sleep(philo))
			return (NULL);
		ft_sleep(philo->args->time_sleep);
		if (print_think(philo))
			return (NULL);
	}
	return (NULL);
}
