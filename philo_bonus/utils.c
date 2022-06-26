/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphoebe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:48:41 by rphoebe           #+#    #+#             */
/*   Updated: 2021/08/26 11:48:42 by rphoebe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	print_info(t_philo *philo, char *info)
{
	sem_wait(philo->print_sem);
	if (philo->flag == 1)
	{
		ft_putnbr_fd(get_time() - philo->starttime, philo->flag);
		write(philo->flag, " ", 1);
		ft_putnbr_fd(philo->order, philo->flag);
		write(philo->flag, " ", 1);
		write(philo->flag, info, ft_strlen(info));
	}
	sem_post(philo->print_sem);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

long int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(long time_to_sleep)
{
	long	end;

	end = get_time() + time_to_sleep;
	while (get_time() < end)
		usleep(100);
}

int	ft_atoi(char *str)
{
	int	i;
	int	res;
	int	z;

	i = 0;
	z = 1;
	res = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] < 27 || (str[i] > 27 && str[i] < 33))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			z = -1;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		res = res * 10;
		res = res + str[i] - 48;
		i++;
	}
	return (res * z);
}
