/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:06:25 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/02 19:03:01 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_fork(t_philo *philo, int leftFork)
{
	t_fork	*fork;
	int		*taken;

	if (!is_dead(philo))
	{
		taken = &philo->r_taken;
		fork = philo->r_fork;
		if (leftFork)
		{
			taken = &philo->l_taken;
			fork = philo->l_fork;
		}
		pthread_mutex_lock(&fork->lock);
		if (!*taken && !fork->used)
		{
			*taken = 1;
			fork->used = 1;
			pthread_mutex_unlock(&fork->lock);
			write_state("has taken a fork", philo);
		}
		else
			pthread_mutex_unlock(&fork->lock);
	}
}

void	release_fork(t_philo *philo, int leftFork)
{
	t_fork	*fork;
	int		*taken;

	taken = &philo->r_taken;
	fork = philo->r_fork;
	if (leftFork)
	{
		taken = &philo->l_taken;
		fork = philo->l_fork;
	}
	pthread_mutex_lock(&fork->lock);
	*taken = 0;
	fork->used = 0;
	pthread_mutex_unlock(&fork->lock);
}

void	release_forks_and_sleep(t_philo *philo)
{
	release_fork(philo, 0);
	release_fork(philo, 1);
	write_state("is sleeping", philo);
	ft_usleep(philo->params->time_sleep);
}
