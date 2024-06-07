/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:04:59 by molasz-a          #+#    #+#             */
/*   Updated: 2024/06/07 17:25:52 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_fork(t_philo *philo)
{
	size_t	time;

	time = get_time() - philo->args->start;
	pthread_mutex_lock(&philo->args->death_mutex);
	if (philo->args->death)
		return (1);
	pthread_mutex_unlock(&philo->args->death_mutex);
	pthread_mutex_lock(&philo->args->print);
	print_time_philo(time, philo->id);
	print(" has taken a fork\n", 1);
	pthread_mutex_unlock(&philo->args->print);
	return (0);
}

int	print_eat(t_philo *philo)
{
	size_t	time;

	time = get_time() - philo->args->start;
	pthread_mutex_lock(&philo->args->death_mutex);
	if (philo->args->death)
		return (1);
	pthread_mutex_unlock(&philo->args->death_mutex);
	pthread_mutex_lock(&philo->args->print);
	print_time_philo(time, philo->id);
	print(" is eating\n", 1);
	pthread_mutex_unlock(&philo->args->print);
	return (0);
}

int	print_sleep(t_philo *philo)
{
	size_t	time;

	time = get_time() - philo->args->start;
	pthread_mutex_lock(&philo->args->death_mutex);
	if (philo->args->death)
		return (1);
	pthread_mutex_unlock(&philo->args->death_mutex);
	pthread_mutex_lock(&philo->args->print);
	print_time_philo(time, philo->id);
	print(" is sleeping\n", 1);
	pthread_mutex_unlock(&philo->args->print);
	return (0);
}

int	print_think(t_philo *philo)
{
	size_t	time;

	time = get_time() - philo->args->start;
	pthread_mutex_lock(&philo->args->death_mutex);
	if (philo->args->death)
		return (1);
	pthread_mutex_unlock(&philo->args->death_mutex);
	pthread_mutex_lock(&philo->args->print);
	print_time_philo(time, philo->id);
	print(" is thinking\n", 1);
	pthread_mutex_unlock(&philo->args->print);
	return (0);
}

void	print_died(t_philo *philo)
{
	size_t	time;

	time = get_time() - philo->args->start;
	print_time_philo(time, philo->id);
	print(" died\n", 1);
}
