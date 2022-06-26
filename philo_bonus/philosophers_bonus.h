/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphoebe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:50:35 by rphoebe           #+#    #+#             */
/*   Updated: 2021/08/26 11:50:36 by rphoebe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philo
{
	int		order;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	long	starttime;
	long	last_meal;
	int		eated;
	int		eat_at_least;
	int		feed;
	char	*sem_name;
	char	*fed_name;
	sem_t	*forks;
	sem_t	*print_sem;
	sem_t	*action_sem;
	sem_t	*death_sem;
	sem_t	*fed_sem;

	int		flag;
}				t_philo;

typedef struct s_data
{
	int		number_of_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		eat_at_least;
	t_philo	*philosophers;
	sem_t	*forks;
	sem_t	*print_sem;
	sem_t	*death_sem;
	long	starttime;
	int		end;
	int		*pids;
}				t_data;

int			ft_error(int code);
int			ft_atoi(char *str);
void		ft_parcer(t_data *data, char **argv, int argc);
long int	get_time(void);
void		ft_usleep(long time_to_sleep);
int			simulation_end(t_data *data);
void		print_info(t_philo *philo, char *info);
void		philosopher_init_helper(t_data *data, int i);
void		start_timer(t_data *data);
void		proc_killer(t_data *data);
void		simulation_stop(t_data *data);
void		life(t_philo *philo);
void		*routine(void *arg);
void		ft_putnbr_fd(long int n, int fd);
int			ft_strlen(const char *str);
int			ft_isdigit(int c);
#endif
