/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 23:52:56 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/30 18:33:27 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	routine_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	print_fork(philo);
	pthread_mutex_lock(philo->r_fork);
	print_fork(philo);
	print_eat(philo);
	ft_sleep(philo->args->time_eat);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->eats++;
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->philo_mutex);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

static void	routine_sleep(t_philo *philo)
{
	print_sleep(philo);
	ft_sleep(philo->args->time_sleep);
}

static void	routine_think(t_philo *philo)
{
	print_think(philo);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2)
		ft_sleep(1);
	while (1)
	{
		routine_eat(philo);
		routine_sleep(philo);
		routine_think(philo);
	}
	return (NULL);
}
