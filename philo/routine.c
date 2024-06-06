/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 23:52:56 by molasz-a          #+#    #+#             */
/*   Updated: 2024/06/06 13:42:53 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->l_fork);
	else
		pthread_mutex_lock(philo->r_fork);
	print_fork(philo);
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->r_fork);
	else
		pthread_mutex_lock(&philo->l_fork);
	print_fork(philo);
	print_eat(philo);
}

static void	routine_eat(t_philo *philo)
{
	size_t	time;

	take_forks(philo);
	time = get_time();
	pthread_mutex_lock(&philo->last_eats_mutex);
	philo->last_eat = time;
	pthread_mutex_unlock(&philo->last_eats_mutex);
	if (philo->args->min_eats > 0)
	{
		pthread_mutex_lock(&philo->eats_mutex);
		philo->eats++;
		pthread_mutex_unlock(&philo->eats_mutex);
	}
	ft_sleep(philo->args->time_eat);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	pthread_mutex_lock(&philo->args->print);
	pthread_mutex_unlock(&philo->args->print);
	pthread_mutex_lock(&philo->last_eats_mutex);
	philo->last_eat = philo->args->start;
	pthread_mutex_unlock(&philo->last_eats_mutex);
	if (philo->id % 2 == 0)
		ft_sleep(philo->args->time_eat - 10);
	while (1)
	{
		routine_eat(philo);
		print_sleep(philo);
		ft_sleep(philo->args->time_sleep);
		print_think(philo);
	}
	return (NULL);
}
