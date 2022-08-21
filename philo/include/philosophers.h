/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student-42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:13:19 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/08/21 17:43:37 by fmarin-p         ###   ########.fr       */
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

typedef struct s_stats
{
	int				pos;
	int				left_fork;
	int				right_fork;
	int				meals_left;
	int				already_eating;
	struct timeval	start;
	struct timeval	end;
}	t_stats;

typedef struct s_table
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	lock;
	pthread_mutex_t	print;
	t_stats			*stats;
	int				order;
	int				n_philosophers;
	int				n_philosophers_full;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	int				dead;
	struct timeval	g_start;
}	t_table;

//Utils
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	init_stats(t_table *table, t_stats *stats);
int		time_diff(struct timeval *start, struct timeval *end);
char	*choose_color(char *message);

//Philo actions
void	get_to_eat(t_table *table, t_stats *stats);
void	*philo_routine(void *p);
void	print_stat(t_table *table, t_stats *stats, char *message);

#endif
