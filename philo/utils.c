/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:25:40 by molasz-a          #+#    #+#             */
/*   Updated: 2024/06/02 17:59:59 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep(size_t mili)
{
	size_t	start;
	size_t	time;

	start = get_time();
	while (1)
	{
		time = get_time();
		if (time - start >= mili)
			break ;
	}
}

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_time_philo(size_t time, int philo)
{
	putnbr_fd(time, 1);
	putchar_fd(' ', 1);
	putnbr_fd(philo, 1);
}
