/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:06:38 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/02 18:55:48 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philo(t_data *data, int i)
{
	char	*pos_str;
	char	*sem_name;

	data->philos[i].params = data->params;
	data->philos[i].id = i;
	data->philos[i].last_meal = 0;
	data->philos[i].meal_count = 0;
	pos_str = ft_itoa(data->philos[i].id);
	sem_name = ft_strjoin("/sem_last_meal", pos_str);
	sem_unlink(sem_name);
	data->philos[i].semaphore = sem_open(sem_name, O_CREAT, 0644, 1);
	sem_unlink(sem_name);
	free(pos_str);
	free(sem_name);
}

int	create_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->params->num);
	if (!data->philos)
		return (0);
	i = -1;
	while (++i < data->params->num)
		init_philo(data, i);
	return (1);
}

void	init_sem(t_params *params)
{
	sem_unlink("/sem_forks");
	sem_unlink("/sem_console");
	sem_unlink("/finished");
	params->forks = sem_open("/sem_forks", O_CREAT, 0644, params->num);
	params->print = sem_open("/sem_console", O_CREAT, 0644, 1);
	params->finish = sem_open("/finished", O_CREAT, 0644, 1);
	sem_unlink("/sem_forks");
	sem_unlink("/sem_console");
	sem_unlink("/finished");
	sem_wait(params->finish);
}

int	init_params(t_params *params, int argc, char **argv)
{
	if (argc < 5)
	{
		printf("Usage : ./philo number_philos time_die ");
		printf("time_eat time_sleep [number_eat]\n");
		return (0);
	}
	params->num = ft_atoi(argv[1]);
	params->time_die = ft_atoi(argv[2]);
	params->time_eat = ft_atoi(argv[3]);
	params->time_sleep = ft_atoi(argv[4]);
	params->max_meals = -1;
	if (argc > 5)
	{
		params->max_meals = ft_atoi(argv[5]);
		if (ft_atoi(argv[5]) < 0)
			return (0);
	}
	if (params->num <= 0 || params->time_die < 0 || params->time_eat < 0
		|| params->time_sleep < 0)
		return (0);
	init_sem(params);
	return (1);
}
