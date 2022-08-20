/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student-42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 19:21:06 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/08/20 20:43:15 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	get_fork(t_table *table, t_stats *stats, int fork)
{
	pthread_mutex_lock(&table->fork[fork]);
	gettimeofday(&stats->end, NULL);
	if (time_diff(stats->start, stats->end) < table->time_to_die)
		print_stat(table, stats, FORK);
	else
	{
		print_stat(table, stats, DEAD);
		table->dead = 1;
	}
}

void	get_to_sleep(t_table *table, t_stats *stats)
{
	print_stat(table, stats, SLEEP);
	usleep(table->time_to_sleep * 1000);
	gettimeofday(&stats->end, NULL);
	if (time_diff(stats->start, stats->end) >= table->time_to_die)
	{
		print_stat(table, stats, DEAD);
		table->dead = 1;
	}
}

void	get_to_eat(t_table *table, t_stats *stats)
{
	print_stat(table, stats, EAT);
	usleep(table->time_to_eat * 1000);
	pthread_mutex_unlock(&table->fork[stats->left_fork]);
	pthread_mutex_unlock(&table->fork[stats->right_fork]);
	gettimeofday(&stats->start, NULL);
}

void	*philo_routine(void *p)
{
	t_table	*table;
	t_stats	stats;

	table = (t_table *)p;
	stats = init_stats(&table->print, table->n_philosophers);
	if (!table->g_start.tv_sec)
		gettimeofday(&table->g_start, NULL);
	gettimeofday(&stats.start, NULL);
	while (1)
	{
		if (stats.pos % 2 == 0)
			usleep(500000);
		get_fork(table, &stats, stats.left_fork);
		get_fork(table, &stats, stats.right_fork);
		get_to_eat(table, &stats);
		get_to_sleep(table, &stats);
		print_stat(table, &stats, THINK);
		if (table->dead)
			break ;
	}
	return (0);
}
