/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:08:12 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/30 12:24:39 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

static void	putnbr(int nb, int fd)
{
	if (nb <= -10)
		putnbr(nb / 10, fd);
	putchar_fd(-(nb % 10) + '0', fd);
}

void	putnbr_fd(int nb, int fd)
{
	if (nb < 0)
		putchar_fd('-', fd);
	else
		nb = -nb;
	putnbr(nb, fd);
}
