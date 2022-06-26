/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphoebe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:48:24 by rphoebe           #+#    #+#             */
/*   Updated: 2021/08/26 11:50:22 by rphoebe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_isdigit(int c)
{
	if ((c > 47 && c < 58))
		return (1);
	else
		return (0);
}

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

int	ft_error2(int code)
{
	if (code == 4)
	{
		printf("ERROR: Thread creating\n");
		exit(0);
	}
	else if (code == 5)
	{
		printf("ERROR: Process creating\n");
		exit(0);
	}
	return (0);
}

int	ft_error(int code)
{
	if (code == 1)
	{
		printf("ERROR: Invalid arguments\n");
		exit(0);
	}
	else if (code == 2)
	{
		printf("ERROR: Memory allocation problem\n");
		exit(0);
	}
	else if (code == 3)
	{
		printf("ERROR: Semaphore open/close\n");
		exit(0);
	}
	else if (code == 4)
		ft_error2(4);
	else if (code == 5)
		ft_error2(4);
	return (0);
}
