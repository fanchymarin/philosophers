/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student-42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:13:19 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/08/23 13:56:27 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <semaphore.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEAD "died"

typedef struct s_philo
{
	sem_t			*forks;
	sem_t			*get_forks;
	sem_t			*print;
	pthread_t		proc_monitoring;
	int				pos;
	int				n_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	int				already_eating;
	struct timeval	g_start;
	struct timeval	start;
	struct timeval	end;
}	t_philo;

//Utils
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		time_diff(struct timeval *start, struct timeval *end);
char	*choose_color(char *message);

//Philo actions
//void	get_to_eat(t_table *table, t_stats *stats);
void	philo_routine(t_philo *philo);
void	print_stat(t_philo *philo, char *message);

#endif
