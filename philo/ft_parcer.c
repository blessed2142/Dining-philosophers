/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parcer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphoebe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:49:03 by rphoebe           #+#    #+#             */
/*   Updated: 2021/08/26 11:49:04 by rphoebe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philosophers_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philos)
	{
		data->philosophers[i].flag = 1;
		data->philosophers[i].eated = 0;
		data->philosophers[i].feed = 0;
		data->philosophers[i].eat_at_least = data->eat_at_least;
		data->philosophers[i].forks = data->forks;
		data->philosophers[i].print_mutex = &data->print_mutex;
		data->philosophers[i].time_to_die = data->time_to_die;
		data->philosophers[i].time_to_eat = data->time_to_eat;
		data->philosophers[i].time_to_sleep = data->time_to_sleep;
		data->philosophers[i].order = i + 1;
		data->philosophers[i].right_fork = i;
		data->philosophers[i].left_fork = i - 1;
		if (i == 0)
		{
			data->philosophers[i].left_fork = data->number_of_philos - 1;
			if (data->philosophers[i].left_fork < 0)
				data->philosophers[i].left_fork = 0;
		}
	}
}

int	mutex_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (ft_error(4));
	}
	i = -1;
	while (++i < data->number_of_philos)
	{
		if (pthread_mutex_init(&data->philosophers[i].action_mutex, NULL))
			ft_error(4);
	}
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (ft_error(4));
	return (0);
}

int	after_parcer_init(t_data *data)
{
	data->philosophers = malloc(sizeof(t_philo) * data->number_of_philos);
	if (data->philosophers == NULL)
		return (ft_error(2));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philos);
	if (data->forks == NULL)
		return (ft_error(2));
	data->t = malloc(sizeof(pthread_t) * data->number_of_philos);
	if (data->t == NULL)
		return (ft_error(2));
	if (mutex_init(data))
		return (1);
	philosophers_init(data);
	return (0);
}

int	args_check(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (ft_error(1));
		}
	}
	return (0);
}

int	ft_parcer(t_data *data, char **argv, int argc)
{
	if (args_check(argc, argv))
		return (1);
	data->number_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->eat_at_least = ft_atoi(argv[5]);
	else
		data->eat_at_least = -1;
	if (data->eat_at_least == 0)
		return (1);
	data->end = 0;
	return (after_parcer_init(data));
}
