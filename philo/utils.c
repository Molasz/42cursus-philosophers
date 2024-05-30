/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:25:40 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/31 00:03:44 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep(int mili)
{
	int	start;

	start = get_time();
	while (1)
	{
		if (get_time() - start >= mili)
			break ;
	}
}

int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_time_philo(int time, int philo)
{
	putnbr_fd(get_time() - time, 1);
	print(" ", 1);
	putnbr_fd(philo, 1);
}
