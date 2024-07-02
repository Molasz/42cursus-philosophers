/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:06:30 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/02 18:44:14 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_fork(t_philo *philo)
{
	sem_wait(philo->params->forks);
	write_state("has taken a fork", philo);
}

void	release_forks_and_sleep(t_philo *philo)
{
	sem_post(philo->params->forks);
	sem_post(philo->params->forks);
	write_state("is sleeping", philo);
	ft_usleep(philo->params->time_sleep);
}
