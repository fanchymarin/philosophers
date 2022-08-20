/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student-42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:13:19 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/08/20 19:33:48 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEAD "died"

typedef struct s_table
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	int				n_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	int				dead;
	struct timeval	g_start;
}	t_table;

typedef struct s_stats
{
	int				pos;
	int				left_fork;
	int				right_fork;
	struct timeval	start;
	struct timeval	end;
}	t_stats;

//Utils
void	print_usage(void);
int		ft_atoi(const char *str);
t_stats	init_stats(pthread_mutex_t *lock, int last);
int		time_diff(struct timeval start, struct timeval end);
void	print_stat(t_table *table, t_stats *stats, char *message);

//Philo actions
void	get_fork(t_table *table, t_stats *stats, int fork);
void	get_to_sleep(t_table *table, t_stats *stats);
void	get_to_eat(t_table *table, t_stats *stats);
void	*philo_routine(void *p);

#endif
