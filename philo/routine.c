/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 23:52:56 by molasz-a          #+#    #+#             */
/*   Updated: 2024/06/30 19:03:20 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->l_fork);
	else
		pthread_mutex_lock(philo->r_fork);
	print_action(philo, " take fork\n");
	if (!philo->r_fork)
		return (pthread_mutex_unlock(&philo->l_fork), 1);
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->r_fork);
	else
		pthread_mutex_lock(&philo->l_fork);
	if (print_action(philo, " take fork\n")
		|| print_action(philo, " is eating\n"))
		return (1);
	return (0);
}

static int	routine_eat(t_philo *philo)
{
	if (take_forks(philo))
	{	
		pthread_mutex_unlock(&philo->l_fork);
		if (philo->r_fork)
			pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	pthread_mutex_lock(&philo->mutex);
	philo->eats++;
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->mutex);
	ft_sleep(philo->time_eat);
	pthread_mutex_unlock(&philo->l_fork);
	if (philo->r_fork)
		pthread_mutex_unlock(philo->r_fork);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	pthread_mutex_lock(philo->flag);
	pthread_mutex_unlock(philo->flag);
	if (philo->id % 2 == 0)
		ft_sleep(philo->time_eat - 10);
	while (1)
	{
		if (routine_eat(philo))
			return (NULL);
		if (print_action(philo, " is sleeping\n"))
			return (NULL);
		ft_sleep(philo->time_sleep);
		if (print_action(philo, " is thinking\n"))
			return (NULL);
	}
	return (NULL);
}
