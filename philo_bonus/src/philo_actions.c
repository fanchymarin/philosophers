/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student-42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 19:21:06 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/08/23 15:37:13 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_stat(t_philo *philo, char *message)
{
	sem_wait(philo->print);
	printf("\033[0;37m");
	printf("[%d] ", time_diff(&philo->g_start, &philo->end));
	printf("%s", choose_color(message));
	printf("%d %s\n", philo->pos, message);
	sem_post(philo->print);
}

void	get_to_eat(t_philo *philo)
{
	philo->already_eating = 1;
	print_stat(philo, EAT);
	if (!--philo->number_of_meals)
		printf("pendiente de gestionar jj\n");
	usleep(philo->time_to_eat * 1000);
	gettimeofday(&philo->start, NULL);
	sem_post(philo->forks);
	sem_post(philo->forks);
	philo->already_eating = 0;
}

void	*proc_monitoring(void *p)
{
	t_philo	*philo;

	philo = p;
	while (1)
	{
		gettimeofday(&philo->end, NULL);
		if (time_diff(&philo->start, &philo->end)
			>= philo->time_to_die && !philo->already_eating)
		{
			print_stat(philo, DEAD);
			kill(0, SIGQUIT);
		}
	}
	return (0);
}

void	philo_routine(t_philo *philo)
{
	philo->forks = sem_open("FORKS", O_CREAT, 0777,
			philo->n_philosophers);
	philo->print = sem_open("PRINT", O_CREAT, 0777, 1);
	philo->get_forks = sem_open("GET_FORKS", O_CREAT, 0777, 2);
	if (philo->get_forks == SEM_FAILED)
		perror("sem_open:");
	gettimeofday(&philo->start, NULL);
	pthread_create(&philo->proc_monitoring, NULL, proc_monitoring, philo);
	while (1)
	{
		sem_wait(philo->get_forks);
		sem_wait(philo->forks);
		print_stat(philo, FORK);
		sem_wait(philo->forks);
		print_stat(philo, FORK);
		sem_post(philo->get_forks);
		get_to_eat(philo);
		print_stat(philo, SLEEP);
		usleep(philo->time_to_sleep * 1000);
		print_stat(philo, THINK);
	}
}
