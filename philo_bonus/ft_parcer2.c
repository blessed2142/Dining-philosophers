/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parcer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphoebe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:48:31 by rphoebe           #+#    #+#             */
/*   Updated: 2021/08/26 11:48:32 by rphoebe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	sem_name_maker(char *sem_name, char *reference, int order)
{
	int	i;

	i = -1;
	if (reference[1] == 'a')
	{
		while (++i < 8)
			sem_name[i] = reference[i];
		sem_name[i] = '\0';
		sem_name[7] = order + 49;
	}
	else
	{
		while (++i < 5)
			sem_name[i] = reference[i];
		sem_name[i] = '\0';
		sem_name[4] = order + 49;
	}
}

void	philosopher_init_helper2(t_data *data, int i)
{
	data->philosophers[i].flag = 1;
	data->philosophers[i].eated = 0;
	data->philosophers[i].feed = 0;
	data->philosophers[i].eat_at_least = data->eat_at_least;
	data->philosophers[i].forks = data->forks;
	data->philosophers[i].print_sem = data->print_sem;
	data->philosophers[i].death_sem = data->death_sem;
	data->philosophers[i].time_to_die = data->time_to_die;
	data->philosophers[i].time_to_eat = data->time_to_eat;
	data->philosophers[i].time_to_sleep = data->time_to_sleep;
	data->philosophers[i].order = i + 1;
}

void	philosopher_init_helper(t_data *data, int i)
{
	philosopher_init_helper2(data, i);
	data->philosophers[i].sem_name = malloc(sizeof(char) * 9);
	if (data->philosophers[i].sem_name == NULL)
		ft_error(2);
	sem_name_maker(data->philosophers[i].sem_name, "/actionx", i);
	sem_unlink(data->philosophers[i].sem_name);
	data->philosophers[i].action_sem = sem_open(data->philosophers[i] \
	 .sem_name, O_CREAT | O_EXCL, 0777, 1);
	free(data->philosophers[i].sem_name);
	data->philosophers[i].fed_name = malloc(sizeof(char) * 6);
	if (data->philosophers[i].fed_name == NULL)
		ft_error(2);
	sem_name_maker(data->philosophers[i].fed_name, "/fedx", i);
	sem_unlink(data->philosophers[i].fed_name);
	data->philosophers[i].fed_sem = sem_open(\
		data->philosophers[i].fed_name, O_CREAT | O_EXCL, 0777, 1);
	sem_wait(data->philosophers[i].fed_sem);
	free(data->philosophers[i].fed_name);
	if (data->philosophers[i].fed_sem == SEM_FAILED \
	|| data->philosophers[i].action_sem == SEM_FAILED)
		ft_error(3);
}
