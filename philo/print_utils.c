/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:08:12 by molasz-a          #+#    #+#             */
/*   Updated: 2024/06/11 19:27:48 by molasz-a         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->args->print);
	putnbr_fd(get_time() - philo->args->start, 1);
	write(1, " ", 1);
	putnbr_fd(philo->id, 1);
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(&philo->args->print);
	return (0);
}
