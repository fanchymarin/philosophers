/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student-42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 19:21:06 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/09/02 10:30:38 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_stat(t_philo *philo, char *message)
{
	sem_wait(philo->print);
//	printf("\033[0;37m");
	printf("%d ", time_diff(&philo->g_start, &philo->end));
	printf("%s", choose_color(message));
	printf("%d %s\n", philo->pos, message);
	if (ft_strncmp(message, DEAD, 5))
		sem_post(philo->print);
}

void	get_to_eat(t_philo *philo)
{
	philo->already_eating = 1;
	print_stat(philo, EAT);
	usleep(philo->time_to_eat * 1000);
	gettimeofday(&philo->start, NULL);
	sem_post(philo->forks);
	sem_post(philo->forks);
	if (!--philo->number_of_meals)
		exit(2);
	philo->already_eating = 0;
}

void	*proc_monitoring(void *p)
{
	t_philo	*philo;

	philo = p;
	while (1)
	{
		usleep(100);
		gettimeofday(&philo->end, NULL);
		if (time_diff(&philo->start, &philo->end)
			>= philo->time_to_die && !philo->already_eating)
		{
			print_stat(philo, DEAD);
			exit(1);
		}
	}
	return (0);
}

void	philo_routine(t_philo *philo)
{
	gettimeofday(&philo->start, NULL);
	gettimeofday(&philo->end, NULL);
	pthread_create(&philo->proc_monitoring, NULL, proc_monitoring, philo);
	while (1)
	{
		sem_wait(philo->forks);
		print_stat(philo, FORK);
		sem_wait(philo->forks);
		print_stat(philo, FORK);
		get_to_eat(philo);
		print_stat(philo, SLEEP);
		usleep(philo->time_to_sleep * 1000);
		print_stat(philo, THINK);
	}
}
