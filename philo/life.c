/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphoebe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:49:07 by rphoebe           #+#    #+#             */
/*   Updated: 2021/08/26 11:49:08 by rphoebe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleep_and_think(t_philo *philo)
{
	if (pthread_mutex_unlock(&philo->forks[philo->left_fork]))
		ft_error(4);
	if (pthread_mutex_unlock(&philo->forks[philo->right_fork]))
		ft_error(4);
	print_info(philo, "is sleeping\n");
	ft_usleep(philo->time_to_sleep);
	print_info(philo, "is thinking\n");
}

void	take_fork_odd(t_philo *philo)
{
	if (philo->flag != 1)
		return ;
	if (pthread_mutex_lock(&philo->forks[philo->right_fork]))
		ft_error(4);
	print_info(philo, "has taken a right fork\n");
	if (philo->flag != 1)
		return ;
	if (pthread_mutex_lock(&philo->forks[philo->left_fork]))
		ft_error(4);
	if (philo->flag != 1)
		return ;
	print_info(philo, "has taken a left fork\n");
	if (pthread_mutex_lock(&philo->action_mutex))
		ft_error(4);
	print_info(philo, "is eating\n");
	philo->last_meal = get_time();
	ft_usleep(philo->time_to_eat);
	philo->eated++;
	if (philo->flag != 1)
		return ;
	if (pthread_mutex_unlock(&philo->action_mutex))
		ft_error(4);
	if (philo->eated >= philo->eat_at_least)
		philo->feed = 1;
	sleep_and_think(philo);
}

void	take_fork_even(t_philo *philo)
{
	if (philo->flag != 1)
		return ;
	if (pthread_mutex_lock(&philo->forks[philo->left_fork]))
		ft_error(4);
	if (philo->flag != 1)
		return ;
	print_info(philo, "has taken a left fork\n");
	if (pthread_mutex_lock(&philo->forks[philo->right_fork]))
		ft_error(4);
	if (philo->flag != 1)
		return ;
	print_info(philo, "has taken a right fork\n");
	if (pthread_mutex_lock(&philo->action_mutex))
		ft_error(4);
	print_info(philo, "is eating\n");
	philo->last_meal = get_time();
	ft_usleep(philo->time_to_eat);
	if (philo->flag != 1)
		return ;
	if (pthread_mutex_unlock(&philo->action_mutex))
		ft_error(4);
	philo->eated++;
	if (philo->eated >= philo->eat_at_least)
		philo->feed = 1;
	sleep_and_think(philo);
}
