/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphoebe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 10:59:16 by rphoebe           #+#    #+#             */
/*   Updated: 2021/08/31 10:59:17 by rphoebe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/wait.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				order;
	int				left_fork;
	int				right_fork;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long			starttime;
	long			last_meal;
	int				eated;
	int				eat_at_least;
	int				feed;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	action_mutex;
	int				flag;
}				t_philo;

typedef struct s_data
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_at_least;
	t_philo			*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_t		*t;
	long			starttime;
	int				end;
}				t_data;

int			ft_error(int code);
int			ft_atoi(char *str);
int			ft_parcer(t_data *data, char **argv, int argc);
long int	get_time(void);
void		ft_usleep(long time_to_sleep);
int			simulation_end(t_data *data);
void		ft_putnbr_fd(long int n, int fd);
void		print_info(t_philo *philo, char *info);
void		take_fork_even(t_philo *philo);
void		take_fork_odd(t_philo *philo);
int			infinite(t_data *data);
int			any_deaths(t_data *data);
int			ft_strlen(const char *str);
int			ft_isdigit(int c);
#endif
