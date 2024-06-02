/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:08:12 by molasz-a          #+#    #+#             */
/*   Updated: 2024/06/02 18:01:34 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

void	putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	putnbr_fd(size_t nb, int fd)
{
	if (nb >= 10)
		putnbr_fd(nb / 10, fd);
	putchar_fd(nb % 10 + '0', fd);
}
