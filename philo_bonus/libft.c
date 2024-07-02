/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 00:32:19 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/02 18:19:35 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	num_len(unsigned int n)
{
	int	i;

	i = 0;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i + 1);
}

static unsigned int	ft_abs(int n, int *size)
{
	unsigned int	num;

	num = (unsigned int)n;
	if (n < 0)
	{
		num = (unsigned int)-n;
		*size += 1;
	}
	return (num);
}

char	*ft_itoa(int n)
{
	unsigned int	num;
	char			*str;
	int				str_size;
	int				str_count;

	str_size = 0;
	num = ft_abs(n, &str_size);
	str_size += num_len(num);
	str = malloc(sizeof (char) * (str_size + 1));
	if (!str)
		return (NULL);
	str[str_size] = 0;
	if (n < 0)
		str[0] = '-';
	str_count = str_size - 1;
	while ((n >= 0 && str_count >= 0) || (n < 0 && str_count))
	{
		str[str_count] = (num % 10) + '0';
		num /= 10;
		str_count--;
	}
	return (str);
}

int	ft_atoi(char *str)
{
	int	i;
	int	count;
	int	sign;

	i = 0;
	sign = 1;
	count = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		count *= 10;
		count += str[i] - '0';
		i++;
	}
	return (count * sign);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ret;
	char	*realret;

	ret = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ret)
		return (NULL);
	realret = ret;
	while (*s1)
		*ret++ = *s1++;
	while (*s2)
		*ret++ = *s2++;
	*ret = 0;
	return (realret);
}
