/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student-42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 19:21:06 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/10/05 15:42:19 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_stat(t_table *table, t_stats *stats, char *message)
{
	pthread_mutex_lock(&table->print);
	if (table->dead)
	{
		pthread_mutex_unlock(&table->print);
		return ;
	}
	printf("\033[0;37m");
	printf("[%d] ", time_diff(&table->g_start, &stats->end));
	printf("%s", choose_color(message));
	printf("%d %s\n", stats->pos, message);
	pthread_mutex_unlock(&table->print);
}

void	init_stats(t_table *table, t_stats *stats)
{
	static int	order = 1;

	stats->pos = order++;
	stats->start.tv_sec = 0;
	stats->meals_left = table->number_of_meals;
	stats->right_fork = stats->pos - 1;
	if (stats->pos == table->n_philosophers)
		stats->left_fork = 0;
	else
		stats->left_fork = stats->pos;
}

void	get_to_eat(t_table *table, t_stats *stats)
{
	print_stat(table, stats, EAT);
	ft_usleep(table->time_to_eat);
	gettimeofday(&stats->start, NULL);
	if (!--stats->meals_left)
	{
		pthread_mutex_lock(&table->lock);
		if (++table->n_philosophers_full == table->n_philosophers)
			table->dead = 1;
		pthread_mutex_unlock(&table->lock);
	}
	pthread_mutex_unlock(&table->fork[stats->left_fork]);
	pthread_mutex_unlock(&table->fork[stats->right_fork]);
}

t_stats	*init_philo(t_table *table)
{
	t_stats	*stats;

	pthread_mutex_lock(&table->lock);
	if (!table->order)
		gettimeofday(&table->g_start, NULL);
	stats = &table->stats[table->order++];
	pthread_mutex_unlock(&table->lock);
	gettimeofday(&stats->start, NULL);
	gettimeofday(&stats->end, NULL);
	if (stats->pos % 2 == 0)
		usleep(100);
	return (stats);
}

void	*philo_routine(void *p)
{
	t_table		*table;
	t_stats		*stats;

	table = (t_table *)p;
	stats = init_philo(table);
	while (!table->dead)
	{
		pthread_mutex_lock(&table->fork[stats->left_fork]);
		print_stat(table, stats, FORK);
		if (stats->left_fork == stats->right_fork)
		{
			pthread_mutex_unlock(&table->fork[stats->left_fork]);
			break ;
		}
		pthread_mutex_lock(&table->fork[stats->right_fork]);
		print_stat(table, stats, FORK);
		get_to_eat(table, stats);
		print_stat(table, stats, SLEEP);
		ft_usleep(table->time_to_sleep);
		print_stat(table, stats, THINK);
	}
	return (0);
}
