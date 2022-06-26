/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphoebe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:48:36 by rphoebe           #+#    #+#             */
/*   Updated: 2021/08/26 11:48:37 by rphoebe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*fed(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = -1;
	while (++i < data->number_of_philos)
		sem_wait(data->philosophers[i].fed_sem);
	sem_post(data->death_sem);
	return (NULL);
}

void	simulation_start_helper(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philos)
		sem_post(data->philosophers[i].fed_sem);
	proc_killer(data);
	simulation_stop(data);
	exit(0);
}

int	simulation_start(t_data *data)
{
	int			i;
	pthread_t	fed_thread;

	i = -1;
	start_timer(data);
	while (++i < data->number_of_philos)
	{
		data->pids[i] = fork();
		if (data->pids[i] == 0)
			life(&data->philosophers[i]);
		else if (data->pids[i] < 0)
			ft_error(5);
	}
	if (data->pids[0] != 0)
	{
		if (data->eat_at_least > 0)
		{
			if (pthread_create(&fed_thread, NULL, &fed, (void *)data))
				ft_error(4);
		}
		sem_wait(data->death_sem);
		simulation_start_helper(data);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		ft_error(1);
	ft_parcer(&data, argv, argc);
	return (simulation_start(&data));
}
