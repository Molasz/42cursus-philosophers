/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:08:12 by molasz-a          #+#    #+#             */
/*   Updated: 2024/06/30 19:02:12 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

void	putnbr_fd(size_t nb, int fd)
{
	char	c;

	c = nb % 10 + 48;
	if (nb >= 10)
		putnbr_fd(nb / 10, fd);
	write(fd, &c, 1);
}

int	print_action(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->mutex);
	if (philo->stop)
		return (pthread_mutex_unlock(&philo->mutex), 1);
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_lock(philo->print);
	putnbr_fd(get_time() - *philo->start, 1);
	write(1, " ", 1);
	putnbr_fd(philo->id, 1);
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(philo->print);
	return (0);
}
