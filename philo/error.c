/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphoebe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:48:57 by rphoebe           #+#    #+#             */
/*   Updated: 2021/08/26 11:48:58 by rphoebe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	if ((c > 47 && c < 58))
		return (1);
	else
		return (0);
}

int	simulation_end_helper(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philos)
	{
		pthread_mutex_unlock(&data->forks[i]);
		if (pthread_mutex_destroy(&data->forks[i]))
			return (ft_error(4));
	}
	i = -1;
	free(data->forks);
	free(data->t);
	free(data->philosophers);
	return (0);
}

int	simulation_end(t_data *data)
{
	int	i;

	i = -1;
	data->end = 1;
	while (++i < data->number_of_philos)
		data->philosophers[i].flag = -100;
	i = -1;
	while (++i < data->number_of_philos)
	{
		if (pthread_detach(data->t[i]))
			return (ft_error(3));
	}
	pthread_mutex_unlock(&data->print_mutex);
	ft_usleep(5000);
	if (pthread_mutex_destroy(&data->print_mutex))
		return (ft_error(4));
	i = -1;
	while (++i < data->number_of_philos)
	{
		if (pthread_mutex_unlock(&data->philosophers[i].action_mutex))
			return (ft_error(4));
		if (pthread_mutex_destroy(&data->philosophers[i].action_mutex))
			return (ft_error(4));
	}
	return (simulation_end_helper(data));
}

int	ft_error(int code)
{
	if (code == 1)
	{
		printf("ERROR: Invalid arguments\n");
		return (1);
	}
	else if (code == 2)
	{
		printf("ERROR: Memory allocation\n");
		return (2);
	}
	else if (code == 3)
	{
		printf("ERROR: Thread creat/detach\n");
		return (3);
	}
	else if (code == 4)
	{
		printf("ERROR: Mutex locked/unlocked/created/destroyed\n");
		return (4);
	}
	return (0);
}
