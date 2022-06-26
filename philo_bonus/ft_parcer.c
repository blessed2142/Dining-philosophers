/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parcer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphoebe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:48:10 by rphoebe           #+#    #+#             */
/*   Updated: 2021/08/26 11:48:11 by rphoebe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	philosophers_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philos)
		philosopher_init_helper(data, i);
}

void	sem_maker(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/death");
	data->forks = sem_open("/forks", O_CREAT | O_EXCL, 0777, \
	 data->number_of_philos);
	data->print_sem = sem_open("/print", O_CREAT | O_EXCL, 0777, 1);
	data->death_sem = sem_open("/death", O_CREAT | O_EXCL, 0777, 1);
	if (data->forks == SEM_FAILED || data->print_sem == SEM_FAILED || \
	data->death_sem == SEM_FAILED)
		ft_error(3);
	sem_wait(data->death_sem);
}

void	after_parcer_init(t_data *data)
{
	int	i;

	i = -1;
	data->pids = malloc(sizeof(int) * data->number_of_philos);
	if (data->pids == NULL)
		ft_error(2);
	data->philosophers = malloc(sizeof(t_philo) * data->number_of_philos);
	if (data->philosophers == NULL)
		ft_error(2);
	sem_maker(data);
	philosophers_init(data);
}

void	args_check(int argc, char **argv)
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
				ft_error(1);
		}
	}
}

void	ft_parcer(t_data *data, char **argv, int argc)
{
	args_check(argc, argv);
	data->number_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->eat_at_least = ft_atoi(argv[5]);
	else
		data->eat_at_least = -1;
	if (data->eat_at_least == 0)
		exit(0);
	data->end = 0;
	after_parcer_init(data);
}
