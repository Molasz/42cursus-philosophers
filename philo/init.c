/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:06:32 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/01 21:36:27 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_chars(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
		}
	}
	return (0);
}

int	init_params(t_params *params, int argc, char **argv)
{
	if (argc < 5)
	{
		printf("./philo number_philos time_die ");
		printf("time_eat time_sleep [number_eat]\n");
		return (0);
	}
	if (check_chars(argv))
		return (printf("Only numeric chars allowed\n"), 0);
	params->num = ft_atoi(argv[1]);
	params->time_die = ft_atoi(argv[2]);
	params->time_eat = ft_atoi(argv[3]);
	params->time_sleep = ft_atoi(argv[4]);
	params->max_meals = -1;
	params->death = 0;
	if (argc > 5)
	{
		params->max_meals = ft_atoi(argv[5]);
		if (ft_atoi(argv[5]) < 0)
			return (0);
	}
	if (params->num <= 0 || params->time_die < 0 || params->time_eat < 0
		|| params->time_sleep < 0)
		return (0);
	pthread_mutex_init(&params->print, NULL);
	return (pthread_mutex_init(&params->mutex_death, NULL), 1);
}

static void	init_philo(t_data *data, int i)
{
	t_philo	*philo;

	philo = data->philos + i;
	philo->params = data->params;
	philo->id = i;
	philo->last_meal = 0;
	philo->meal_count = 0;
	philo->r_fork = data->forks + i;
	philo->r_taken = 0;
	philo->l_taken = 0;
	if (i == data->params->num - 1)
		philo->l_fork = data->forks;
	else
		philo->l_fork = data->forks + i + 1;
	philo->l_fork->used = 0;
	pthread_mutex_init(&philo->mutex, NULL);
	pthread_mutex_init(&philo->mutex, NULL);
}

int	create_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->params->num);
	if (!data->philos)
		return (0);
	data->forks = malloc(sizeof(t_fork) * data->params->num);
	if (!data->forks)
		return (free(data->philos), 0);
	i = -1;
	while (++i < data->params->num)
		init_philo(data, i);
	return (1);
}
