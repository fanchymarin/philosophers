/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student-42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:28:40 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/10/05 16:00:52 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

int	time_diff(struct timeval *start, struct timeval *end)
{
	return (((end->tv_sec * 1000000 + end->tv_usec)
			- (start->tv_sec * 1000000 + start->tv_usec)) / 1000);
}

void	ft_usleep(int usec)
{
	struct timeval	start;
	struct timeval	end;
	int				i;

	i = 0;
	gettimeofday(&start, NULL);
	while (i++ <= usec)
	{
		gettimeofday(&end, NULL);
		if (time_diff(&start, &end) >= usec)
			break ;
		usleep(1000);
	}
}
