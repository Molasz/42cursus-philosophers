/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:21:07 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/29 12:13:58 by molasz-a         ###   ########.fr       */
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

static int	ft_atoi(char *str)
{
	size_t	i;
	int		count;
	int		sign;

	i = 0;
	sign = 1;
	count = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] == '0')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		count *= 10;
		count += str[i] - '0';
		i++;
	}
	return (count * sign);
}

static int	read_args(t_args *args, char **argv)
{
	args->philos = ft_atoi(argv[0]);
	args->time_die = ft_atoi(argv[1]);
	args->time_eat = ft_atoi(argv[2]);
	args->time_sleep = ft_atoi(argv[3]);
	if (argv[4])
		args->min_eats = ft_atoi(argv[4]);
	else
		args->min_eats = -1;
	return (0);
}

static int	check_args(t_args *args)
{
	if (!args->philos)
		return (print("Minimum 1 philosopher required\n", 2), 1);
	if (!args->time_die || !args->time_eat || !args->time_sleep)
		return (print("Can't run the program with time of 0ms\n", 2), 1);
	if (!args->min_eats)
		return (print("Can't run the program with min eats at 0\n", 2), 1);
	return (0);
}

int	parse(t_args *args, int argc, char **argv)
{
	if (argc < 5)
		return (print("Too few arguments\n", 2), 1);
	if (argc > 6)
		return (print("Too many arguments\n", 2), 1);
	if (check_chars(argv + 1))
		return (print("Only digit characters permitted\n", 2), 1);
	if (read_args(args, argv + 1))
		return (1);
	if (check_args(args))
		return (1);
	return (0);
}
