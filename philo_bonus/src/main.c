/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:31:30 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/08/23 14:32:54 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*create_philo(int argc, char **argv)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	philo->n_philosophers = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->pos = 0;
	philo->already_eating = 0;
	if (argc > 5)
		philo->number_of_meals = ft_atoi(argv[5]);
	else
		philo->number_of_meals = -2;
	if (philo->n_philosophers == -1 || philo->time_to_die == -1
		|| philo->time_to_eat == -1 || philo->time_to_sleep == -1
		|| philo->number_of_meals == -1)
		return (0);
	return (philo);
}
/*
void	end_simulation(t_table *table, pthread_t *philo)
{
	int	i;

	i = -1;
	while (++i < table->n_philosophers)
		pthread_join(philo[i], NULL);
	i = -1;
	while (++i < table->n_philosophers)
		pthread_mutex_destroy(&table->fork[i]);
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->lock);
	free(table->fork);
	free(table->stats);
	free(philo);
	free(table);
}
*/

int	main_process(t_philo *philo)
{
	int	i;
	int	pid;
	int	status;

	i = -1;
	gettimeofday(&philo->g_start, NULL);
	sem_unlink("FORKS");
	sem_unlink("GET_FORKS");
	sem_unlink("PRINT");
	while (++i < philo->n_philosophers)
	{
		philo->pos++;
		pid = fork();
		if (!pid)
			philo_routine(philo);
	}
	waitpid(-1, &status, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*default_philo;

	if (argc < 5 || argc > 6)
	{
		printf("Correct usage: ./philo number_of_philosophers ");
		printf("time_to_die time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	default_philo = create_philo(argc, argv);
	if (!default_philo)
	{
		printf("Error while parsing arguments.\n");
		return (0);
	}
	if (main_process(default_philo))
		printf("Error while creating processes\n");
	return (0);
}
