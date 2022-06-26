/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphoebe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:48:45 by rphoebe           #+#    #+#             */
/*   Updated: 2021/08/26 11:48:47 by rphoebe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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

void	proc_killer(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philos)
		kill(data->pids[i], SIGKILL);
}

void	simulation_stop(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philos)
	{
		if (sem_close(data->philosophers[i].action_sem))
			ft_error(3);
		if (sem_close(data->philosophers[i].fed_sem))
			ft_error(3);
	}
	if (sem_close(data->print_sem))
		ft_error(3);
	if (sem_close(data->death_sem))
		ft_error(3);
	if (sem_close(data->forks))
		ft_error(3);
	free(data->philosophers);
	free(data->pids);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->flag)
	{
		sem_wait(philo->forks);
		print_info(philo, "has taken a fork\n");
		sem_wait(philo->forks);
		print_info(philo, "has taken a fork\n");
		sem_wait(philo->action_sem);
		print_info(philo, "is eating\n");
		sem_post(philo->action_sem);
		philo->last_meal = get_time();
		ft_usleep(philo->time_to_eat);
		philo->eated++;
		if (philo->eated == philo->eat_at_least)
			sem_post(philo->fed_sem);
		sem_post(philo->forks);
		sem_post(philo->forks);
		print_info(philo, "is sleeping\n");
		ft_usleep(philo->time_to_sleep);
		print_info(philo, "is thinking\n");
	}
	return (NULL);
}

void	life(t_philo *philo)
{
	pthread_t	t;
	int			i;

	if (pthread_create(&t, NULL, &routine, (void *)philo))
		ft_error(4);
	while (1)
	{
		if (get_time() - (philo->last_meal + philo->time_to_die) > 0)
		{
			sem_wait(philo->print_sem);
			sem_wait(philo->action_sem);
			printf("%ld %d is dead\n", get_time() \
			- philo->starttime, philo->order);
			philo->flag = -100;
			break ;
		}
		ft_usleep(1);
	}
	sem_post(philo->death_sem);
	while (1)
		i = 0;
}
