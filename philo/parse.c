/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:21:07 by molasz-a          #+#    #+#             */
/*   Updated: 2024/06/29 20:37:19 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_chars(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static size_t	ft_atoi(char *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i] == '0')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		count *= 10;
		count += str[i] - '0';
		i++;
	}
	return (count);
}

static int	read_args(t_data *data, char **argv)
{
	data->philos_num = ft_atoi(argv[0]);
	data->time_die = ft_atoi(argv[1]);
	data->time_eat = ft_atoi(argv[2]);
	data->time_sleep = ft_atoi(argv[3]);
	if (argv[4])
		data->min_eats = ft_atoi(argv[4]);
	else
		data->min_eats = -1;
	return (0);
}

static int	check_args(t_data *data)
{
	if (!data->philos_num)
		return (print("Minimum 1 philosopher required\n", 2), 1);
	if (!data->time_die || !data->time_eat || !data->time_sleep)
		return (print("Can't run the program with time of 0ms\n", 2), 1);
	if (!data->min_eats)
		return (print("Can't run the program with min eats at 0\n", 2), 1);
	return (0);
}

int	parse(t_data *data, int argc, char **argv)
{
	if (argc < 5)
		return (print("Too few arguments\n", 2), 1);
	if (argc > 6)
		return (print("Too many arguments\n", 2), 1);
	if (check_chars(argv + 1))
		return (print("Only digit characters permitted\n", 2), 1);
	if (read_args(data, argv + 1))
		return (1);
	if (check_args(data))
		return (1);
	return (0);
}
