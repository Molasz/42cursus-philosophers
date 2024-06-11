/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 23:52:56 by molasz-a          #+#    #+#             */
/*   Updated: 2024/06/11 19:23:26 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_death(t_philo *philo)
{
	int	death;
	pthread_mutex_lock(&philo->args->death_mutex);
	death = philo->args->death;
	pthread_mutex_unlock(&philo->args->death_mutex);
	return (death);
}

static int	take_forks(t_philo *philo)
{
	if (philo->id % 2)
		pthread_mutex_lock(&philo->l_fork);
	else 
		pthread_mutex_lock(philo->r_fork);
	print_action(philo, " take fork\n");
	if (!philo->r_fork)
		return (pthread_mutex_unlock(&philo->l_fork), 1);
	if (philo->id % 2)
		pthread_mutex_lock(philo->r_fork);
	else 
		pthread_mutex_lock(&philo->l_fork);
	print_action(philo, " take fork\n");
	print_action(philo, " is eating\n");
	return (0);
}

static int	routine_eat(t_philo *philo)
{

	take_forks(philo);
	pthread_mutex_lock(&philo->mutex);
	philo->last_eat = get_time();
	philo->eats++;
	pthread_mutex_unlock(&philo->mutex);
	ft_sleep(philo->args->time_eat);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (check_death(philo));
}

static void	philo_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->stopped = 1;
	pthread_mutex_unlock(&philo->mutex);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2 == 0)
		ft_sleep(philo->args->time_eat - 10);
	while (1)
	{
		if (routine_eat(philo))
			return (philo_stop(philo), NULL);
		print_action(philo, " is sleeping\n");
		ft_sleep(philo->args->time_sleep);
		if (check_death(philo))
			return (philo_stop(philo), NULL);
		print_action(philo, " is thinking\n");
	}
	return (NULL);
}
