/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student-42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 19:21:06 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/08/23 20:15:18 by fmarin-p         ###   ########.fr       */
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
//	printf("\033[0;37m");
	printf("%d ", time_diff(&table->g_start, &stats->end));
	printf("%s", choose_color(message));
	printf("%d %s\n", stats->pos, message);
	pthread_mutex_unlock(&table->print);
}

void	get_to_eat(t_table *table, t_stats *stats)
{
	stats->already_eating = 1;
	print_stat(table, stats, EAT);
	if (!--stats->meals_left)
	{
		pthread_mutex_lock(&table->lock);
		if (++table->n_philosophers_full == table->n_philosophers)
			table->dead = 1;
		pthread_mutex_unlock(&table->lock);
	}
	usleep(table->time_to_eat * 1000);
	gettimeofday(&stats->start, NULL);
	pthread_mutex_unlock(&table->fork[stats->left_fork]);
	pthread_mutex_unlock(&table->fork[stats->right_fork]);
	stats->already_eating = 0;
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
	return (stats);
}

void	*philo_routine(void *p)
{
	t_table		*table;
	t_stats		*stats;

	table = (t_table *)p;
	stats = init_philo(table);
	while (1)
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
		usleep(table->time_to_sleep * 1000);
		print_stat(table, stats, THINK);
		if (table->dead)
			break ;
	}
	return (0);
}
