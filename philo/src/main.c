/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:31:30 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/10/05 15:42:19 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_table	*create_table(int argc, char **argv)
{
	t_table	*table;
	int		i;

	table = malloc(sizeof(t_table));
	table->n_philosophers = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc > 5)
		table->number_of_meals = ft_atoi(argv[5]);
	else
		table->number_of_meals = -2;
	if (table->n_philosophers == -1 || table->time_to_die == -1
		|| table->time_to_eat == -1 || table->time_to_sleep == -1
		|| table->number_of_meals == -1)
	{
		free(table);
		return (0);
	}
	table->fork = malloc(sizeof(pthread_mutex_t) * table->n_philosophers);
	i = -1;
	while (++i < table->n_philosophers)
		pthread_mutex_init(&table->fork[i], NULL);
	return (table);
}

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

void	thread_monitoring(t_table *table, pthread_t *philo)
{
	int	i;

	while (!table->stats[0].start.tv_sec)
		;
	while (1)
	{
		i = -1;
		usleep(100);
		if (table->dead)
		{
			end_simulation(table, philo);
			break ;
		}
		while (++i < table->n_philosophers)
		{
			gettimeofday(&table->stats[i].end, NULL);
			if (time_diff(&table->stats[i].start, &table->stats[i].end)
				>= table->time_to_die)
			{
				print_stat(table, &table->stats[i], DEAD);
				table->dead = 1;
				break ;
			}
		}
	}
}

int	main_thread(t_table *table)
{
	pthread_t	*philo;
	int			i;

	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->lock, NULL);
	philo = malloc(sizeof(pthread_t) * table->n_philosophers);
	table->stats = malloc(sizeof(t_stats) * table->n_philosophers);
	table->order = 0;
	table->dead = 0;
	table->n_philosophers_full = 0;
	i = -1;
	while (++i < table->n_philosophers)
		init_stats(table, &table->stats[i]);
	i = -1;
	while (++i < table->n_philosophers)
		if (pthread_create(&philo[i], NULL, &philo_routine, (void *)table))
			return (1);
	thread_monitoring(table, philo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table		*table;

	if (argc < 5 || argc > 6)
	{
		printf("Correct usage: ./philo number_of_philosophers ");
		printf("time_to_die time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	table = create_table(argc, argv);
	if (!table)
	{
		printf("Error while parsing arguments.\n");
		return (1);
	}
	if (main_thread(table))
	{
		printf("Error while creating or waiting on threads.\n");
		return (1);
	}
	return (0);
}
