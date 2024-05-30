/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:04:59 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/30 18:01:14 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex->print);
	print_time_philo(philo->args->start, philo->id);
	print(" has taken a fork\n", 1);
	pthread_mutex_unlock(&philo->mutex->print);
}

void	print_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex->print);
	print_time_philo(philo->args->start, philo->id);
	print(" is eating\n", 1);
	pthread_mutex_unlock(&philo->mutex->print);
}

void	print_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex->print);
	print_time_philo(philo->args->start, philo->id);
	print(" is sleeping\n", 1);
	pthread_mutex_unlock(&philo->mutex->print);
}

void	print_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex->print);
	print_time_philo(philo->args->start, philo->id);
	print(" is thinking\n", 1);
	pthread_mutex_unlock(&philo->mutex->print);
}

void	print_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex->print);
	print_time_philo(philo->args->start, philo->id);
	print(" died\n", 1);
	pthread_mutex_unlock(&philo->mutex->print);
}
