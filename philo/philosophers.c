/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphoebe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:49:13 by rphoebe           #+#    #+#             */
/*   Updated: 2021/08/26 11:49:15 by rphoebe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->flag == 1)
	{
		if ((philo->order) % 2 == 0)
			take_fork_even(philo);
		else
			take_fork_odd(philo);
	}
	return (NULL);
}

void	start_timer(t_data *data)
{
	int	i;

	i = -1;
	data->starttime = get_time();
	while (++i < data->number_of_philos)
	{
		data->philosophers[i].starttime = data->starttime;
		data->philosophers[i].last_meal = data->starttime;
	}
}

int	any_deaths(t_data *data)
{
	int	i;
	int	yes;

	i = -1;
	yes = 0;
	while (++i < data->number_of_philos)
	{
		if ((get_time() - (data->philosophers[i].last_meal \
		+ data->philosophers[i].time_to_die)) > 0)
		{
			pthread_mutex_lock(&data->philosophers[i].action_mutex);
			print_info(data->philosophers + i, "is dead\n");
			return (simulation_end(data));
		}
		if (data->eat_at_least > 0 && data->philosophers[i].feed)
			yes++;
	}
	if ((yes >= data->number_of_philos && data->eat_at_least > 0) || data->end)
	{
		if (pthread_mutex_lock(&data->print_mutex))
			ft_error(4);
		return (simulation_end(data));
	}
	return (1);
}

int	simulation_start(t_data *data)
{
	int	i;

	i = -1;
	start_timer(data);
	while (++i < data->number_of_philos)
	{
		if ((data->philosophers[i].order) % 2 != 0)
		{
			if (pthread_create(&data->t[i], NULL, routine, \
			 (void *)&data->philosophers[i]))
				return (ft_error(5));
		}
	}
	i = -1;
	while (++i < data->number_of_philos)
	{
		if ((data->philosophers[i].order) % 2 == 0)
		{
			if (pthread_create(&data->t[i], NULL, routine, \
			(void *)&data->philosophers[i]))
				return (ft_error(5));
		}	
	}
	return (infinite(data));
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (ft_error(1));
	if (ft_parcer(&data, argv, argc))
		return (0);
	return (simulation_start(&data));
}
