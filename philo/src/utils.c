/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student-42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:28:40 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/08/20 20:36:39 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_usage(void)
{
	printf("Correct usage: ./philo number_of_philosophers ");
	printf("time_to_die time_to_eat time_to_sleep ");
	printf("[number_of_times_each_philosopher_must_eat]\n");
}

int	ft_atoi(const char *str)
{
	int	num;

	num = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32 || *str == 43)
		++str;
	if (*str == 45)
		return (-1);
	while (*str >= 48 && *str <= 57)
		num = num * 10 + (*(str++) - 48);
	if (*(--str) - 48 != num % 10)
		return (-1);
	while (*(++str))
		if (*str < 48 || *str > 57)
			return (-1);
	return (num);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < (n - 1) && s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*choose_color(char *message)
{
	if (!ft_strncmp(message, FORK, 5))
		return ("\033[0;33m");
	else if (!ft_strncmp(message, EAT, 5))
		return ("\033[0;32m");
	else if (!ft_strncmp(message, SLEEP, 5))
		return ("\033[0;34m");
	else if (!ft_strncmp(message, THINK, 5))
		return ("\033[0;35m");
	else if (!ft_strncmp(message, DEAD, 5))
		return ("\033[0;31m");
	return (0);
}

int	time_diff(struct timeval start, struct timeval end)
{
	return (((end.tv_sec * 1000000 + end.tv_usec)
			- (start.tv_sec * 1000000 + start.tv_usec)) / 1000);
}

void	print_stat(t_table *table, t_stats *stats, char *message)
{
	if (table->dead)
		return ;
	pthread_mutex_lock(&table->print);
	printf("\033[0;37m");
	printf("[%d] ", time_diff(table->g_start, stats->end));
	printf("%s", choose_color(message));
	printf("%d %s\n", stats->pos, message);
	pthread_mutex_unlock(&table->print);
}

t_stats	init_stats(pthread_mutex_t *lock, int last)
{
	static int	order = 1;
	t_stats		stats;

	pthread_mutex_lock(lock);
	stats.pos = order++;
	stats.left_fork = stats.pos - 1;
	if (stats.pos == last)
		stats.right_fork = 0;
	else
		stats.right_fork = stats.pos;
	pthread_mutex_unlock(lock);
	return (stats);
}
