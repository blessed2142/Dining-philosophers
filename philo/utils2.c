/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphoebe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:49:22 by rphoebe           #+#    #+#             */
/*   Updated: 2021/08/26 11:49:23 by rphoebe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(long int n, int fd)
{
	long int	nn;
	int			i;
	char		c;

	nn = n;
	i = 0;
	if (nn < 0)
	{
		ft_putchar_fd('-', fd);
		nn = -nn;
	}
	if (nn > 9)
	{
		ft_putnbr_fd(nn / 10, fd);
		ft_putnbr_fd(nn % 10, fd);
	}
	if (nn < 10)
	{
		c = nn + '0';
		ft_putchar_fd(c, fd);
	}
}

void	print_info(t_philo *philo, char *info)
{
	if (philo->flag != 1)
		return ;
	if (pthread_mutex_lock(philo->print_mutex))
		ft_error(4);
	if (philo->flag == 1)
	{
		ft_putnbr_fd(get_time() - philo->starttime, philo->flag);
		write(philo->flag, " ", 1);
		ft_putnbr_fd(philo->order, philo->flag);
		write(philo->flag, " ", 1);
		write(philo->flag, info, ft_strlen(info));
	}
	if (pthread_mutex_unlock(philo->print_mutex))
		ft_error(4);
	if (info[5] == 'a' && info[6] == 'd')
	{
		if (pthread_mutex_lock(philo->print_mutex))
			ft_error(4);
	}
}
